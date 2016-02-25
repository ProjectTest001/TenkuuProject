//*****************************************************************************
//
//	player.cpp
//	name：Masatugu Kamada
//	更新日：2012/06/25
//
//*****************************************************************************

//*****************************************************************************
//	インクルード
//*****************************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<stdio.h>
#include	<math.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene_x.h"
#include	"item.h"
#include	"player.h"
#include	"manager.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"camera.h"
#include	"scene3d.h"
#include	"field.h"
#include	"enemy.h"
#include	"number.h"
#include	"score.h"
#include	"ster.h"
#include	"time.h"
#include	"gimmick.h"
#include	"debugproc.h"
#include	"shadow.h"
#include	"texture.h"
#include	"shine.h"
#include	"xfile.h"
#include	"model.h"
#include	"script.h"

//*****************************************************************************
//	静的変数
//*****************************************************************************
bool	CPlayer::m_bDeath = false;
MOTIONDATA	*CPlayer::m_apKey = NULL;

//*****************************************************************************
//	グローバル変数
//*****************************************************************************
int	g_spanshot = SPAN_SHOT;

//モデルのパーツの位置と向き情報
static	float	g_akeyDefault[MODELPARTS_MAX][6] = 
{
	//座標				//角度
	{0.0f,2.3f,0.0f,  0.0f,0.0f,0.0f},			//腰
	{0.0f,0.2f,0.0f,  0.0f,0.0f,0.0f},			//身体
	{0.0f,2.6f,0.0f,  0.0f,0.0f,0.0f},			//首
	{0.0f,0.1f,0.0f,  0.0f,0.0f,0.0f},			//頭
	{0.05f,1.75f,0.0f,  0.0f,0.0f,0.0f},		//右腕
	{0.75f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//右肘
	{0.73f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//右手
	{-0.05f,1.75f,0.0f,  0.0f,0.0f,0.0f},		//左腕
	{-0.75f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//左肘
	{-0.73f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//左手
	{-0.1f,-0.43f,0.0f,  0.0f,0.0f,0.0f},			//右太もも
	{0.0f,-0.75f,0.0f,  0.0f,0.0f,0.0f},			//右膝
	{0.0f,-0.7f,0.0f,  0.0f,0.0f,0.0f},			//右足
	{0.1f,-0.43f,0.0f,  0.0f,0.0f,0.0f},			//左太もも
	{0.0f,-0.75f,0.0f,  0.0f,0.0f,0.0f},			//左膝
	{0.0f,-0.7f,0.0f,  0.0f,0.0f,0.0f},			//左足
};

//*****************************************************************************
//
//	プレイヤークラス関数
//
//*****************************************************************************

//*****************************************************************************
//	コンストラクタ
//*****************************************************************************
CPlayer::CPlayer()
{

}

//*****************************************************************************
//	デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
//	プレイヤー生成
//*****************************************************************************
CPlayer	*CPlayer::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo)
{
	CPlayer	*pPlayer;
	pPlayer = new	CPlayer;
	pPlayer->Init(pDevice,vtx,rot,TexNo);

	return	pPlayer;
}
//*****************************************************************************
//	初期化
//*****************************************************************************
HRESULT	CPlayer::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo)
{
		//モデル読み込み
	if( FAILED(D3DXLoadMeshFromX("model/棒人間.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"読み込め","エラー",MB_OK);
		}

	//ステータス初期化
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vertex_3d.Scail_vtx = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Vertex_3d.Rot_vtx = rot;
	m_bDeath = false;
	clear = false;
	m_pSceneLink = NULL;
	m_Vertex_3d.PosNowY = 0.0f;
	m_nTex = TexNo;

	//自身の影の生成＆初期化
	m_pShadow = new	CShadow();
	m_pShadow->Init(pDevice,m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),D3DXVECTOR3(1,1,1),0,SHADOW_TEXTURE);

	//パーツ初期化
	for(int	i = LSB_ID; i < LSB_ID + LSB_NUM; i++)
	{
		//モデルデータ生成
		m_apModel[i] = CModel::Create(pDevice,i,D3DXVECTOR3(g_akeyDefault[i][0],g_akeyDefault[i][1],g_akeyDefault[i][2]),
								D3DXVECTOR3(g_akeyDefault[i][3],g_akeyDefault[i][4],g_akeyDefault[i][5]),BLUE_TEXTURE);
	}
	//モデル階層構造設定
	m_apModel[MODELPARTS_WAIST]->SetParent(NULL);
	m_apModel[MODELPARTS_BODY]->SetParent(m_apModel[MODELPARTS_WAIST]);
	m_apModel[MODELPARTS_NECK]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_HEAD]->SetParent(m_apModel[MODELPARTS_NECK]);
	m_apModel[MODELPARTS_RIGHTARM]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_RIGHTELBOW]->SetParent(m_apModel[MODELPARTS_RIGHTARM]);
	m_apModel[MODELPARTS_RIGHTHAND]->SetParent(m_apModel[MODELPARTS_RIGHTELBOW]);
	m_apModel[MODELPARTS_LEFTARM]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_LEFTELBOW]->SetParent(m_apModel[MODELPARTS_LEFTARM]);
	m_apModel[MODELPARTS_LEFTHAND]->SetParent(m_apModel[MODELPARTS_LEFTELBOW]);
	m_apModel[MODELPARTS_RIGHTLEG]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_RIGHTKNEE]->SetParent(m_apModel[MODELPARTS_RIGHTLEG]);
	m_apModel[MODELPARTS_RIGHTFOOT]->SetParent(m_apModel[MODELPARTS_RIGHTKNEE]);
	m_apModel[MODELPARTS_LEFTLEG]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_LEFTKNEE]->SetParent(m_apModel[MODELPARTS_LEFTLEG]);
	m_apModel[MODELPARTS_LEFTFOOT]->SetParent(m_apModel[MODELPARTS_LEFTKNEE]);

	//モーションデータ取得
	m_apKey = CScript::GetPlayerMotion();

	//モーションの設定
	m_motionType = MOTIONTYPE_NEUTRAL;

	switch(m_motionType)
	{
		case	MOTIONTYPE_NEUTRAL:
			m_pKeyInfo = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_NEUTRAL].NumFrame;
			m_bLoopMotion = true;

			break;
	}

	m_nKey = 0;
	m_nCountMotion = 0;
	m_bMotion = false;
	m_bFinishMotion = false;

	m_pKeyInfoBlend = NULL;
	m_nNumBlend = 0;
	m_nKeyBlend = 0;
	m_nCountMotionBlend = 0;
	m_bLoopMotionBlend = false;

	m_nFrameBlend = 0;					//ブレンドする際にかけるフレーム数
	m_nCountBlend = 0;					//ブレンド中のカウンタ
	m_bBlendMotion = false;				//ブレンドするかどうか
	m_bBlendNow = false;

	return	S_OK;
}

