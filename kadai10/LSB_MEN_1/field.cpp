//***************************************************************
//
//	field.cpp
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
#include	"field.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
VERTEX_3D	CField::m_Vertex_3d;

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
CField::CField()
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CField::~CField()
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
HRESULT	CField::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
					 D3DXVECTOR3	Rot,float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo)
{
	//数値初期化
	m_Vertex_3d.vtx = vtx;							//座標
	m_Vertex_3d.diffuse = color;
	m_Vertex_3d.Rot_vtx = Rot;
	m_Vertex_3d.Scail_vtx.x = Xwidth;
	m_Vertex_3d.Scail_vtx.z = Zwidth;
	m_Vertex_3d.vertex.x = (float)cutX + 1.0f;
	m_Vertex_3d.vertex.z = (float)cutZ + 1.0f;
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z) + (m_Vertex_3d.vertex.z - (m_Vertex_3d.vertex.z * 2 / 3) )) * 2;
	m_nTex = TexNo;

	//今回の課題の山をつける為の変数
	float	mountion[17 * 17] = {
			21.0f,20.5f,15.0f,7.0f ,5.0f ,0.0f ,1.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,4.0f ,3.0f ,
			20.5f,20.5f,15.0f,7.0f ,5.0f ,0.0f ,1.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,4.0f ,4.0f ,
			15.0f,15.0f,13.0f,7.0f ,5.0f ,0.0f ,1.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,2.0f ,2.0f ,
			10.0f,10.0f,11.0f,5.0f ,0.0f ,1.0f ,4.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,10.0f,
			5.0f ,5.0f ,5.0f ,5.0f ,0.0f ,1.0f ,4.0f ,3.0f ,2.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,11.0f,13.0f,
			0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,4.0f ,4.0f ,3.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,11.0f,13.0f,
			1.0f ,1.0f ,1.0f ,1.0f ,4.0f ,4.0f ,3.0f ,4.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,-10.0f,11.0f,12.0f,
			3.0f ,4.0f ,4.0f ,4.0f ,4.0f ,3.0f ,4.0f ,6.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,
			1.0f ,2.0f ,3.0f ,3.0f ,3.0f ,0.0f ,6.0f ,8.0f ,6.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,
			1.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,6.0f ,1.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,8.0f ,8.0f ,
			1.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,2.0f ,6.0f ,2.5f ,10.0f,10.0f,10.0f,6.0f ,6.0f ,
			1.0f ,2.0f ,3.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,6.0f ,8.0f ,2.5f ,3.0f ,10.0f,10.0f,3.0f ,3.0f ,
			1.0f ,2.0f ,5.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,3.0f ,6.0f ,0.7f ,3.0f ,10.0f,10.0f,1.0f ,1.0f ,
			1.0f ,2.0f ,5.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,3.0f ,1.0f ,3.0f ,10.0f,10.0f,0.0f ,0.0f ,
			1.0f ,2.0f ,1.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,0.0f ,3.0f ,14.0f,14.0f,0.0f ,0.0f ,
			0.0f ,0.0f ,0.0f ,3.0f ,3.0f ,3.0f ,2.0f ,1.0f ,0.0f ,0.0f ,0.0f ,0.0f ,3.0f ,3.0f ,3.0f ,0.0f ,0.0f ,
			0.0f ,0.0f ,0.0f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.5f ,0.0f ,0.0f ,0.0f ,0.0f ,};

			//バッファ設定
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z),
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

			m_Vertex_3d.DataVtx = new	D3DXVECTOR3[(int)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z)];

				//アンロック変数
				VERTEX_3D	*pv;
				WORD	*pi;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//画像の初期化の流れ
				int	zCount = 0;
				int	xCount = 0;

			//各頂点座標書き込み
			for(int	z = 0; z < (int)m_Vertex_3d.vertex.z ; z++)
			{
				for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x ; x++)
				{
					int	nCount_i = zCount * (int)m_Vertex_3d.vertex.x + xCount;
					pv[nCount_i].vtx.x = (m_Vertex_3d.Scail_vtx.x / (-2)) + (m_Vertex_3d.Scail_vtx.x / (m_Vertex_3d.vertex.x - 1.0f)) * (float)x;
					pv[nCount_i].vtx.y = mountion[nCount_i];
					pv[nCount_i].vtx.z = (m_Vertex_3d.Scail_vtx.z / 2) - (m_Vertex_3d.Scail_vtx.z / (m_Vertex_3d.vertex.z - 1.0f)) * (float)z;
					m_Vertex_3d.DataVtx[nCount_i] = pv[nCount_i].vtx;
					pv[nCount_i].tex.x = (float)xCount;
					pv[nCount_i].tex.y = (float)zCount;
					pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
					xCount++;
				}
				zCount++;
				xCount = 0;
			}

			//ベクトル計算用変数
			D3DXVECTOR3	vec0;
			D3DXVECTOR3	vec1;

			//法線の面数分確保
			m_pNormalBuff = new	D3DXVECTOR3[cutX * cutZ * 2];

			//法線の設定
			for(int	z = 0; z < cutZ ; z++)
			{
				for(int	x = 0; x < cutX;x++)
				{
					int	nCount_i = z * cutX + x;

						//左側の面
						vec0 = pv[x + (int)m_Vertex_3d.vertex.x * z].vtx - pv[x + (int)m_Vertex_3d.vertex.x * (z + 1)].vtx;
						vec1 = pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx - pv[x + (int)m_Vertex_3d.vertex.x * z].vtx;
						m_pNormalBuff[nCount_i * 2].x = vec0.y * vec1.z - vec0.z * vec1.y;
						m_pNormalBuff[nCount_i * 2].y = vec0.z * vec1.x - vec0.x * vec1.z;
						m_pNormalBuff[nCount_i * 2].z = vec0.x * vec1.y - vec0.y * vec1.x;

						//右側の面
						vec0 = pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx - pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx;
						vec1 = pv[x + (int)m_Vertex_3d.vertex.x * z].vtx - pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx;
						m_pNormalBuff[nCount_i * 2 + 1].x = vec0.y * vec1.z - vec0.z * vec1.y;
						m_pNormalBuff[nCount_i * 2 + 1].y = vec0.z * vec1.x - vec0.x * vec1.z;
						m_pNormalBuff[nCount_i * 2 + 1].z = vec0.x * vec1.y - vec0.y * vec1.x;

				}
			}


			int	Xcut = cutX;
			int	Zcut = cutZ;

			for(int	z = 0; z < m_Vertex_3d.vertex.z ; z++)
			{
				for(int	x = 0; x < m_Vertex_3d.vertex.x; x++)
				{
					int	nCount_i = z * (int)m_Vertex_3d.vertex.x + x;
					if(z == 0)
					{
						//左奥の場合
						if(x == 0)
						{
							pv[nCount_i].hor = (m_pNormalBuff[0] + m_pNormalBuff[1]) / 2;
						}
						//右奥の場合
						else	if(x == cutX)
						{
							pv[nCount_i].hor = m_pNormalBuff[Xcut * 2 - 1];
						}
						//最奥側の場合
						else
						{
								pv[nCount_i].hor = (m_pNormalBuff[(x * 2) - 1] + 
													m_pNormalBuff[(x * 2)] + 
													m_pNormalBuff[(x * 2) + 1]) / 3;
						}
					}
					else	if(z == cutZ)
					{
						//左手前の場合
						if(x == 0)
						{
							pv[nCount_i].hor = m_pNormalBuff[Xcut * 2 * (z - 1)];
						}
						//右手前の場合
						else	if(x == (m_Vertex_3d.vertex.x - 1))
						{
							pv[nCount_i].hor = (m_pNormalBuff[Xcut * Zcut * 2 - 1] + 
												m_pNormalBuff[Xcut * Zcut * 2 - 2]) / 2;
						}
						//最手前の場合
						else
						{
							pv[nCount_i].hor = (m_pNormalBuff[((x * 2) - 2) + (Zcut * 2 * (z - 1))] +
												m_pNormalBuff[((x * 2) - 1) +(Zcut * 2 * (z - 1) )] + 
												m_pNormalBuff[(x * 2) + (Zcut * 2 * (z - 1))]) / 3;
						}
					}
					else
					{
						//左端の場合
						if(x == 0)
						{
							pv[nCount_i].hor = (m_pNormalBuff[(Xcut * 2) * z] +
												m_pNormalBuff[(Xcut * 2) * z + 1] + 
												m_pNormalBuff[(Xcut * 2) * (z - 1)]) / 3;
						}
						//右端の場合
						else	if(x == cutX)
						{
							pv[nCount_i].hor = (m_pNormalBuff[(Xcut * 2 * z) - 1] +
												m_pNormalBuff[(Xcut * 2 * z) - 2] + 
												m_pNormalBuff[(Xcut * 2 ) * (z + 1) - 1] ) / 3;
						}
						//上記全てに属さない場合
						else
						{
							pv[nCount_i].hor = (m_pNormalBuff[(x * 2 - 2) + ((z -1) * Xcut * 2)] +
												m_pNormalBuff[(x * 2 - 1) + ((z -1) * Xcut * 2)] + 
												m_pNormalBuff[(x * 2) + ((z -1) * Xcut * 2)] + 
												m_pNormalBuff[(x * 2 - 1) + (z * Xcut * 2)] + 
												m_pNormalBuff[(x * 2) + (z * Xcut * 2)] + 
												m_pNormalBuff[(x * 2 + 1) + (z * Xcut * 2)]) / 6;
						}
					}
					//正規化
					D3DXVec3Normalize(&pv[nCount_i].hor,&pv[nCount_i].hor);
					nCount_i++;
				}
			}

					//ロック
					m_pD3DVtxBuff->Unlock();

					//インデックスバッファのアンロック
					m_pD3DIndexBuff->Lock(0,0,(void**)&pi,0);

									//インデックス書き込み用変数宣言
				int	n = 0;	//Ｎｕｍ変数
				int	a;		//ナンバー設定変数


				//インデックス設定
	for(int	gz = 0; gz < (int)m_Vertex_3d.vertex.z  - 1 ;gz++)
	{
		//最初はスルー
		if(n != 0)
		{
			pi[n] = (a + 1) + (int)m_Vertex_3d.vertex.x ;
			n++;
		}
			for(int	gx = 0; gx < (int)m_Vertex_3d.vertex.x  ;gx++)
			{
					a = gz * (int)m_Vertex_3d.vertex.x  + gx;

				pi[n+0] = a + (int)m_Vertex_3d.vertex.x ;
				pi[n+1] = a;
				n += 2;
			}

		//最後はスルー
		if(gz != (int)m_Vertex_3d.vertex.z  - 1)
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
//戻り値
//CScene3d	元クラス
//***************************************************************
CField	*CField::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Rot,
						float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo)
{
	//ポインタ宣言
	CField	*pField;

	//クラス生成
	pField = new	CField;

	//初期化
	pField->Init(pDevice, vtx, color,Rot,Xwidth,Zwidth,cutX,cutZ,TexNo);

	return	pField;
}

//***************************************************************
//	終了
//***************************************************************
void	CField::Uninit()
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

	//座標情報の解放
	if(m_Vertex_3d.DataVtx != NULL)
	{
		delete	m_Vertex_3d.DataVtx;
		m_Vertex_3d.DataVtx = NULL;
	}

}

//***************************************************************
//	更新
//***************************************************************
void	CField::Update()
{

}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//***************************************************************
void	CField::Draw(LPDIRECT3DDEVICE9 pDevice)
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
	D3DXMatrixRotationYawPitchRoll(&mRotate, D3DXToRadian(m_Vertex_3d.Rot_vtx.y), D3DXToRadian(m_Vertex_3d.Rot_vtx.x), D3DXToRadian(m_Vertex_3d.Rot_vtx.z));

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
											(UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z),
											0,
											(int)((m_Vertex_3d.vertex.x) * (m_Vertex_3d.vertex.z) * 2) );


}
