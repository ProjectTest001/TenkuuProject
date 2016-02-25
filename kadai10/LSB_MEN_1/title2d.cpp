//***************************************************************
//
//	title2d.cpp
//	name:Masatugu Kamada
//	create:2012/10/20
//	update：2012/10/20
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
#include	"title2d.h"
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
CTitle2d::CTitle2d()
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CTitle2d::~CTitle2d()
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
HRESULT	CTitle2d::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
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
CTitle2d	*CTitle2d::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
{
	//ポインタ宣言
	CTitle2d	*pScene2d;

	//クラス生成
	pScene2d = new	CTitle2d;

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
void	CTitle2d::Uninit()
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
void	CTitle2d::Update()
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

		//色の変化用変数（今は１種類の変化要素の為、宣言と同時に計算）
		float	r = (float)(rand()%10 + 1) / 10;
		float	g = (float)(rand()%10 + 1) / 10;
		float	b = (float)(rand()%10 + 1) / 10;
		float	a = (float)(rand()%10 + 1) / 10;

	//描画の種類によって各自処理
	switch(m_nType)
	{
		//何も動かないタイプ
		case	NONE:
		//色彩変化
		m_Vertex_2d.diffuse = D3DXCOLOR(r,g,b,a);
		break;

		//一定の移動のタイプ
		case	 MOVE_TYPE:
		m_Vertex_2d.vtx.x -= 2.5f;

		if(m_Vertex_2d.vtx.x < -m_Vertex_2d.Scail.x)
		{
			m_Vertex_2d.vtx.x = SCREEN_WIDTH + m_Vertex_2d.Scail.x * 2;
		}
		break;

		//入力処理によって移動するタイプ
		case	MOVE_KEY:
		//色彩変化
		m_Vertex_2d.diffuse = D3DXCOLOR(r,g,1,1);

		//移動
		if(pKeyBoard->GetkeyboardPress(DIK_LEFT))
		{
			m_Vertex_2d.vtx.x -= 5.05f;
		}
		if(pKeyBoard->GetkeyboardPress(DIK_UP))
		{
			m_Vertex_2d.vtx.y -= 5.05f;
		}
		if(pKeyBoard->GetkeyboardPress(DIK_DOWN))
		{
			m_Vertex_2d.vtx.y += 5.05f;
		}
		if(pKeyBoard->GetkeyboardPress(DIK_RIGHT))
		{
			m_Vertex_2d.vtx.x += 5.05f;
		}
		break;

		//一回の入力で移動するタイプ
		case	MOVE_TUTORIAL:
		if(pKeyBoard->GetkeyboardPress(DIK_T))
		{
			if(!bmove)
			{
				bmove = true;
			}
		}

		if(bmove)
		{
			if(m_Vertex_2d.vtx.x < 0)
			{
				m_Vertex_2d.vtx.x += 5.05f;
			}
			else
			{
				m_Vertex_2d.vtx.x = 0;
				bmove = false;
			}
		}
		break;
	}

}
//***************************************************************
//	描画
//	引数：
//	LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//	戻り値：
//	なし
//***************************************************************
void	CTitle2d::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

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

