//****************************************************************
//
//	pose.h
//	name：Masatugu Kamada
//	更新日：2012/08/19
//
//****************************************************************

#ifndef	POSE_H_
#define	POSE_H_


//*****************************************************************************
//	マクロ定義
//*****************************************************************************

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class	CPose
{
public:
	CPose();																	//インストラクタ
	~CPose();																				//デストラクタ

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	void	SetPose(bool	pose){m_bPose = pose;};												//ポーズ設定
	static	bool	GetPose(void){return	m_bPose;};											//ポーズ判定取得
private:
	int	m_nTime;																				//時間
	CScene2d	*m_pPose2d;
	static	bool	m_bPose;
};

#endif