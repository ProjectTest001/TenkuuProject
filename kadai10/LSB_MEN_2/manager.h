//***************************************************************
//
//	manager.h
//	name:Masatugu Kamada
//	更新日：2012/05/19
//
//***************************************************************

#ifndef	MANAGER_H_
#define	MANAGER_H_

//***************************************************************
//	マクロ定義
//***************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
//前方参照
class	CInputKeyboard;
class	CCamera;
class	CLight;
class	CScene3d;
class	CScore;
class	CTime;
class	CTitle;
class	CGame;
class	CRezult;
class	CFade;
class	CDebugProc;
class	CTexture;
class	CXfile;

class	CManager
{
public:
	CManager();																//コンストラクタ
	~CManager();															//デストラクタ

	typedef	enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_REZULT_CLEAR,
		MODE_REZULT_GAMEOVER,
		MODE_MAX,
	}MODE;

	HRESULT	Init(HINSTANCE	hInstance, HWND	hWnd, BOOL	bWindow);		//初期化
	void	Uninit(void);													//終了
	void	Update(void);													//更新
	void	Draw(void);														//描画

	static	CRenderer	*GetRenderer(void){return	m_pRenderer;};									//レンダ―取得
	static	CInputKeyboard	*GetInputKeyboard(void){return	m_pInputkeyboard;};						//キー入力の取得関数
	static	CCamera	*GetCamera(void){return	m_pCamera;};											//カメラ情報取得
	static	CScene3d	*GetScene3D(void){return	m_pScene3d;};
	static	void	SetMode(MODE	mode);															//ステート切り替え
	static	void	ChangeMode(MODE	mode);															//ステート切り替え

private:
	static	CRenderer	*m_pRenderer;										//レンダ―変数
	static	CTexture	*m_pTexture;										//テクスチャ変数
	static	CInputKeyboard	*m_pInputkeyboard;								//キーボード変数
	static	CCamera	*m_pCamera;												//カメラ変数
	static	CLight	*m_pLight;												//ライト変数
	static	CScene3d	*m_pScene3d;										//３Ｄ変数
	static	CScore	*m_pScore;												//スコア変数
	static	CTime	*m_pTime;												//時間変数
	static	int	m_mode;													//ゲームモード変数
	static	int	m_amode;
	static	CTitle	*m_pTitle;												//タイトル変数
	static	CGame	*m_pGame;												//ゲーム変数
	static	CRezult	*m_pRezult;												//リザルト変数
	static	CFade	*m_pFade;												//フェード変数
	static	CDebugProc	*m_pDebug;											//デバック変数
	static	CXfile	*m_pXfile;												//Ｘファイル変数
};

#endif