//*****************************************************************************
//	終了
//*****************************************************************************
void	CPlayer::Uninit()
{
	//解放処理

	//メッシュ解放
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//バッファ解放
	if(m_pD3DXMatBuff != NULL)
	{
		m_pD3DXMatBuff->Release();
		m_pD3DXMatBuff = NULL;
	}

}

//*****************************************************************************
//	更新
//*****************************************************************************
void	CPlayer::Update()
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

	//カメラ変数と取得
	D3DXVECTOR3	CameraRot = CCamera::GetCameraRot();

	//地面の高さの取得変数
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//過去の座標を記録
	D3DXVECTOR3	oldVtx = m_Vertex_3d.vtx;

	//ギミックの影響を反映させる
	if(m_pSceneLink)
	{
			//ギミック情報取得
			VERTEX_3D	pVtx;
			m_pSceneLink->GetVtx(&pVtx);

			m_Vertex_3d.vtx += pVtx.Speed_vtx;
			//m_Vertex_3d.Rot_vtx.y += 0.005f;

		//プレイヤーの角度の修正
		while(m_Vertex_3d.Rot_vtx.y >= 1)
		{
			m_Vertex_3d.Rot_vtx.y -= 1 * 2;
		}

		while(m_Vertex_3d.Rot_vtx.y <= -1)
		{
			m_Vertex_3d.Rot_vtx.y += 1 * 2;
		}

	}
	//プレイヤーの今回の角度

	//死亡した場合
	if(m_bDeath)
	{
		//死亡エフェクト処理
		m_Vertex_3d.Scail_vtx -= D3DXVECTOR3(0.02f,0.02f,0.02f);
		m_Vertex_3d.Rot_vtx.y += 0.2f;
		m_Vertex_3d.vtx.y += 0.1f;

		//プレイヤーが消滅したらゲーム終了
		if(m_Vertex_3d.Scail_vtx.x < 0.0f)
		{
			CScene::Release();
			CManager::ChangeMode(CManager::MODE_REZULT_GAMEOVER);
		}

		//以下の処理を行わずに終了
		return;
	}

	//移動処理
		//奥移動
	if(pKeyBoard->GetkeyboardPress(DIK_W))
	{
		//角度指定
		if(pKeyBoard->GetkeyboardPress(DIK_D))
		{
			PurposeRot = 0.25f + CameraRot.y;
		}
		else	if(pKeyBoard->GetkeyboardPress(DIK_A))
		{
			PurposeRot = -0.25f + CameraRot.y;
		}
		else
		{
			PurposeRot = 0.0f + CameraRot.y;
		}

			ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;

	}
	//手前移動
	else	if(pKeyBoard->GetkeyboardPress(DIK_S))
	{
		if(pKeyBoard->GetkeyboardPress(DIK_D))
		{
			PurposeRot = 0.75f + CameraRot.y;
		}
		else	if(pKeyBoard->GetkeyboardPress(DIK_A))
		{
			PurposeRot = -0.75f + CameraRot.y;
		}
		else
		{
			PurposeRot = 1.0f + CameraRot.y;
		}

		ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;

	}
	//左移動
	else	if(pKeyBoard->GetkeyboardPress(DIK_A))
	{
		PurposeRot = -0.5f + CameraRot.y ;

		ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;

	}
	//右移動
	else	if(pKeyBoard->GetkeyboardPress(DIK_D))
	{
		//目的の角度の指定
		PurposeRot = 0.5f + CameraRot.y;

		//角度の結果を計算
		ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;
	}
	else
	{
		m_Vertex_3d.MoveFlag = false;
	}

	//移動処理
	if(m_Vertex_3d.MoveFlag)
	{
		while(ResultRot >= 1)
		{
			ResultRot -= 1 * 2;
		}

		while(ResultRot <= -1)
		{
			ResultRot += 1 * 2;
		}

		m_Vertex_3d.Rot_vtx.y += ResultRot * PLAYER_ROT;

		m_Vertex_3d.Speed_vtx.x += sin(D3DX_PI * PurposeRot) * MOVE;
		m_Vertex_3d.Speed_vtx.z += cos(D3DX_PI * PurposeRot) * MOVE;

		if(!jump && !m_bMotion)
		{
			if(m_bBlendMotion)
			{
				m_bBlendMotion = false;
			}
			SetMotion(MOTIONTYPE_WALK,10,m_bMotion);
		}
	}
	else
	{
		if(GetMotion() == MOTIONTYPE_WALK)
		{
			m_bFinishMotion = true;
		}
	}

	//ジャンプ
	if(pKeyBoard->GetkeyboardTrigger(DIK_SPACE) && !jump)
	{
		m_Vertex_3d.Speed_vtx.y = 1.0f;
		SetMotion(MOTIONTYPE_JUMP,10,false);
	}
	else	if(pKeyBoard->GetkeyboardTrigger(DIK_1))
	{
		SetMotion(MOTIONTYPE_PUNCH,10,m_bMotion);
	}
	//重力
	m_Vertex_3d.Speed_vtx.y -= 0.03f;

	//空気抵抗
	m_Vertex_3d.Speed_vtx.y -= m_Vertex_3d.Speed_vtx.y * 0.05f;

	//抵抗摩擦
	m_Vertex_3d.Speed_vtx.x -= m_Vertex_3d.Speed_vtx.x * 0.2f;
	m_Vertex_3d.Speed_vtx.z -= m_Vertex_3d.Speed_vtx.z * 0.2f;

	//移動
	m_Vertex_3d.vtx.x += m_Vertex_3d.Speed_vtx.x;
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;
	m_Vertex_3d.vtx.z += m_Vertex_3d.Speed_vtx.z;

	//コインを全て取得したら
	if(CScore::GetScore() >= 500 && !clear)
	{
		CSter::Create(CRenderer::GetDevice(),D3DXVECTOR3(-48.0f,0.0f,48.0f),YEROWW_TEXTURE);
		clear = true;
	}
	//一定以上落下で死亡
	if(m_Vertex_3d.vtx.y < -5.0f)
	{
		m_bDeath = true;
		PlaySound(SE_00,false);
	}

	//時間終了でもアウト
	if(CTime::TimeUp())
	{
		m_bDeath = true;
		PlaySound(SE_00,false);
	}

	//地面にいるかの判定
	if(m_Vertex_3d.vtx.y < pScene3d->GetHeight(m_Vertex_3d.vtx))
	{
		//高さの指定
		m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx);
		jump = false;
		if(m_motionType == MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_NEUTRAL,8,true);
		}

	}
	//宙に浮いている場合
	else
	{
		jump = true;
	}

	//ギミック更新処理
	HitGimmick();

	//壁にぶつかったかの判定
	if(HitWall())
	{
		m_Vertex_3d.vtx = oldVtx;
	}

	//モーションの更新
	UpdateMotion();

	//単発モーションが終了した場合
	if(m_bFinishMotion)
	{
			if(m_bBlendMotion)
			{
				m_bBlendMotion = false;
			}
			if(GetMotion() == MOTIONTYPE_WALK)
			{
				SetMotion(MOTIONTYPE_NEUTRAL,20,true);
			}
			else
			{
				SetMotion(MOTIONTYPE_NEUTRAL,10,false);
			}
			m_bMotion = false;
			m_bFinishMotion = false;
	}

}

