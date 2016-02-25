//***************************************************************
//
//	manager.cpp
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
#include	"sound.h"
#include	<dinput.h>
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"manager.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"camera.h"
#include	"scenebillboard.h"
#include	"light.h"
#include	"player.h"
#include	"number.h"
#include	"score.h"
#include	"time.h"
#include	"title.h"
#include	"game.h"
#include	"rezult.h"
#include	"fade.h"
#include	"debugproc.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
CRenderer	*CManager::m_pRenderer;
CInputKeyboard	*CManager::m_pInputkeyboard = NULL;
CCamera	*CManager::m_pCamera = NULL;
CLight	*CManager::m_pLight = NULL;
CScene3d	*CManager::m_pScene3d = NULL;
CScore		*CManager::m_pScore = NULL;
CTitle	*CManager::m_pTitle = NULL;
CGame	*CManager::m_pGame = NULL;
CRezult	*CManager::m_pRezult = NULL;
int	CManager::m_mode = MODE_TITLE;
int	CManager::m_amode = MODE_TITLE;
CFade	*CManager::m_pFade = NULL;
CDebugProc	*CManager::m_pDebug = NULL;
CTexture	*CManager::m_pTexture = NULL;

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CManager::CManager()
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CManager::~CManager()
{

}

//***************************************************************
//	初期化
//***************************************************************
HRESULT	CManager::Init(HINSTANCE	hInstance, HWND	hWnd, BOOL	bWindow)
{

	//クラス生成
	m_pRenderer = new	CRenderer;
	m_pCamera = new	CCamera;
	m_pLight = new	CLight;
	m_pTitle = new	CTitle;
	//m_pGame = new	CGame;
	m_pFade = new	CFade;
	m_pTexture = new	CTexture;
	//m_pDebug = new	CDebugProc;

		//DirectX初期化
		if(FAILED(m_pRenderer->Init(hWnd,bWindow)))
		{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
		}

		//テクスチャ初期化
		if(FAILED(m_pTexture->Init(m_pRenderer->GetDevice())))
		{
					MessageBox(NULL,"directX initialize",
								"error",MB_OK);
					return	-1;
		}

		//ライトの初期化
		if(FAILED(m_pLight->Init(m_pRenderer->GetDevice())))
		{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
		}

		//カメラの初期化
		if(FAILED(m_pCamera->Init(CCamera::PLAYER_CAMERA)))
		{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
		}

		//キー入力のクラス生成
		m_pInputkeyboard = new	CInputKeyboard;

		//キー入力の初期化
		m_pInputkeyboard->Init(hInstance,hWnd);

		//フェードの初期化
		m_pFade->Init(m_pRenderer->GetDevice(),FADE_TEXTURE);

		//デバック文字の初期化
		//m_pDebug->Init(m_pRenderer->GetDevice());

	//タイトル初期化
		if(FAILED(m_pTitle->Init()))
	{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
	}

	return	S_OK;
}


//***************************************************************
//	終了
//***************************************************************
void	CManager::Uninit()
{
	//解放処理
	CScene::ReleaseAll();

	if(m_pRenderer)
	{
		m_pRenderer->Uninit();
		delete	m_pRenderer;
		m_pRenderer = NULL;
	}

	if(m_pInputkeyboard)
	{
		m_pInputkeyboard->Uninit();
		delete	m_pInputkeyboard;
		m_pInputkeyboard = NULL;
	}

	if(m_pLight)
	{
		m_pLight->Uninit();
		delete	m_pLight;
		m_pLight = NULL;
	}

	if(m_pTexture)
	{
		m_pTexture->UnInit();
		delete	m_pTexture;
		m_pTexture = NULL;
	}
}

//***************************************************************
//	更新
//***************************************************************
void	CManager::Update()
{
	//キーボード入力の更新処理
	m_pInputkeyboard->Update();

	//フェード更新
	m_pFade->Update();

	//フェードインが終了したらモード切り替え
	if(m_pFade->GetStatus() == CFade::FADEIN_END)
	{
		SetMode((MODE)m_amode);
	}

	//カメラの更新処理
	m_pCamera->Update();

	switch(m_mode)
	{
	case	MODE_TITLE:

			m_pTitle->Update();

		break;

	case	MODE_GAME:

		m_pGame->Update();

		break;
	case	MODE_REZULT_CLEAR:
		m_pRezult->Update();
		break;

	case	MODE_REZULT_GAMEOVER:
		m_pRezult->Update();
		break;
	}
}

//***************************************************************
//	描画
//***************************************************************
void	CManager::Draw()
{
	switch(m_mode)
	{
	case	MODE_TITLE:
		m_pTitle->Draw();
		break;
	case	MODE_GAME:
		m_pGame->Draw();
		break;

	case	MODE_REZULT_CLEAR:
		m_pRezult->Draw();
		break;

	case	MODE_REZULT_GAMEOVER:
		m_pRezult->Draw();
		break;
	}

	//デバック表示
	//m_pDebug->Draw();
}

//***************************************************
//	モード切り替え関数
//	引数：
//	MODE	mode:切り替え後のモード変数
//	戻り値：
//	なし
//***************************************************
void	CManager::SetMode(MODE	mode)
{
	//モード切り替え
	m_mode = mode;

	//モード終了処理
	switch(m_mode)
	{
		case	MODE_TITLE:
		if(m_pRezult)
		{
			m_pRezult->Uninit();
			delete	m_pRezult;
			m_pRezult = NULL;
		}
		m_pTitle = new	CTitle;
		m_pTitle->Init();
			break;
		case	MODE_GAME:
			if(m_pTitle)
			{
				m_pTitle->Uninit();
				delete	m_pTitle;
				m_pTitle = NULL;
			}
			m_pGame = new	CGame;
			m_pGame->Init();

			break;
		case	MODE_REZULT_CLEAR:
			if(m_pGame)
			{
				m_pGame->Uninit();
				delete	m_pGame;
				m_pGame = NULL;
			}
			m_pRezult = new	CRezult;
			m_pRezult->Init(CRezult::GAME_CLEAR);

			break;
		case	MODE_REZULT_GAMEOVER:
			if(m_pGame)
			{
				m_pGame->Uninit();
				delete	m_pGame;
				m_pGame = NULL;
			}
			m_pRezult = new	CRezult;
			m_pRezult->Init(CRezult::GAME_OVER);

			break;
	}

	//フェードアウト開始
	m_pFade->Start(CFade::FADEOUT,60);
}

//**********************************************
//	モード切り替え関数
//	引数
//	MODE	mode：対象のモード
//	戻り値
//	なし
//**********************************************
void	CManager::ChangeMode(MODE	mode)
{
	m_amode = mode;
	m_pFade->Start(CFade::FADEIN,60);
}