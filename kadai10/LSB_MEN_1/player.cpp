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

//*****************************************************************************
//	静的変数
//*****************************************************************************
bool	CPlayer::m_bDeath = false;

//*****************************************************************************
//	グローバル変数
//*****************************************************************************
int	g_spanshot = SPAN_SHOT;

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
	}

	//ジャンプ
	if(pKeyBoard->GetkeyboardTrigger(DIK_SPACE) && !jump)
	{
		m_Vertex_3d.Speed_vtx.y = 1.0f;
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

	//移動しているかどうかのフラグ指定
	if(m_Vertex_3d.vtx == oldVtx)
	{
		m_Vertex_3d.MoveFlag = false;
	}
	else
	{
		m_Vertex_3d.MoveFlag = true;
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

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

			//マトリックス初期化
			D3DXMatrixIdentity(&m_mtxWorld);

			//大きさ設定
			D3DXMatrixScaling(&mScale, m_Vertex_3d.Scail_vtx.x, m_Vertex_3d.Scail_vtx.y, m_Vertex_3d.Scail_vtx.z);

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

		//メッシュ読み込み
		LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)m_pD3DXMatBuff->GetBufferPointer();

			//描画開始
			for(unsigned int i = 0 ; i < m_nNumMat ; i++)
			{
				//マテリアルセット
				pDevice->SetMaterial(&pMaterial[i].MatD3D);

				if(Texture)
				{
					//テクスチャ貼り付け
					pDevice->SetTexture(0,
						Texture);
				}

				//描画
				m_pMesh->DrawSubset(i);
			}
			
		//マテリアルを元に戻す
		pMaterial->MatD3D.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
		pMaterial->MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pMaterial->MatD3D.Emissive = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pDevice->SetMaterial(&pMaterial->MatD3D);

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
							CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//下からめりこんでいるか
						else	if(m_Vertex_3d.Speed_vtx.y > 0.0f && m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y > pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) && 
															m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y < pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y)
						{
							//位置補正
							m_Vertex_3d.Speed_vtx.y = 0.0f;
							//影生成
							CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//下にいるか
						else
						{
							m_Vertex_3d.PosNowY = 0.0f;
							//影生成
							CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
					}
				}
			}
			pScene  = pSceneNext;
		}
	}

	m_Vertex_3d.PosNowY = 0.0f;

	//影生成
	CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);

}

