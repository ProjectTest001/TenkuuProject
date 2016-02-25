//***************************************************************
//
//	input.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/30
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

//***************************************************************
//	静的変数
//***************************************************************
LPDIRECTINPUT8	CInput::m_pDInput = NULL;

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CInput::CInput()
{
	//デバイス初期化
	m_pDIDevice = NULL;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CInput::~CInput()
{

}


//***************************************************************
//	初期化
//引数
//HINSTANCE hInst:インスタンス
//HWND hWnd：設定しているウィンドウ
//戻り値
//HRESULT：終了コード
//***************************************************************
HRESULT	CInput::Init(HINSTANCE hInst, HWND hWnd)
{
	//入力設定の生成変数
	HRESULT	hr = S_OK;

	if(m_pDInput == NULL)
	{
		//Direct　Inputインターフェース生成
			hr = DirectInput8Create(
									hInst,					//ソフトのインスタンスハンドル
									DIRECTINPUT_VERSION,			//DirectInputのバージョン
									IID_IDirectInput8,				//取得するインターフェイスのタイプ
									(LPVOID*)&m_pDInput,			//インターフェイスの格納先
									NULL							//COM集成の制御オブジェクト
									);

			if(FAILED(hr))
			{
				return	E_FAIL;
			}

				hr =m_pDInput->CreateDevice(
											GUID_SysKeyboard,			//受け付ける入力デバイス
											&m_pDIDevice,				//IDirectInputDevice8格納先
											NULL						//COM集成の制御オブジェクト
										);
			if(FAILED(hr))
			{
				return	E_FAIL;
			}

			//データフォーマットの設定
			hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);

			//協調モードの設定
				hr = m_pDIDevice->SetCooperativeLevel(hWnd,
												DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

				//入力の受付開始
				m_pDIDevice->Acquire();

	}

	return	hr;
}

//***************************************************************
//	終了
//***************************************************************
void	CInput::Uninit(void)
{
	//解放処理
	if(m_pDIDevice != NULL)
	{
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if(m_pDInput != NULL)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}

}

