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
#include	"renderer.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"field.h"
#include	"camera.h"
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
CScene3d::CScene3d()
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CScene3d::~CScene3d()
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
HRESULT	CScene3d::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo)
{

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
CScene3d	*CScene3d::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo)
{
	//ポインタ宣言
	CScene3d	*pScene3d;

	//クラス生成
	pScene3d = new	CScene3d;

	//初期化
	pScene3d->Init(pDevice, vtx, color,TexNo);

	return	pScene3d;
}

//***************************************************************
//	終了
//***************************************************************
void	CScene3d::Uninit()
{

	//解放処理
	//バッファ解放
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

}

//***************************************************************
//	更新
//***************************************************************
void	CScene3d::Update()
{

}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//***************************************************************
void	CScene3d::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mScale,mRotate;		//左から座標、大きさ、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//大きさ設定
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

	//合成
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

	//角度設定
	D3DXMatrixRotationYawPitchRoll(&mRotate, 0.0f, D3DXToRadian(0.0f), 0.0f);

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

		//フォーマットの指定
		pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0,
				Texture);

			//画像表示
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}


//***************************************************************
//	地面の高さの取得
//	引数
//	D3DXVECTOR3	pos:対象の位置
//	戻り値
//	float：送る高さ
//***************************************************************
float	CScene3d::GetHeight(D3DXVECTOR3 pos)
{
	int	camera = CCamera::GetCameraMode();

	if(camera != CCamera::PLAYER_CAMERA)
	{
		return	0;
	}
	//地面情報取得
	VERTEX_3D	pField = CField::GetVertex();
	
	//計算結果を納める変数
	float	fHeight = pos.y;

	for(int	z = 0 ; z <  pField.vertex.z - 1.0f ; z++)
	{
		for(int	x = 0 ; x <  pField.vertex.x - 1.0f; x++)
		{
			int	nCount_i = z * (int)pField.vertex.x + x;

			//ベクトル変数宣言
			const	D3DXVECTOR3	aVtx[4] = 
			{
				pField.DataVtx[x + (int)pField.vertex.x * (z + 1)],			//左下
				pField.DataVtx[x + (int)pField.vertex.x * z],				//左上
				pField.DataVtx[x + (int)pField.vertex.x * (z + 1) + 1],		//右下
				pField.DataVtx[x + (int)pField.vertex.x * z + 1],			//右上
			};

			D3DXVECTOR3	vec0;
			D3DXVECTOR3	vec1;
			int	Count = 0;

			for(int	nCnt = 0; nCnt < 3 ; nCnt++)
			{
					//ベクトル変数
					vec0 = aVtx[(int)(nCnt + 1) % 3 + 1] - aVtx[nCnt + 1];
					vec1 = pos - aVtx[nCnt + 1];

					//右側の面
				if((vec0.z * vec1.x - vec0.x * vec1.z) <= 0 )
				{
					Count++;
					if(Count > 2)
					{
						fHeight = GetHeightPolygon(pos,aVtx[1],aVtx[3],aVtx[2]);
						return	fHeight;
					}
				}
			}

			Count = 0;

			for(int	nCnt = 0; nCnt < 3 ; nCnt++)
			{
					//ベクトル変数
					vec0 = aVtx[nCnt] - aVtx[(int)(nCnt + 1) % 3];
					vec1 = pos - aVtx[(int)(nCnt + 1) % 3];

					//左側の面
				if((vec0.z * vec1.x - vec0.x * vec1.z) <= 0 )
				{
					Count++;
					if(Count > 2)
					{
						fHeight = GetHeightPolygon(pos,aVtx[0],aVtx[1],aVtx[2]);
						return	fHeight;
					}
				}
			}

		}
	}
	//内積計算
//pos.y = m_Vertex_3d.vtx.y - pos.x + m_Vertex_3d.vtx.x - pos.z + m_Vertex_3d.vtx.z;
	return	fHeight;
}

//*
//
//*
float	CScene3d::GetHeightPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2)
{
	float	fHeight = 0.0f;
	D3DXVECTOR3	vec0;
	D3DXVECTOR3	vec1;
	D3DXVECTOR3	nor;

	vec0 = vtx0 - vtx1;
	vec1 = vtx0 - vtx2;

	nor.x = vec0.y * vec1.z - vec0.z * vec1.y;
	nor.y = vec0.z * vec1.x - vec0.x * vec1.z;
	nor.z = vec0.x * vec1.y - vec0.y * vec1.x;

	fHeight = vtx0.y - (( nor.x * pos.x - nor.x * vtx0.x + nor.z * pos.z - nor.z * vtx0.z  ) / nor.y);
	return	fHeight;
}