//***************************************************************
//
//	sky.cpp
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
#include	"scene.h"
#include	"scene3d.h"
#include	"sky.h"
#include	"texture.h"

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
CSky::CSky()
{
	//初期化
	m_pD3DVtxBuff = NULL;
	m_pD3DIndexBuff = NULL;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CSky::~CSky()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//D3DXCOLOR	color：配色カラ―
//戻り値
//HRESULT:終了コード
//***************************************************************
HRESULT	CSky::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
				   int	cut,float	heght,int	cutY,float	rot,int	TexNo)
{
	//数値初期化
	m_Vertex_3d.vtx = vtx;						//座標
	m_Vertex_3d.diffuse = color;				//配色
	m_Vertex_3d.vertex.y = (float)(cutY);	//Ｙ座標の分割数（＋１は頂点数の補完）
	m_Vertex_3d.vertex.x = (float)(cut + 1.0f);	//円の分割数（＋１は頂点数の補完）
	m_Vertex_3d.Rot_vtx.x = rot;
	m_Vertex_3d.Scail_vtx.y = heght;			//高さ
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) + (m_Vertex_3d.vertex.y - (m_Vertex_3d.vertex.y * 1 / 4) )) * 2;
	m_nTex = TexNo;

	//空反転時の法線対策
	D3DXVECTOR3	nor;

	if(rot == 180.0f)
	{
		nor = D3DXVECTOR3(0.0f,-1.0f,0.0f);
	}
	else
	{
		nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}
	//バッファ設定（ドーム）
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) * 2,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}

			if(FAILED(pDevice->CreateIndexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.index * 2,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff,
											NULL)))
			{
				return	E_FAIL;
			}

			//バッファ設定（フタ）
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.vertex.x + 1,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff2,
											NULL)))
			{
				return	E_FAIL;
			}

			if(FAILED(pDevice->CreateIndexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.vertex.x + 2,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff2,
											NULL)))
			{
				return	E_FAIL;
			}

//*************************************************************
//ドーム生成
//*************************************************************
				//アンロック変数
				VERTEX_3D	*pv;
				WORD	*pi;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//画像の初期化の流れ
				int	yCount = 0;
				int	xCount = 0;

				//各頂点座標書き込み
				for(int	y = 0 ; y < (int)m_Vertex_3d.vertex.y  ; y++)
				{
					for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x;x++)
					{
						int	nCount_i = yCount * (int)m_Vertex_3d.vertex.x + xCount;
						float	NewVec = (vec / cutY) * (y+1);
						pv[nCount_i].vtx.x = sinf(D3DXToRadian((float)(360.0f / cut) * x)) * NewVec;
						pv[nCount_i].vtx.z = cosf(D3DXToRadian((float)(360.0f / cut) * x)) * NewVec;
						pv[nCount_i].vtx.y = sinf(cosf(D3DXToRadian((float)(90.0f / cutY) * (y+1)))) * vec;
						pv[nCount_i].tex.x = (float)(1.0f / m_Vertex_3d.vertex.x) * x;
						pv[nCount_i].tex.y = (float)(1.0f / m_Vertex_3d.vertex.y) * y;
						pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
						pv[nCount_i].hor = nor;
						xCount++;
					}
					yCount++;
					xCount = 0;
				}

					//ロック
					m_pD3DVtxBuff->Unlock();

					//インデックスバッファのアンロック
					m_pD3DIndexBuff->Lock(0,0,(void**)&pi,0);

									//インデックス書き込み用変数宣言
				int	n = 0;	//Ｎｕｍ変数
				int	a;		//ナンバー設定変数

				//インデックス設定
			for(int	gz = 0; gz < (int)m_Vertex_3d.vertex.y - 1 ;gz++)
			{
				//最初はスルー
				if(n != 0)
				{
					pi[n] = (a + 1) + (int)m_Vertex_3d.vertex.x;
					n++;
				}

					//インデックス書き込み
					for(int	gx = 0; gx < (int)m_Vertex_3d.vertex.x ;gx++)
					{
							a = gz * (int)m_Vertex_3d.vertex.x  + gx;

						pi[n+0] = a + (int)m_Vertex_3d.vertex.x;
						pi[n+1] = a;
						n += 2;
					}

				//最後はスルー
				if(gz != (int)m_Vertex_3d.vertex.y )
				{
					pi[n] = a;
					n++;
				}
			}
					//ロック
					m_pD3DIndexBuff->Unlock();

