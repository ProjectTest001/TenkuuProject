//***************************************************************
//
//	scene2d.cpp
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
#include	"scene2d.h"
#include	"fade.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
int	CFade::m_status = NONE;

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
CFade::CFade(int	nPriority):CScene(nPriority)
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CFade::~CFade()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//戻り値：
//HRESULT	終了コード
//***************************************************************
HRESULT	CFade::Init(LPDIRECT3DDEVICE9 pDevice,int	TexNo)
{
	//初期化
	m_Vertex_2d.vtx = D3DXVECTOR3(-SCREEN_WIDTH,0.0f,0.0f);
	m_status = NONE;
	m_nTex = TexNo;

			//バッファ設定
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_2D)) * 4,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}


				//アンロック変数
				VERTEX_2D	*pv;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//画像の初期化の流れ
						//座標x,y,z
						pv[0].vtx = D3DXVECTOR3(-SCREEN_WIDTH, 0, 0.0f);
						pv[1].vtx = D3DXVECTOR3(0, 0,0.0f);
						pv[2].vtx = D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f);
						pv[3].vtx = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);

						//バースの補正値
						pv[0].rhw = 
						pv[1].rhw = 
						pv[2].rhw = 
						pv[3].rhw = 1.0f;

						//頂点色(赤、緑、青）
						pv[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

						// テクスチャＵＶ
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0fで左上指定
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0fで右上指定
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0fで左下指定
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0fで右下指定

					//ロック
					m_pD3DVtxBuff->Unlock();

	return	S_OK;
}

//***************************************************************
//	フェードの切り替え関数
//
//***************************************************************
void	CFade::Start(CFade::STATUS status, int Time)
{
	m_status = status;

}
//***************************************************************
//	終了
//***************************************************************
void	CFade::Uninit()
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
void	CFade::Update()
{
	switch(m_status)
	{
	case	FADEIN:
		m_Vertex_2d.vtx.x += 11.5f;

		if(m_Vertex_2d.vtx.x >SCREEN_WIDTH)
		{
			m_Vertex_2d.vtx.x = SCREEN_WIDTH;
			m_status = FADEIN_END;
		}

		break;
	case	FADEIN_END:

		break;
	case	FADEOUT:
		m_Vertex_2d.vtx.x += 110.5f;

		if(m_Vertex_2d.vtx.x >SCREEN_WIDTH * 2)
		{
			m_Vertex_2d.vtx.x = 0;
			m_status = FADEOUT_END;
		}

		break;
	case	FADEOUT_END:
		m_status = NONE;
		break;
	}

}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//***************************************************************
void	CFade::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//アンロック変数
	VERTEX_2D	*pv;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//画像の初期化の流れ
						//座標x,y,z
					pv[0].vtx = D3DXVECTOR3(-SCREEN_WIDTH + m_Vertex_2d.vtx.x, 0, 0.0f);
					pv[1].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, 0,0.0f);
					pv[2].vtx = D3DXVECTOR3(-SCREEN_WIDTH + m_Vertex_2d.vtx.x, SCREEN_HEIGHT,0.0f);
						pv[3].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x,SCREEN_HEIGHT,0.0f);

						m_pD3DVtxBuff->Unlock();

		//フォーマットの指定
		pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャ設定
			pDevice->SetTexture(0,
				Texture);

			//頂点バッファの送信
			pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_2D));

			//画像表示
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);




}
