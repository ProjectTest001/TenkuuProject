//***************************************************************
//
//	input.h
//	name:Masatugu Kamada
//	更新日：2012/05/22
//
//***************************************************************

#ifndef	INPUT_H_
#define	INPUT_H_

#define	MAX_KEY		(256)


//*****************************************************************************
//	クラス定義
//*****************************************************************************
class	CInput
{
public:
	CInput();													//コンストラクタ
	virtual	~CInput();											//デストラクタ
	virtual	HRESULT	Init(HINSTANCE	hInst, HWND	hWnd);			//初期化
	virtual	void	Uninit(void);								//終了
	virtual	HRESULT	Update(void) = 0;							//更新
		LPDIRECTINPUTDEVICE8	GetKeyDevice(void){return	m_pDIDevice;};

protected:

	static	LPDIRECTINPUT8	m_pDInput;							//入力変数
	LPDIRECTINPUTDEVICE8	m_pDIDevice;						//入力デバイス

private:
};


#endif