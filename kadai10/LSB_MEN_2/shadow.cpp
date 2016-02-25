//***************************************************************
//
//	wall.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/29
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"renderer.h"
#include	"manager.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"wall.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"field.h"
#include	"shadow.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//	引数
//	int	nPriority：階層番号
//	戻り値
//	なし
//***************************************************************
CShadow::CShadow()
{
	//初期化
	m_pD3DVtxBuff = NULL;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CShadow::~CShadow()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//D3DXCOLOR	color：配色カラ―
//D3DXVECTOR3	Rot:回転角度
//float	width:幅
//float	heght:高さ
//int	cutX:Ｘの分割数
//int	cutY:Ｙの分割数
//戻り値
//HRESULT:終了コード
//***************************************************************
HRESULT	CShadow::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo)
{
	//地面の高さの取得変数
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//数値初期化
	m_Vertex_3d.vtx = vtx;						//座標
	m_Vertex_3d.vtx.y += 0.1f;
	m_Vertex_3d.diffuse = color;				//配色
	m_Vertex_3d.Scail_vtx = Scail;
	if(life != 0)
	{
		m_ShadowPoint = 1 / (float)life;
	}
	else
	{
		m_ShadowPoint = 0.0f;
	}
	m_nTex = TexNo;

	//インデックス数
	m_Vertex_3d.index = 4;

			//バッファ設定
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * 4,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}

			if(FAILED(pDevice->CreateIndexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.index,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff,
											NULL)))
			{
				return	E_FAIL;
			}

				//アンロック変数
				VERTEX_3D	*pv;
				WORD	*pi;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

					pv[0].vtx = D3DXVECTOR3(-0.5f,0.0f,0.5f);
					pv[1].vtx = D3DXVECTOR3(0.5f,0.0f,0.5f);
					pv[2].vtx = D3DXVECTOR3(-0.5f,0.0f,-0.5f);
					pv[3].vtx = D3DXVECTOR3(0.5f,0.0f,-0.5f);

					pv[0].diffuse = D3DXCOLOR(1,1,1,1);
					pv[1].diffuse = D3DXCOLOR(1,1,1,1);
					pv[2].diffuse = D3DXCOLOR(1,1,1,1);
					pv[3].diffuse = D3DXCOLOR(1,1,1,1);

					pv[0].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
					pv[1].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
					pv[2].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
					pv[3].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);

					pv[0].tex = D3DXVECTOR2(0.0f,0.0f);
					pv[1].tex = D3DXVECTOR2(1.0f,0.0f);
					pv[2].tex = D3DXVECTOR2(0.0f,1.0f);
					pv[3].tex = D3DXVECTOR2(1.0f,1.0f);


					//ロック
					m_pD3DVtxBuff->Unlock();

					//インデックスバッファのアンロック
					m_pD3DIndexBuff->Lock(0,0,(void**)&pi,0);

					pi[0] = 0;
					pi[1] = 1;
					pi[2] = 2;
					pi[3] = 3;


					//ロック
					m_pD3DIndexBuff->Unlock();

	//高さの指定
	m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx) + 0.1f;


	return	S_OK;
}

//***************************************************************
//	ポリゴン生成
//引数：
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//D3DXCOLOR	color：配色カラ―
//D3DXVECTOR3	Rot:回転角度
//float	width:幅
//float	heght:高さ
//int	cutX:Ｘの分割数
//int	cutY:Ｙの分割数
//戻り値
//CWall	元クラス
//***************************************************************
CShadow	*CShadow::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo)
{
	//ポインタ宣言
	CShadow	*pWall;

	//クラス生成
	pWall = new	CShadow;

	//初期化
	pWall->Init(pDevice, vtx, color,Scail,life,TexNo);

	return	pWall;
}

//***************************************************************
//	終了
//***************************************************************
void	CShadow::Uninit()
{
	//解放処理
	//バッファ解放
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

	//インデックスバッファ解放
	if(m_pD3DIndexBuff != NULL)
	{
		m_pD3DIndexBuff->Release();
		m_pD3DIndexBuff = NULL;
	}

		CScene::Release();

}

//***************************************************************
//	更新
//***************************************************************
void	CShadow::Update()
{
	//地面の高さの取得変数
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//エフェクト減少
	m_Vertex_3d.Scail_vtx.x -= m_ShadowPoint;
	m_Vertex_3d.Scail_vtx.y -= m_ShadowPoint;
	m_Vertex_3d.Scail_vtx.z -= m_ShadowPoint;

	//高さの指定
	m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx) + 0.1f;

	if(m_Vertex_3d.Scail_vtx.x < 0.0f)
	{
		Uninit();
	}
}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//***************************************************************
void	CShadow::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mScale,mRotate;		//左から座標、大きさ、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::ADD);

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//大きさ設定
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

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

	//バッファ指定
	pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pD3DIndexBuff);

		//フォーマットの指定
		pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0,
				Texture);

			//画像表示
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);


}

