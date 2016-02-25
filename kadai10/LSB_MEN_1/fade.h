//***************************************************************
//
//	fade.h
//	name:Masatugu Kamada
//	更新日：2012/07/11
//
//***************************************************************

#ifndef	FADE_H_
#define	FADE_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
class	CFade:public	CScene
{
public:
	CFade(int	nPriority = 7);																	//インストラクタ
	~CFade();																				//デストラクタ

	//フェードモード設定
	typedef	enum
	{
		NONE = 0,			//通常状態
		FADEIN,				//フェードイン
		FADEIN_END,			//フェードイン終了
		FADEOUT,			//フェードアウト
		FADEOUT_END,		//フェードアウト終了
		FADE_MAX
	}STATUS;

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,int	TexNo);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	void	Start(STATUS	status,int	Time);													//フェードの切り替え
	static	int	GetStatus(void){return	m_status;};																	//フェード状態の取得

private:
	static	int	m_status;																		//フェードモード用変数
	int	m_nTime;																				//時間
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//バッファ
	VERTEX_2D	m_Vertex_2d;																	//２Ｄデータ構造体
	int	m_nTex;																					//画像番号
};





#endif