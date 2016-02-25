//***************************************************************
//
//	scene3d.cpp
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
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"manager.h"
#include	"scene.h"
#include	"scene_x.h"
#include	"texture.h"

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//	引数
//	int	nPriority：階層番号
//	イニシャライザ
//	CScene(nPriority)：階層番号受け渡し
//	戻り値
//	なし
//***************************************************************
CScene_x::CScene_x(int	nPriority):CScene(nPriority)
{
	//初期化
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CScene_x::~CScene_x()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//戻り値：
//HRESULT	終了コード
//***************************************************************
HRESULT	CScene_x::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo)
{
		//モデル読み込み
	if( FAILED(D3DXLoadMeshFromX(Name,
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"読み込め","エラー",MB_OK);

		}

	//初期化
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Rot_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
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
CScene_x	*CScene_x::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo)
{
	//ポインタ宣言
	CScene_x	*pScene_x;

	//クラス生成
	pScene_x = new	CScene_x;

	//初期化
	pScene_x->Init(pDevice ,vtx,Name,TexNo);

	return	pScene_x;

}
//***************************************************************
//	終了
//***************************************************************
void	CScene_x::Uninit()
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
void	CScene_x::Update()
{
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

	if(m_Vertex_3d.vtx.y < 0.0f)
	{
		m_Vertex_3d.vtx.y = 0.0f;
	}
}
//***************************************************************
//	描画
//***************************************************************
void	CScene_x::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mScale,mRotate;		//左から座標、大きさ、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

			//マトリックス初期化
			D3DXMatrixIdentity(&m_mtxWorld);

			//大きさ設定
			D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//角度設定
			D3DXMatrixRotationYawPitchRoll(&mRotate, m_Vertex_3d.Rot_vtx.y,m_Vertex_3d.Rot_vtx.x,m_Vertex_3d.Rot_vtx.z);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//座標設定
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x,m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z);

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
