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
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"manager.h"
#include	"scene.h"
#include	"scene2d.h"
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
CScene2d::CScene2d(int	nPriority):CScene(nPriority)
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CScene2d::~CScene2d()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//D3DXVECTOR3	vtx:描画位置
//D3DXVECTOR2	Scail:大きさ
//const	char*Name:ファイル名
//int	Type:描画の種類
//戻り値：
//HRESULT	終了コード
//***************************************************************
HRESULT	CScene2d::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
{
	//初期化
	m_Vertex_2d.vtx = vtx;									//座標
	m_Vertex_2d.Scail = Scail;								//大きさ
	m_nType = Type;											//描画の種類
	m_Vertex_2d.diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);	//色
	bmove = false;											//移動フラグ
	//m_Vertex_2d.rhw = 1.0f;

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
					pv[0].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y, 0.0f);
					pv[1].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x, m_Vertex_2d.vtx.y,0.0f);
						pv[2].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);
						pv[3].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x,m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);

						//バースの補正値
						pv[0].rhw = 
						pv[1].rhw = 
						pv[2].rhw = 
						pv[3].rhw = 1.0f;

						//頂点色(赤、緑、青）
						pv[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
						pv[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
						pv[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
						pv[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);

						// テクスチャＵＶ
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0fで左上指定
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0fで右上指定
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0fで左下指定
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0fで右下指定

					//ロック
					m_pD3DVtxBuff->Unlock();

					//その他初期化
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	ポリゴン生成
//引数
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//D3DXVECTOR3	vtx:描画位置
//D3DXVECTOR2	Scail:大きさ
//const	char*Name:ファイル名
//int	Type:描画の種類
//戻り値
//CScene2d：元クラス
//***************************************************************
CScene2d	*CScene2d::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
{
	//ポインタ宣言
	CScene2d	*pScene2d;

	//クラス生成
	pScene2d = new	CScene2d;

	//初期化
	pScene2d->Init(pDevice,vtx,Scail,Type,TexNo);

	return	pScene2d;

}

//***************************************************************
//	終了
//	引数：
//	なし
//	戻り値：
//	なし
//***************************************************************
void	CScene2d::Uninit()
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
//	引数：
//	なし
//	戻り値：
//	なし
//***************************************************************
void	CScene2d::Update()
{

}
//***************************************************************
//	描画
//	引数：
//	LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//	戻り値：
//	なし
//***************************************************************
void	CScene2d::Draw(LPDIRECT3DDEVICE9 pDevice)
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
					pv[0].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y, 0.0f);
					pv[1].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x, m_Vertex_2d.vtx.y,0.0f);
					pv[2].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);
					pv[3].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x,m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);

						//頂点色(赤、緑、青）
					pv[0].diffuse = m_Vertex_2d.diffuse;
					pv[1].diffuse = m_Vertex_2d.diffuse;
					pv[2].diffuse = m_Vertex_2d.diffuse;
					pv[3].diffuse = m_Vertex_2d.diffuse;

	//ロック
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
