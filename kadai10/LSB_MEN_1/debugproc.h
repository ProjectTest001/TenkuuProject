//***************************************************************
//
//	debugproc.h
//	name:Masatugu Kamada
//
//***************************************************************

#ifndef	DEBUGPROC_H_
#define	DEBUGPROC_H_

//***************************************************************
//	クラス定義
//***************************************************************
class	CDebugProc
{
public:
	CDebugProc();									//コンストラクタ
	~CDebugProc();									//デストラクタ

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);		//初期化
	void	Uninit(void);							//終了
	static	void	Print(char	*fmt,...);			//書き込み設定
	static	void	Draw(void);						//描画

private:
	static	LPD3DXFONT	m_pD3DXFont;				//フォント変数
	static	char	m_aStr[1028];					//文字配列
	bool	Switch;									//文字表示切り替えフラグ

};

#endif