//*****************************************************************************
//	描画
//	引数：
//	LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//	戻り値：
//	なし
//*****************************************************************************
void	CPlayer::Draw(LPDIRECT3DDEVICE9	pDevice)
{
	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mScale,mRotate;		//左から座標、大きさ、回転

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

			//マトリックス初期化
			D3DXMatrixIdentity(&m_mtxWorld);

			//大きさ設定
			D3DXMatrixScaling(&mScale, 0.6f, 0.6f, 0.6f);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//角度設定
			D3DXMatrixRotationYawPitchRoll(&mRotate, D3DX_PI * m_Vertex_3d.Rot_vtx.y + D3DX_PI, D3DX_PI * m_Vertex_3d.Rot_vtx.x, D3DX_PI * m_Vertex_3d.Rot_vtx.z);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//座標設定
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x, m_Vertex_3d.vtx.y, m_Vertex_3d.vtx.z);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

			//セッティング
			pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

		//モデルの各パーツの描画
		for(int	i = 0 ; i < MODELPARTS_MAX; i++)
		{
			if(m_apModel[i])
			{
				m_apModel[i]->Draw(pDevice);
			}
		}

}

//*********************************************
//	壁との当たり判定
//
//*********************************************
bool	CPlayer::HitWall(void)
{
	CDebugProc::Print("%f",m_Vertex_3d.vertex.x);
	bool	Hit = false;
	//地面情報取得
	VERTEX_3D	pField = CField::GetVertex();

	//ベクトル変数宣言
	const	D3DXVECTOR3	aVtx[4] = 
	{
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2) ),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//左上
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//右上
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//右下
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2)),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//左下
	};
	
	//角度が加わった時の修正変数
	D3DXVECTOR3	aVtxNew[4];
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
		aVtxNew[nCount].x = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x + cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z;
		aVtxNew[nCount].z = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z - cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x;
	}


	//当たり判定測定
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
				//弾と壁のベクトル関係の計算
				D3DXVECTOR3	nVtx = aVtxNew[(int)(nCount + 1) % 4] - aVtxNew[nCount];
				D3DXVECTOR3	BulletVtx = m_Vertex_3d.vtx - aVtxNew[nCount];

			//外積計算で負の数字になった場合、当たった事にする
			if( (nVtx.z * BulletVtx.x- nVtx.x * BulletVtx.z) < 0 )
			{
				Hit = true;
			}
	}

	return	Hit;
}

