//***************************************************************
//
//	coin.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"scenebillboard.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"manager.h"
#include	"player.h"
#include	"gimmick.h"
#include	"texture.h"

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
CGimmick::CGimmick()
{
	//初期化
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CGimmick::~CGimmick()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//戻り値：
//HRESULT	終了コード
//***************************************************************
HRESULT	CGimmick::Init(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo)
{
		//モデル読み込み
	if( FAILED(D3DXLoadMeshFromX("model/ギミック.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"読み込め","エラー",MB_OK);

		}

	//オブジェクトタイプの設定
	CGimmick::SetObjectType(CScene::TYPE_GIMMICK);

	//初期化
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Scail_vtx = Scail;
	m_Vertex_3d.Rot_vtx = rot;
	m_Vertex_3d.diffuse = D3DXCOLOR(1.0,0.0f,0.0f,1.0f);
	m_Vertex_3d.Speed_vtx = Speed;
	m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	生成関数
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//D3DXVECTOR3 vtx：指定座標
//戻り値
//CScene_x	元クラス
//***************************************************************
CGimmick	*CGimmick::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo)
{
	//ポインタ宣言
	CGimmick	*pGimmick;

	//クラス生成
	pGimmick = new	CGimmick;

	//初期化
	pGimmick->Init(pDevice, vtx,Scail,rot,Speed,TexNo);

	
	return	pGimmick;

}
//***************************************************************
//	終了
//***************************************************************
void	CGimmick::Uninit()
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

	CScene::Release();
}

//***************************************************************
//	更新
//***************************************************************
void	CGimmick::Update()
{
	//移動
	m_Vertex_3d.vtx.x += m_Vertex_3d.Speed_vtx.x;
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;
	m_Vertex_3d.vtx.z += m_Vertex_3d.Speed_vtx.z;

}
//***************************************************************
//	描画
//***************************************************************
void	CGimmick::Draw(LPDIRECT3DDEVICE9 pDevice)
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
			D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//角度設定
			D3DXMatrixRotationYawPitchRoll(&mRotate,D3DX_PI * m_Vertex_3d.Rot_vtx.y + D3DX_PI,0.0f,0.0f);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//座標設定
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x,CScene3d::GetHeight(m_Vertex_3d.vtx) + 1.0f + m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z);

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

