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
#include	"scene.h"
#include	"scene3d.h"
#include	"wall.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"field.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
bool	CWall::m_bHit = false;

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
CWall::CWall()
{
	//初期化
	m_pD3DVtxBuff = NULL;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CWall::~CWall()
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
HRESULT	CWall::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Rot,
					float	width,float	heght,int	cutX,int	cutY,int	TexNo)
{
	//数値初期化
	m_Vertex_3d.vtx = vtx;						//座標
	m_Vertex_3d.diffuse = color;				//配色
	m_Vertex_3d.Rot_vtx = Rot;					//回転角度
	m_Vertex_3d.vertex.x = (float)cutX + 1.0f;	//Ｘ座標の分割数（＋１は頂点数の補完）
	m_Vertex_3d.vertex.y = (float)cutY + 1.0f;	//Ｙ座標の分割数（＋１は頂点数の補完）
	m_Vertex_3d.Scail_vtx.x = width;			//幅
	m_Vertex_3d.Scail_vtx.y = heght;			//高さ
	m_nTex = TexNo;

	//インデックス数
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) + (m_Vertex_3d.vertex.y - (m_Vertex_3d.vertex.y * 2 / 3) )) * 2;

			//バッファ設定
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y),
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

				//画像の初期化の流れ
				int	yCount = 0;
				int	xCount = 0;

				//各頂点座標書き込み
				for(int	y = 0 ; y < (int)m_Vertex_3d.vertex.y ; y++)
				{
					for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x ;x++)
					{
						int	nCount_i = yCount * (int)m_Vertex_3d.vertex.x + xCount;
						pv[nCount_i].vtx.x = (m_Vertex_3d.Scail_vtx.x / (-2)) + (m_Vertex_3d.Scail_vtx.x / (m_Vertex_3d.vertex.x - 1)) * (float)x;
						pv[nCount_i].vtx.y = m_Vertex_3d.Scail_vtx.y - (m_Vertex_3d.Scail_vtx.y / (m_Vertex_3d.vertex.y - 1)) * (float)y;
						pv[nCount_i].tex.x = (float)xCount;
						pv[nCount_i].tex.y = (float)yCount;
						pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
						pv[nCount_i].hor = D3DXVECTOR3(0.0f,0.0f,-1.0f) + pv[nCount_i].vtx;
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
					pi[n] = (a + 1) + (WORD)m_Vertex_3d.vertex.x;
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
				if(gz != (int)m_Vertex_3d.vertex.y  - 1)
				{
					pi[n] = a;
					n++;
				}
			}
					//ロック
					m_pD3DIndexBuff->Unlock();

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
CWall	*CWall::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Rot,
					   float	width,float	heght,int	cutX,int	cutY,int	TexNo)
{
	//ポインタ宣言
	CWall	*pWall;

	//クラス生成
	pWall = new	CWall;

	//初期化
	pWall->Init(pDevice, vtx, color,Rot,width,heght,cutX,cutY,TexNo);

	return	pWall;
}

//***************************************************************
//	終了
//***************************************************************
void	CWall::Uninit()
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

}

//***************************************************************
//	更新
//***************************************************************
void	CWall::Update()
{
	
}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//***************************************************************
void	CWall::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D	pField = CField::GetVertex();
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
	D3DXMatrixRotationYawPitchRoll(&mRotate, D3DXToRadian(m_Vertex_3d.Rot_vtx.y + pField.Rot_vtx.y),
												D3DXToRadian(m_Vertex_3d.Rot_vtx.x + pField.Rot_vtx.x),
												D3DXToRadian(m_Vertex_3d.Rot_vtx.z + pField.Rot_vtx.z));

	//合成
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

	//座標設定
	D3DXMatrixTranslation(&mTrans, sinf(D3DXToRadian(m_Vertex_3d.Rot_vtx.y + pField.Rot_vtx.y)) * (m_Vertex_3d.vtx.x + (pField.Scail_vtx.x / 2)),
									m_Vertex_3d.vtx.y,
									cosf(D3DXToRadian(m_Vertex_3d.Rot_vtx.y + pField.Rot_vtx.y)) * (m_Vertex_3d.vtx.z + (pField.Scail_vtx.z / 2)));

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
											(int)((m_Vertex_3d.vertex.x) * (m_Vertex_3d.vertex.y) * 2) );
}