//***************************************************************
//フタ生成
//***************************************************************
				//アンロック変数
				VERTEX_3D	*pv2;
				WORD	*pi2;

					//ロック解除
					m_pD3DVtxBuff2->Lock(0,0,(void**)&pv2,0);

						for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x ;x++)
						{
							if(x == 0)
							{
								pv2[x].vtx.x = 0.0f;
								pv2[x].vtx.z = 0.0f;
							}
							else
							{
								pv2[x].vtx.x = sinf(D3DXToRadian((float)(360.0f / cut) * (cut - (x-1) ))) * (vec / m_Vertex_3d.vertex.y);
								pv2[x].vtx.z = cosf(D3DXToRadian((float)(360.0f / cut) * (cut - (x-1) ))) * (vec / m_Vertex_3d.vertex.y);
							}
							pv2[x].vtx.y = sinf(cosf(D3DXToRadian(0.0f))) * vec;
							pv2[x].tex.x = (float)x;
							pv2[x].tex.y = 1.0f;
							pv2[x].diffuse = m_Vertex_3d.diffuse;
							pv2[x].hor = nor;
						}
					//ロック
					m_pD3DVtxBuff2->Unlock();

					//インデックスバッファのアンロック
					m_pD3DIndexBuff2->Lock(0,0,(void**)&pi2,0);

						for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x + 1;x++)
						{
							if(x == (int)m_Vertex_3d.vertex.x)
							{
								pi2[x] = 1;
							}
							else
							{
								pi2[x] = x;
							}
						}
					//ロック
					m_pD3DIndexBuff2->Unlock();

		m_Vertex_3d.Rot_vtx.y = 0.0f;

	return	S_OK;
}

//***************************************************************
//	ポリゴン生成
//引数：
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//D3DXCOLOR	color：配色カラ―
//戻り値
//CScene3d	元クラス
//***************************************************************
CSky	*CSky::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
					  int	cut,float	heght,int	cutY,float	rot,int	TexNo)
{
	//ポインタ宣言
	CSky	*pSky;

	//クラス生成
	pSky = new	CSky;

	//初期化
	pSky->Init(pDevice, vtx,vec, color,cut,heght,cutY,rot,TexNo);

	return	pSky;
}

//***************************************************************
//	終了
//***************************************************************
void	CSky::Uninit()
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

	//バッファ解放
	if(m_pD3DVtxBuff2 != NULL )
	{
		m_pD3DVtxBuff2->Release();
		m_pD3DVtxBuff2 = NULL;
	}

	//インデックスバッファ解放
	if(m_pD3DIndexBuff2 != NULL)
	{
		m_pD3DIndexBuff2->Release();
		m_pD3DIndexBuff2 = NULL;
	}

}

//***************************************************************
//	更新
//***************************************************************
void	CSky::Update()
{
	m_Vertex_3d.Rot_vtx.y += 0.001f;
}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//***************************************************************
void	CSky::Draw(LPDIRECT3DDEVICE9 pDevice)
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
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

	//合成
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

	//角度設定
	D3DXMatrixRotationYawPitchRoll(&mRotate, m_Vertex_3d.Rot_vtx.y,0.0f, D3DXToRadian(m_Vertex_3d.Rot_vtx.x));

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
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
											0,
											0,
											(UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y),
											0,
											(int)((m_Vertex_3d.vertex.x) * (m_Vertex_3d.vertex.y) * 3) );

	//バッファ指定
	pDevice->SetStreamSource(0,m_pD3DVtxBuff2,0,sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pD3DIndexBuff2);

			//画像表示
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,
											0,
											0,
											(UINT)m_Vertex_3d.vertex.x + 3,
											0,
											(int)((m_Vertex_3d.vertex.x) + 3) );

}
