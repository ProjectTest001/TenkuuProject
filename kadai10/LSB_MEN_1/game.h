//***************************************************************
//
//	game.h
//	name:Masatugu Kamada
//	更新日：2012/07/10
//
//***************************************************************

#ifndef	GAME_H_
#define	GAME_H_


//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define	MAX_PLAYER		(1)				//プレイヤー最大数（一人用を考えてるから多分いらない）

//*****************************************************************************
//	クラス定義
//*****************************************************************************
//前方参照
class	CPose;

class	CGame
{
public:
	CGame();	//インストラクタ
	~CGame();	//デストラクタ

	HRESULT	Init(void);		//初期化処理
	void	Uninit(void);	//終了処理
	void	Update(void);	//更新処理
	void	Draw(void);
	static	VERTEX_3D	GetPlayer(void){return	m_pPlayer[0]->GetVtx();};

private:
	static	CScene3d	*m_pScene3d;										//３Ｄ変数
	static	CScore	*m_pScore;												//スコア変数
	static	CTime	*m_pTime;												//時間変数
	static	CRenderer	*m_pRenderer;										//レンダ―変数

	bool	m_bSwitch;														//ポーズ判定
	static	CPose	*m_pPose;												//ポーズ変数
	static	CPlayer	*m_pPlayer[MAX_PLAYER];									//プレイヤー変数

};

#endif