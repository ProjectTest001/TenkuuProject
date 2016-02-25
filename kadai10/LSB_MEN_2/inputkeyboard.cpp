//***************************************************************
//
//	inputkeyboard.cpp
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
#include	"inputkeyboard.h"

//***************************************************************
//	静的変数
//***************************************************************
BYTE	CInputKeyboard::m_akey[MAX_KEY] = {NULL};
BYTE	CInputKeyboard::m_akeyTrigger[MAX_KEY] = {NULL};
BYTE	CInputKeyboard::m_akeyRelease[MAX_KEY] = {NULL};
BYTE	CInputKeyboard::m_akeyRepeatTrigger[MAX_KEY] = {NULL};
int	CInputKeyboard::m_akeyRepeatCount[MAX_KEY] = {0};

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CInputKeyboard::CInputKeyboard()
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CInputKeyboard::~CInputKeyboard()
{

}

//***************************************************************
//	初期化
//引数
//HINSTANCE hInst:インスタンス
//HWND hWnd：設定したウィンドウ
//戻り値
//HRESULT：終了コード
//***************************************************************
HRESULT	CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	//キーの設定変数宣言
	HRESULT	result = S_OK;


	//初期化
	CInput::Init(hInst,hWnd);

	//キーの基本情報取得
	LPDIRECTINPUTDEVICE8	pKeyboard = CInput::GetKeyDevice();

	//デバイスの作成
	result = pKeyboard->GetDeviceState(256,m_akey);

		//キーバッファの初期化
		ZeroMemory(m_akey, 256);

		pKeyboard->Acquire();

	return	result;
}

//***************************************************************
//	終了
//***************************************************************
void	CInputKeyboard::Uninit(void)
{
	CInput::Uninit();

}

//***************************************************************
//	更新
//戻り値
//HRESULT：終了コード
//***************************************************************
HRESULT	CInputKeyboard::Update(void)
{
	HRESULT	result;						//更新設定変数
	BYTE	lastKeyState[MAX_KEY];		//前回の状態保存用
	LPDIRECTINPUTDEVICE8	pKeyboard = CInput::GetKeyDevice();	//キー情報取得

	// 前回の状態を保存、比較用
	memcpy(lastKeyState,m_akey,MAX_KEY);

		// 最新の状態を得る
	result = pKeyboard->GetDeviceState(256,m_akey);
	if(SUCCEEDED(result))
	{
		for(int i = 0; i < MAX_KEY; i++)      // キーの数だけ、繰り返し
		{
			m_akeyTrigger[i] = (lastKeyState[i] ^ m_akey[i]) // 変更あり
                            & m_akey[i];                      // かつ　今ONのもの
            m_akeyRelease[i] = (lastKeyState[i] ^ m_akey[i]) // 変更あり
                            & ~m_akey[i];                     // かつ　今OFFのもの

            // 自動リピート処理
            if(m_akey[i])         // 押されているもので
            {
				
                if(m_akeyRepeatCount[i] == 0)  // カウンタが0なら
                {
                    m_akeyRepeatTrigger[i] = m_akey[i];  // ON扱い
                }
                else                        // カウント途中
                {
                    m_akeyRepeatTrigger[i] = 0;    // OFF扱い
                }
                
                m_akeyRepeatCount[i]++;
                if(m_akeyRepeatCount[i] > REPEAT_TIME) // 一定frame越えたら
                        m_akeyRepeatCount[i] = 0;      // カウント0にして、次回ON
				
            }
            else                    // 押されていなかったらOFF扱い
            {
                m_akeyRepeatTrigger[i] = 0;
                m_akeyRepeatCount[i] = 0;
            }
        }
    }
	//情報取得に失敗した場合
		else
		{
			//アクセス権取得
			pKeyboard->Acquire();
		}

	return	result;
}

//*****************************************************************************
//	キー取得関数
//引数
//int nkey:押されたキーのナンバー
//戻り値
//BOOL：押されたかの判定
//*****************************************************************************
BOOL	CInputKeyboard::GetkeyboardPress(int nkey)
{
    return (m_akey[nkey] & 0x80);	// 押されたときに立つビットを検査

}

//*****************************************************************************
//	キートリガー取得関数
//引数
//int nkey:押されたキーのナンバー
//戻り値
//BOOL：押されたかの判定
//*****************************************************************************
BOOL	CInputKeyboard::GetkeyboardTrigger(int nkey)
{
    return (m_akeyTrigger[nkey] & 0x80);

}
