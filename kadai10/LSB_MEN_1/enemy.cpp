//*****************************************************************************
//
//	player.cpp
//	name：Masatugu Kamada
//	create
//	更新日：2012/05/25
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
#include	"scene3d.h"
#include	"scene_x.h"
#include	"enemy.h"
#include	"manager.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"camera.h"
#include	"player.h"
#include	"shadow.h"
#include	"texture.h"
#include	"game.h"

//*****************************************************************************
//	静的変数
//*****************************************************************************

//*****************************************************************************
//
//	プレイヤークラス関数
//
//*****************************************************************************

//*****************************************************************************
//	コンストラクタ
//*****************************************************************************
CEnemy::CEnemy()
{

}

//*****************************************************************************
//	デストラクタ
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
//	敵生成
//	引数：
//	LPDIRECT3DDEVICE9	pDevice:デバイスポインタ
//	D3DXVECTOR3	vtx:座標
//	D3DXVECTOR3	rot:初期角度
//	float	speed:移動力
//	float	rotspeed:回転速度
//	float	jumpup:ジャンプ力
//	int	Type:行動タイプ
//	戻り値：
//	CEnemy：元クラス
//*****************************************************************************
CEnemy	*CEnemy::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,float	rotspeed,float	jumpup,int	Type,int	TexNo)
{
	CEnemy	*pEnemy;
	pEnemy = new	CEnemy;
	pEnemy->Init(pDevice,vtx,rot,speed,rotspeed,jumpup,Type,TexNo);

	return	pEnemy;

}
//*****************************************************************************
//	初期化
//	引数：
//	LPDIRECT3DDEVICE9	pDevice:デバイスポインタ
//	D3DXVECTOR3	vtx:座標
//	D3DXVECTOR3	rot:初期角度
//	float	speed:移動力
//	float	rotspeed:回転速度
//	float	jumpup:ジャンプ力
//	int	Type:行動タイプ
//	戻り値：
//	HRESULT：終了コード
//*****************************************************************************
HRESULT	CEnemy::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,
					 float	rotspeed,float	jumpup,int	nType,int	TexNo)
{
		//モデル読み込み
	if( FAILED(D3DXLoadMeshFromX("model/敵.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"読み込め","エラー",MB_OK);

		}

	//ステータス初期化
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vertex_3d.Scail_vtx = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Vertex_3d.Rot_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	type = nType;
	m_aEnamy.Speed = speed;
	m_aEnamy.RotSpeed = rotspeed;
	m_aEnamy.JumpUp = jumpup;
	m_aEnamy.Vec = 25.0f;
	m_nTex = TexNo;

	return	S_OK;
}

//*****************************************************************************
//	終了
//*****************************************************************************
void	CEnemy::Uninit()
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

	//リリース
	CScene::Release();

}

//*****************************************************************************
//	更新
//*****************************************************************************
void	CEnemy::Update()
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

	//プレイヤーの位置情報取得
	VERTEX_3D	Player = CGame::GetPlayer();

	//カメラ変数と取得
	D3DXVECTOR3	CameraRot = CCamera::GetCameraRot();

	//地面の高さの取得変数
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//過去の座標を記録
	D3DXVECTOR3	oldVtx = m_Vertex_3d.vtx;

	//タイプ毎の処理
	switch(type)
	{
		case	NOMAL_MOVE:
			//移動処理
		m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
		m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

		//指定距離減少
		if(m_Vertex_3d.Speed_vtx.z > 0.0f)
		{
			m_aEnamy.Vec -= m_Vertex_3d.Speed_vtx.z;
		}
		else
		{
			m_aEnamy.Vec += m_Vertex_3d.Speed_vtx.z;
		}

		//一定以上の距離まで行った場合
		if(m_aEnamy.Vec < 0.0f)
		{
			m_Vertex_3d.Rot_vtx.y += 1.0f;
			m_aEnamy.Vec = 25.0f;
		}
			break;
		case	ROLING:
		//回転
			m_Vertex_3d.Rot_vtx.y += m_aEnamy.RotSpeed;

			//移動処理
		m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
		m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

			break;

		case	JUMPING:
		if(m_Vertex_3d.vtx.y == pScene3d->GetHeight(m_Vertex_3d.vtx))
		{
			//ジャンプ
			m_Vertex_3d.Speed_vtx.y = m_aEnamy.JumpUp;
		}

			break;
		case	ROLL_JUMPING:
		//回転
			m_Vertex_3d.Rot_vtx.y += m_aEnamy.RotSpeed;

		if(m_Vertex_3d.vtx.y == pScene3d->GetHeight(m_Vertex_3d.vtx))
		{
			//ジャンプ
			m_Vertex_3d.Speed_vtx.y = m_aEnamy.JumpUp;
		}

		//移動処理
		m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
		m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

			break;
		case	PLAYER_JUMPING:

		if(m_Vertex_3d.vtx.y == pScene3d->GetHeight(m_Vertex_3d.vtx) && pKeyBoard->GetkeyboardPress(DIK_SPACE))
		{
			//ジャンプ
			m_Vertex_3d.Speed_vtx.y = m_aEnamy.JumpUp;
		}

		break;

		//追跡
		case	TRACKING:
            // 回転角度計算

            // 内積計算
            float cos1;                                          // 角度 cos θ
			cos1 = m_Vertex_3d.vtx.x * Player.vtx.x + m_Vertex_3d.vtx.z * Player.vtx.z;	// 内積
			m_Vertex_3d.Rot_vtx.y = cos( cos1 );                // 度数に変換

			//移動
			m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
			m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

			break;
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

	//当たり判定
	//プレイヤーと接触した場合
	if(HitEnemy(CGame::GetPlayer().vtx))
	{
		CPlayer::PlayerDeath();
	}

	//地面にいるかの判定
	if(m_Vertex_3d.vtx.y < pScene3d->GetHeight(m_Vertex_3d.vtx))
	{
		//高さの指定
		m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx);
	}

	//影生成
	//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3);

}

//*****************************************************************************
//	描画
//	引数：
//	LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//	戻り値：
//	なし
//*****************************************************************************
void	CEnemy::Draw(LPDIRECT3DDEVICE9	pDevice)
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

//*****************************************************************************
//	敵との当たり判定
//	引数：
//	D3DXVECTOR3	pos:対象の座標
//	戻り値
//	bool:当たり判定
//*****************************************************************************
bool	CEnemy::HitEnemy(D3DXVECTOR3 Pos)
{
	bool	Hit = false;

	if(m_Vertex_3d.vtx.x - 1.5f < Pos.x && m_Vertex_3d.vtx.x + 1.5f> Pos.x &&
		m_Vertex_3d.vtx.y - 1.5f < Pos.y && m_Vertex_3d.vtx.y + 1.5f> Pos.y &&
		m_Vertex_3d.vtx.z - 1.5f < Pos.z && m_Vertex_3d.vtx.z + 1.5f> Pos.z)
		{
			Hit= true;
		}

	return	Hit;
}
