//***************************************************************
//
//	renderer.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/19
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
#include	"camera.h"
#include	"number.h"

//***************************************************************
//	クラス関数
//***************************************************************
LPDIRECT3DDEVICE9	CRenderer::m_D3DDevice = NULL;
int	CRenderer::m_nType = NOMAL;
//***************************************************************
//	インストラクタ
//***************************************************************
CRenderer::CRenderer()
{
	//初期化
	m_pD3D = NULL;
	m_D3DDevice = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CRenderer::~CRenderer()
{

}

//***************************************************************
//	初期化
//***************************************************************
HRESULT	CRenderer::Init(HWND hWindow, BOOL bwindow)
{
	//初期化
	m_pD3D = Direct3DCreate9(
				D3D_SDK_VERSION);
	//読み込みに失敗した場合
	if(m_pD3D == NULL)
	{
		return	E_FAIL;
	}
	//表示設定
	D3DDISPLAYMODE	dm;
	D3DPRESENT_PARAMETERS	pp;

	//displaymode 確認
	if(FAILED( m_pD3D->GetAdapterDisplayMode(
						D3DADAPTER_DEFAULT,&dm) ))
	{
		return	E_FAIL;
	}
	//各種表示設定
	ZeroMemory(&pp,sizeof(pp));
	// 0 clear
	pp.BackBufferCount = 1;		//裏画面の設定
	pp.BackBufferWidth = SCREEN_WIDTH;		//幅設定
	pp.BackBufferHeight = SCREEN_HEIGHT;		//高さ設定

	//画面切り替え時の指定
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = bwindow;		//window mode

	// 深度バッファ
	pp.EnableAutoDepthStencil = true;
	// 16bit 使う
	pp.AutoDepthStencilFormat = D3DFMT_D16;

	//全画面モード（ＯＦＦの場合）
	if(bwindow)
	{
		pp.BackBufferFormat = D3DFMT_UNKNOWN;
		// 全画面のときの切り替えタイミング
		pp.FullScreen_RefreshRateInHz = 0;
		pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	}
	//全画面モード（ＯＮの場合）
	else
	{
		pp.BackBufferFormat = D3DFMT_R5G6B5;
		// 全画面のときの切り替えタイミング
		pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	}

	//表示装置作成
	if(FAILED( m_pD3D->CreateDevice(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,			//hardware
						hWindow,				//リンクするwindow
						D3DCREATE_HARDWARE_VERTEXPROCESSING,	//頂点処理hardware
						&pp,					//表示設定
						&m_D3DDevice) ))				//表示装置（ｏｕｔ）
	{
		if(FAILED( m_pD3D->CreateDevice(
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,			//hardware
							hWindow,				//リンクするwindow
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//頂点処理software
							&pp,					//表示設定
							&m_D3DDevice) ))				//表示装置（ｏｕｔ）
		{
			if(FAILED( m_pD3D->CreateDevice(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_REF,			//hardware
								hWindow,				//リンクするwindow
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//頂点処理software
								&pp,					//表示設定
								&m_D3DDevice) ))				//表示装置（ｏｕｔ）
			{
				MessageBox(NULL,"デバイスエラー",
						"エラー",MB_OK);
				return	E_FAIL;
			}
		}
	}

	//描画設定
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

	//カリング（陰面処理）しない
	m_D3DDevice->SetRenderState(D3DRS_ZENABLE,true);

	// Z buffer(深度バッファ）有効
	//半透明の指定
	m_D3DDevice->SetRenderState(
					D3DRS_CULLMODE,D3DCULL_CCW);
	m_D3DDevice->SetRenderState(
					D3DRS_ZENABLE,
						D3DCULL_NONE);
	m_D3DDevice->SetRenderState(
					D3DRS_ALPHABLENDENABLE,true);
	m_D3DDevice->SetRenderState(
					D3DRS_SRCBLEND,
						D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(
					D3DRS_DESTBLEND,
						D3DBLEND_INVSRCALPHA);

	//　サンプラー設定
	// 　テクスチャ繰返し指定
	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_ADDRESSU,
			D3DTADDRESS_WRAP);			//横軸の繰返し指定

	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_ADDRESSV,
			D3DTADDRESS_WRAP);			//縦軸の繰返し指定

	//拡大縮小時の指定
	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER,
			D3DTEXF_POINT);				//縮小時の指定

	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER,
			D3DTEXF_POINT);				//拡大時の指定

	//テクスチャステージステートの設定
	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_COLOROP,
						D3DTOP_MODULATE);

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_COLORARG1,
						D3DTA_TEXTURE);

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_COLORARG2,
						D3DTA_CURRENT);
						
	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_ALPHAOP,
						D3DTOP_SELECTARG1);			//ＡＲＧ１とＡＲＧ２のα値を乗算してαの値を取得

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_ALPHAARG1,
						D3DTA_TEXTURE);				//テクスチャのα値

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_ALPHAARG2,
						D3DTA_CURRENT);				//頂点のα値
/*
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_D3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
*/
	//m_D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	return	S_OK;
}

//***************************************************************
//	終了
//***************************************************************
void	CRenderer::Uninit()
{
	//解放処理
	if(m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	//デバイス解放
	if(m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}
}

//***************************************************************
//	更新
//***************************************************************
void	CRenderer::Update()
{
	//全更新
	CScene::UpdateAll();
}

//***************************************************************
//	描画
//***************************************************************
void	CRenderer::Draw()
{

			//画面クリア
	m_D3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET |
					D3DCLEAR_ZBUFFER),
					//フレームバッファと深度バッファクリア
					D3DCOLOR_RGBA(0,0,0,0),
					//クリア色
					1.0f,
					//クリア	Ｚ値
					0);	//ステンシル値
	if(SUCCEEDED( m_D3DDevice->BeginScene() ))
	{

		//カメラセット
		CCamera::SetCamera(m_D3DDevice);

		//全描画
		CScene::DrawAll(m_D3DDevice);

		//描画終了
		m_D3DDevice->EndScene();
		
	}

	//裏画面と表画面を切り替え
	m_D3DDevice->Present(NULL,NULL,NULL,NULL);
}

//***************************************************************
//	デバイスを渡す関数
//	引数
//	無し
//	戻り値:
//	LPDIRECT3DDEVICE9	取得するデバイス
//***************************************************************
LPDIRECT3DDEVICE9	CRenderer::GetDevice()
{
	return	m_D3DDevice;
}

//***************************************************************
//	描画タイプの変更関数
//	引数
//	CRenderer::RENDER_TYPE type：描画タイプ
//	戻り値
//	なし
//***************************************************************
void	CRenderer::SetRenderType(CRenderer::RENDER_TYPE type)
{
	//描画タイプが変更引数と同じ場合は以下の処理を行わない
	if(m_nType == type)
	{
		return;
	}

	m_nType = type;

	switch(m_nType)
	{
	case	NOMAL:
	m_D3DDevice->SetRenderState(
					D3DRS_SRCBLEND,
						D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(
					D3DRS_DESTBLEND,
						D3DBLEND_INVSRCALPHA);

	break;
	case	KASAN:
		m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		m_D3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		m_D3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
		break;

	}
}