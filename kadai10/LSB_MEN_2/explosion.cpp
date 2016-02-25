//***************************************************************
//
//	scenebillboard.cpp
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
#include	"scenebillboard.h"
#include	"camera.h"
#include	"manager.h"
#include	"explosion.h"
#include	"texture.h"

//***************************************************************
//	クラス関数
//***************************************************************
int	span = 5;
//***************************************************************
//	コンストラクタ
//	引数
//	無し
//	戻り値
//	なし
//***************************************************************
CExplosion::CExplosion(int	nPriority):CSceneBillboard(nPriority)
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CExplosion::~CExplosion()
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
HRESULT	CExplosion::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,int	TexNo)
{
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

				//アンロック変数
				VERTEX_3D	*pv;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//画像の初期化の流れ
						//座標x,y,z
						pv[0].vtx = D3DXVECTOR3(-1.5f, 1.5f, 0.0f);
						pv[1].vtx = D3DXVECTOR3(1.5f, 1.5f,0.0f);
						pv[2].vtx = D3DXVECTOR3(-1.5f, -1.5f, 0.0f);
						pv[3].vtx = D3DXVECTOR3(1.5f,-1.5f , 0.0f);

						//法線
						pv[0].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[1].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[2].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[3].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);


						//頂点色(赤、緑、青）
						pv[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

						// テクスチャＵＶ
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0fで左上指定
						pv[1].tex = D3DXVECTOR2(0.1f,0.0f);		//1.0f,0.0fで右上指定
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0fで左下指定
						pv[3].tex = D3DXVECTOR2(0.1f,1.0f);		//1.0f,1.0fで右下指定

					//ロック
					m_pD3DVtxBuff->Unlock();

					//数値初期化
					m_Vertex_3d.vtx = vtx;
					m_Time = 0.0f;

					//その他初期化
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	ポリゴン生成
//引数：
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//戻り値
//CExplosion	元クラス
//***************************************************************
CExplosion	*CExplosion::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo)
{
	//ポインタ宣言
	CExplosion	*pExplosion;

	//クラス生成
	pExplosion = new	CExplosion;

	//初期化
	pExplosion->Init(pDevice,vtx,TexNo);

	return	pExplosion;
}

//***************************************************************
//	終了
//***************************************************************
void	CExplosion::Uninit()
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
void	CExplosion::Update()
{
	if(span < 0 )
	{
		if(m_Time > 0.9f)
		{
			CExplosion::Uninit();
			CScene::Release();
		}
		else
		{
			m_Time += 0.1f;
		}
		span = 1;
	}
	else
	{
		span--;
	}
}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//***************************************************************
void	CExplosion::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	
	//マトリックス変数宣言
	D3DXMATRIX	mTrans;		//座標

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//カメラ関係変数宣言
	D3DXMATRIX	mtxView;
	CCamera	*pCamera;

	//カメラ情報取得
	pCamera = CManager::GetCamera();
	mtxView = pCamera->GetViewMatrix();

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//アンロック変数
	VERTEX_3D	*pv;

	//ロック解除
	m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

		// テクスチャＵＶ
		pv[0].tex = D3DXVECTOR2(m_Time,0.0f);				
		pv[1].tex = D3DXVECTOR2(m_Time + 0.1f,0.0f);		
		pv[2].tex = D3DXVECTOR2(m_Time,1.0f);			
		pv[3].tex = D3DXVECTOR2(m_Time + 0.1f,1.0f);	

	m_pD3DVtxBuff->Unlock();

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビルボード設定
	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		//インバース
		D3DXMatrixInverse(&matViewInv,NULL,&matViewInv);

		//合成
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&matViewInv);

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
