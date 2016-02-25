//***************************************************************
//
//	number.cpp
//	name:Masatugu Kamada
//	更新日：2012/07/03
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
#include	"number.h"
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
CNumber::CNumber(int	nPriority)
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CNumber::~CNumber()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//戻り値：
//HRESULT	終了コード
//***************************************************************
HRESULT	CNumber::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo)
{
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
						pv[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, 0.0f);
						pv[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y,0.0f);
						pv[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + heght,0.0f);
						pv[3].vtx = D3DXVECTOR3(vtx.x + width,vtx.y + heght,0.0f);

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
						pv[1].tex = D3DXVECTOR2(0.0625f,0.0f);		//1.0f,0.0fで右上指定
						pv[2].tex = D3DXVECTOR2(0.0f,0.125f);		//0.0f,1.0fで左下指定
						pv[3].tex = D3DXVECTOR2(0.0625f,0.125f);		//1.0f,1.0fで右下指定

					//ロック
					m_pD3DVtxBuff->Unlock();

					//その他初期化
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	ポリゴン生成
//引数
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//戻り値
//CScene2d：元クラス
//***************************************************************
CNumber	*CNumber::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo)
{
	//ポインタ宣言
	CNumber	*pNumber;

	//クラス生成
	pNumber = new	CNumber;

	//初期化
	pNumber->Init(pDevice,vtx,width,heght,TexNo);

	return	pNumber;

}

//***************************************************************
//	終了
//***************************************************************
void	CNumber::Uninit()
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
void	CNumber::Update()
{

}

//***************************************************************
//	数字のセット
//***************************************************************
void	CNumber::SetNumber(int	nNumber)
{
	float	fNumber = (float)nNumber * 0.0625f;

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//アンロック変数
	VERTEX_2D	*pv;

		//ロック解除
		m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

			// テクスチャＵＶ
			pv[0].tex = D3DXVECTOR2(fNumber,0.0f);		//0.0f,0.0fで左上指定
			pv[1].tex = D3DXVECTOR2(fNumber + 0.0625f,0.0f);		//1.0f,0.0fで右上指定
			pv[2].tex = D3DXVECTOR2(fNumber,0.125f);		//0.0f,1.0fで左下指定
			pv[3].tex = D3DXVECTOR2(fNumber + 0.0625f,0.125f);		//1.0f,1.0fで右下指定

	//ロック
	m_pD3DVtxBuff->Unlock();

}

//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//***************************************************************
void	CNumber::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

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