//*********************************************
//	ギミック系更新処理
//
//*********************************************
void	CPlayer::HitGimmick(void)
{
	//ギミック初期化
	m_pSceneLink = NULL;

	for(int	i = 0; i < MAX_LIST; i++)
	{
		CScene	*pScene = CScene::GetTopScene(i);
		while(pScene)
		{
			CScene	*pSceneNext = pScene->GetNext();
			CScene::OBJECT_TYPE	Type = pScene->GetType();

			//CGimmickだった場合
			if(Type == CScene::TYPE_GIMMICK)
			{
				//ギミックの４頂点の変数宣言
				D3DXVECTOR3	aVtxScene[4];

				//ギミック情報取得
				VERTEX_3D	pVtx;
				pScene->GetVtx(&pVtx);

				//ギミック角度設定
				float	fValueSin = sinf(pVtx.Rot_vtx.y);
				float	fValueCos = cos(pVtx.Rot_vtx.y);
				D3DXVECTOR3	VtxMax = pVtx.vtx + pVtx.Scail_vtx;
				D3DXVECTOR3	VtxMin = pVtx.vtx - pVtx.Scail_vtx;

				aVtxScene[0] = D3DXVECTOR3(pVtx.vtx.x - pVtx.Scail_vtx.x ,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z + pVtx.Scail_vtx.z);
				aVtxScene[1] = D3DXVECTOR3(pVtx.vtx.x + pVtx.Scail_vtx.x,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z + pVtx.Scail_vtx.z);
				aVtxScene[2] = D3DXVECTOR3(pVtx.vtx.x + pVtx.Scail_vtx.x,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z - pVtx.Scail_vtx.z);
				aVtxScene[3] = D3DXVECTOR3(pVtx.vtx.x - pVtx.Scail_vtx.x,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z - pVtx.Scail_vtx.z);
/*
				aVtxScene[0] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMin.x + fValueCos * VtxMax.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMax.z + fValueSin * VtxMin.x);

				aVtxScene[1] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMax.x + fValueCos * VtxMin.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMax.z - fValueSin * VtxMin.x);

				aVtxScene[2] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMax.x - fValueCos * VtxMin.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMin.z - fValueSin * VtxMax.x);

				aVtxScene[3] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMin.x - fValueCos * VtxMax.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMin.z + fValueSin * VtxMax.x);
*/
				int	HitCount = 0;
				for(int	nCount = 0 ; nCount < 4 ; nCount++)
				{
					//弾と壁のベクトル関係の計算
					D3DXVECTOR3	nVtx = aVtxScene[(int)(nCount + 1) % 4] - aVtxScene[nCount];
					D3DXVECTOR3	PlayerVtx = m_Vertex_3d.vtx - aVtxScene[nCount];

					//プレイヤーが範囲内にいる
					if( (nVtx.z * PlayerVtx.x- nVtx.x * PlayerVtx.z) > 0 )
					{
						HitCount++;
					}

					if(HitCount >= 4)
					{
						//上空にいる

						//上からめりこんでいるか
						if(m_Vertex_3d.Speed_vtx.y < 1.2f && m_Vertex_3d.vtx.y < pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y &&
															m_Vertex_3d.vtx.y > pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx))
						{
							//位置補正
							m_Vertex_3d.PosNowY = m_Vertex_3d.vtx.y;
							m_Vertex_3d.vtx.y = pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y;
							jump = false;
							m_pSceneLink = pScene;
							//影生成
							//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//下からめりこんでいるか
						else	if(m_Vertex_3d.Speed_vtx.y > 0.0f && m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y > pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) && 
															m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y < pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y)
						{
							//位置補正
							m_Vertex_3d.Speed_vtx.y = 0.0f;
							//影生成
							//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//下にいるか
						else
						{
							m_Vertex_3d.PosNowY = 0.0f;
							//影生成
							//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
					}
				}
			}
			pScene  = pSceneNext;
		}
	}

	m_Vertex_3d.PosNowY = 0.0f;

	//地面の高さの取得変数
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//影配置指定
	m_pShadow->SetPos(D3DXVECTOR3(m_Vertex_3d.vtx.x,pScene3d->GetHeight(m_Vertex_3d.vtx),m_Vertex_3d.vtx.z));

}

//***************************************************
//	モーションの設定
//	引数
//	MOTIONTYPE	type：モーションタイプ
//	int	nFrameBlend:ブレンド中のカウンタ
//	bool	bBlend:ブレンドするかどうか
//	戻り値
//	なし
//***************************************************
void	CPlayer::SetMotion(CPlayer::MOTIONTYPE type,int	nFrameBlend,bool	bBlend)
{
	//ブレンド処理を行っている場合
	if(m_bBlendMotion)
	{
		return;
	}

	m_motionType = type;
	switch(m_motionType)
	{
		//何もしない
	case	MOTIONTYPE_NEUTRAL:
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_NEUTRAL].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_NEUTRAL].NumFrame;
			m_bLoopMotion = true;
		}
		break;

		//歩く
	case	MOTIONTYPE_WALK:
		//ブレンドする場合
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_WALK].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_WALK].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_WALK].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_WALK].NumFrame;
			m_bLoopMotion =true;
		}
		break;

		//パンチ
	case	MOTIONTYPE_PUNCH:
		//ブレンドする場合
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_PUNCH].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_PUNCH].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_PUNCH].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_PUNCH].NumFrame;
			m_bLoopMotion =false;
		}

		break;

		//キック
	case	MOTIONTYPE_KICK:

		break;

	case	MOTIONTYPE_KICK2:

		break;

		//ジャンプ
	case	MOTIONTYPE_JUMP:
		//ブレンドする場合
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_JUMP].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_JUMP].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_JUMP].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_JUMP].NumFrame;
			m_bLoopMotion =false;
		}

		break;
	case	MOTIONTYPE_JUMPEND:

		break;
	case	MOTIONTYPE_HIT:
		break;

		
	}

	//ブレンドする場合
	if(bBlend)
	{
		m_nKeyBlend = 0;
		m_nCountMotionBlend = 0;
		m_nFrameBlend = nFrameBlend;
		m_nCountBlend = 0;
		m_bBlendMotion = true;
	}
	else
	{
		m_nKey = 0;
		m_nCountMotion = 0;
		m_nCountBlend = 0;
		m_bMotion = true;
	}

	//m_bFinishMotion = false;
}

