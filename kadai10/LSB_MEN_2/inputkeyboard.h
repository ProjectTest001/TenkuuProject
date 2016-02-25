//***************************************************************
//
//	inputkeyborad.h
//	name:Masatugu Kamada
//	更新日：2012/05/22
//
//***************************************************************

#ifndef	INPUTKEYBOARD_H_
#define	INPUTKEYBOARD_H_


//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define REPEAT_TIME (6)                 // 自動リピート間隔(frame)

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class	CInputKeyboard:public	CInput
{
public:
	CInputKeyboard();										//コンストラクタ
	~CInputKeyboard();										//デストラクタ
	HRESULT	Init(HINSTANCE	hInst,HWND	hwnd);				//初期化
	void	Uninit(void);									//終了
	HRESULT	Update(void);									//更新

	//キーボードの情報を取得する関数
	static	BOOL	GetkeyboardPress(int	nkey);	//キー取得
	static	BOOL	GetkeyboardTrigger(int	nkey);	//キートリガーの取得


private:
	//キーボードの情報
	static	BYTE	m_akey[MAX_KEY];
	static	BYTE	m_akeyTrigger[MAX_KEY];
	static	BYTE	m_akeyRelease[MAX_KEY];
	static	BYTE	m_akeyRepeatTrigger[MAX_KEY];    // 押しっぱのとき、一定間隔でON(自動連射)
	static	int	m_akeyRepeatCount[MAX_KEY]; // キーリピート用カウント

};

#endif