//******************************************************
//	モーションの更新
//	引数
//	なし
//	戻り値
//	なし
//******************************************************
void	CPlayer::UpdateMotion()
{
	for(int	i = 0; i < MODELPARTS_MAX ; i++)
	{
		KEY	*pKey,*pKeyNext;		//現在のキーと次のキーポインタ

		float	fDiffMotion;		//差分
		float	fRateMotion;		//再生フレームｎ相対値

		float	fPosX,fPosY,fPosZ;		//座標
		float	fRotX,fRotY,fRotZ;		//角度

		//キー情報の取得
		if(!m_bBlendNow)
		{
			pKey = &m_pKeyInfo[m_nKey].aKEY[i];
		}
		else
		{
			pKey = &m_pKeyInfoBlend[m_nKeyBlend].aKEY[i];
		}

		//キーカウントが最大数でかつ、ループモーションの場合
		if(m_nKey >= m_nNumber-1 && m_bLoopMotion)
		{
			pKeyNext = &m_pKeyInfo[0].aKEY[i];
		}
		//キーカウントが最大数でかつ、ループモーションではない場合
		else	if(m_nKey >= m_nNumber-1 && !m_bLoopMotion)
		{
			pKeyNext = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0].aKEY[i];
		}
		else	if(m_bBlendNow)
		{
			pKeyNext = &m_pKeyInfoBlend[m_nKeyBlend+1].aKEY[i];
		}
		else
		{
			pKeyNext = &m_pKeyInfo[m_nKey+1].aKEY[i];
		}

		fRateMotion = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

		//ブレンド中の場合
		if(m_bBlendMotion)
		{
			//ブレンド用変数宣言
			KEY	*pKeyBlend,*pKeyNextBlend;
			float	fDiffMotionBlend;			//差分
			float	fRateMotionBlend;			//再生フレームｎ相対値
			float	fKeyCurrent;				//現在のモーションのポーズ数
			float	fKeyBlend;					//ブレンドモーションのポーズ数
			float	fDiffBlend;					//現在のモーションのポーズの値とブレンドモーションのポーズの値の差分
			float	fRateBlend;					//ブレンド比率

			pKeyBlend = &m_pKeyInfoBlend[m_nKeyBlend].aKEY[i];

				if(m_nKeyBlend >= m_nNumBlend-1 && m_bLoopMotionBlend)
				{
					pKeyNextBlend = &m_pKeyInfoBlend[0].aKEY[i];
				}
				else	if(m_nKeyBlend >= m_nNumBlend-1 && !m_bLoopMotionBlend)
				{
					pKeyNextBlend = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0].aKEY[i];
				}
				else
				{
					pKeyNextBlend = &m_pKeyInfoBlend[m_nKeyBlend+1].aKEY[i];
				}

			fRateMotionBlend = (float)m_nCountMotionBlend / (float)m_pKeyInfoBlend[m_nKeyBlend].nFrame;

			//ブレンドモーションの計算
			//元モーションの差分計算
			fDiffMotion = pKeyNext->posx - pKey->posx;

			//元モーションのポーズ数計算
			fKeyCurrent = pKey->posx + (fDiffMotion * fRateMotion);

			//元モーションとブレンドモーションの差分計算
			fDiffMotionBlend = pKeyNextBlend->posx - pKeyBlend->posx;

			//ブレンドモーション数計算
			fKeyBlend = pKeyBlend->posx + (fDiffMotionBlend * fRateMotionBlend);

			//ブレンド比率計算
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;

			//ポーズの差分計算
			fDiffBlend = fKeyBlend - fKeyCurrent;

			//変数指定（Ｘ座標）
			fPosX = fKeyCurrent + (fDiffBlend * fRateBlend);

			//以下同じ計算を別の変数に指定させる
			//Ｙ座標
			fDiffMotion = pKeyNext->posy - pKey->posy;
			fKeyCurrent = pKey->posy + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->posy - pKeyBlend->posy;
			fKeyBlend = pKeyBlend->posy + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fPosY = fKeyCurrent + (fDiffBlend * fRateBlend);

			//Ｚ座標
			fDiffMotion = pKeyNext->posz - pKey->posz;
			fKeyCurrent = pKey->posz + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->posz - pKeyBlend->posz;
			fKeyBlend = pKeyBlend->posz + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fPosZ = fKeyCurrent + (fDiffBlend * fRateBlend);

			//Ｘ角度
			fDiffMotion = pKeyNext->rotx - pKey->rotx;
			fKeyCurrent = pKey->rotx + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->rotx - pKeyBlend->rotx;
			fKeyBlend = pKeyBlend->rotx + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fRotX = fKeyCurrent + (fDiffBlend * fRateBlend);

			//Ｙ角度
			fDiffMotion = pKeyNext->roty - pKey->roty;
			while(fDiffMotion >= 1)
			{
				fDiffMotion -= 1 * 2;
			}
			while(fDiffMotion <= -1)
			{
				fDiffMotion += 1 * 2;
			}

			fKeyCurrent = pKey->roty + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->roty - pKeyBlend->roty;
			while(fDiffMotionBlend >= 1)
			{
				fDiffMotionBlend -= 1 * 2;
			}
			while(fDiffMotionBlend <= -1)
			{
				fDiffMotionBlend += 1 * 2;
			}

			fKeyBlend = pKeyBlend->roty + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fRotY = fKeyCurrent + (fDiffBlend * fRateBlend);

			//Ｚ角度
			fDiffMotion = pKeyNext->rotz - pKey->rotz;
			fKeyCurrent = pKey->rotz + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->rotz - pKeyBlend->rotz;
			fKeyBlend = pKeyBlend->rotz + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fRotZ = fKeyCurrent + (fDiffBlend * fRateBlend);

		}
		else
		{
			/*
			if(m_bBlendNow)
			{
				//ブレンド用変数宣言
				KEY	*pKeyBlend,*pKeyNextBlend;
				float	fDiffMotionBlend;			//差分
				float	fRateMotionBlend;			//再生フレームｎ相対値
				float	fKeyCurrent;				//現在のモーションのポーズ数
				float	fKeyBlend;					//ブレンドモーションのポーズ数
				float	fDiffBlend;					//現在のモーションのポーズの値とブレンドモーションのポーズの値の差分
				float	fRateBlend;					//ブレンド比率

				pKeyBlend = &m_pKeyInfo[m_nKey].aKEY[i];

					if(m_nKey >= m_nNumber-1)
					{
						pKeyNextBlend = &m_pKeyInfo[0].aKEY[i];
					}
					else
					{
						pKeyNextBlend = &m_pKeyInfo[m_nKey+1].aKEY[i];
					}

				fRateMotionBlend = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

				//ブレンドモーションの計算
				//元モーションの差分計算
				fDiffMotion = pKeyNext->posx - pKey->posx;

				//元モーションのポーズ数計算
				fKeyCurrent = pKey->posx + (fDiffMotion * fRateMotion);

				//元モーションとブレンドモーションの差分計算
				fDiffMotionBlend = pKeyNextBlend->posx - pKeyBlend->posx;

				//ブレンドモーション数計算
				fKeyBlend = pKeyBlend->posx + (fDiffMotionBlend * fRateMotionBlend);

				//ブレンド比率計算
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;

				//ポーズの差分計算
				fDiffBlend = fKeyBlend - fKeyCurrent;

				//変数指定（Ｘ座標）
				fPosX = fKeyCurrent + (fDiffBlend * fRateBlend);

				//以下同じ計算を別の変数に指定させる
				//Ｙ座標
				fDiffMotion = pKeyNext->posy - pKey->posy;
				fKeyCurrent = pKey->posy + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->posy - pKeyBlend->posy;
				fKeyBlend = pKeyBlend->posy + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fPosY = fKeyCurrent + (fDiffBlend * fRateBlend);

				//Ｚ座標
				fDiffMotion = pKeyNext->posz - pKey->posz;
				fKeyCurrent = pKey->posz + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->posz - pKeyBlend->posz;
				fKeyBlend = pKeyBlend->posz + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fPosZ = fKeyCurrent + (fDiffBlend * fRateBlend);

				//Ｘ角度
				fDiffMotion = pKeyNext->rotx - pKey->rotx;
				fKeyCurrent = pKey->rotx + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->rotx - pKeyBlend->rotx;
				fKeyBlend = pKeyBlend->rotx + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fRotX = fKeyCurrent + (fDiffBlend * fRateBlend);

				//Ｙ角度
				fDiffMotion = pKeyNext->roty - pKey->roty;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}

				fKeyCurrent = pKey->roty + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->roty - pKeyBlend->roty;
				while(fDiffMotionBlend >= 1)
				{
					fDiffMotionBlend -= 1 * 2;
				}
				while(fDiffMotionBlend <= -1)
				{
					fDiffMotionBlend += 1 * 2;
				}

				fKeyBlend = pKeyBlend->roty + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fRotY = fKeyCurrent + (fDiffBlend * fRateBlend);

				//Ｚ角度
				fDiffMotion = pKeyNext->rotz - pKey->rotz;
				fKeyCurrent = pKey->rotz + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->rotz - pKeyBlend->rotz;
				fKeyBlend = pKeyBlend->rotz + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fRotZ = fKeyCurrent + (fDiffBlend * fRateBlend);

			}
			else
			{
			*/
				fDiffMotion = pKeyNext->posx - pKey->posx;
				fPosX = pKey->posx + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->posy - pKey->posy;
				fPosY = pKey->posy + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->posz - pKey->posz;
				fPosZ = pKey->posz + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->rotx - pKey->rotx;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}

				fRotX = pKey->rotx + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->roty - pKey->roty;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}
				fRotY = pKey->roty + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->rotz - pKey->rotz;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}
				fRotZ = pKey->rotz + (fDiffMotion * fRateMotion);
			//}
		}

		m_apModel[i]->SetVertex(D3DXVECTOR3(fPosX,fPosY,fPosZ));
		m_apModel[i]->SetRot(D3DXVECTOR3(fRotX,fRotY,fRotZ));
	}

	//ブレンド中の場合
	if(m_bBlendMotion)
	{
		m_nCountMotionBlend++;
		//該当のキーの再生フレーム数に達した
		if(m_nCountMotionBlend >= m_pKeyInfoBlend[m_nKeyBlend].nFrame)
		{
			//単発モーションでかつ、最終キーに達した
			if(!m_bLoopMotionBlend && m_nKeyBlend >= m_nNumBlend -1)
			{
				m_bFinishMotion = true;
				m_nCountMotionBlend = 0;
				m_nKeyBlend = 0;
			}
			else	if(m_bLoopMotionBlend && m_nKey >= m_nNumber -1)
			{
				m_nKeyBlend = 0;
				m_nCountMotionBlend = 0;
			}
			else
			{
				if(m_motionType != MOTIONTYPE_JUMP)
				{
					m_nKeyBlend++;

					m_nCountMotionBlend = 0;
				}
			}

		}

		m_nCountBlend++;

		if(m_nCountBlend >= m_nFrameBlend)
		{
			m_nFrameBlend = 1;
			m_nCountBlend = 1;
		}

	}
	else
	{
		//フレーム上昇
		if(m_motionType != MOTIONTYPE_JUMP || m_nCountMotion < m_pKeyInfo[m_nKey].nFrame)
		{
			m_nCountMotion++;
		}

		//該当のキーの再生フレーム数に達した
		if(m_nCountMotion >= m_pKeyInfo[m_nKey].nFrame)
		{
			//単発モーションでかつ、最終キーに達した
			if(!m_bLoopMotion && m_nKey >= m_nNumber -1)
			{
				m_bFinishMotion = true;
				m_nCountMotion = 0;
				m_nKey = 0;
			}
			else	if(m_bLoopMotion && m_nKey >= m_nNumber -1)
			{
				m_nKey = 0;
				m_nCountMotion = 0;
			}
			else
			{
				if(m_motionType == MOTIONTYPE_JUMP && m_nKey <= m_nNumber)
				{

				}
				else
				{
					m_nKey++;
					m_nCountMotion = 0;
				}
			}
		}

	}
}
