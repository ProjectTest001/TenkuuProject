//***************************************************************
//
//	time.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	TIME_H_
#define	TIME_H_

//***************************************************************
//	マクロ定義
//***************************************************************
#define	TIME_COUNT	(120)					//時間制限
#define	TIME_DIGIT	(3)						//桁数
//***************************************************************
//	クラス定義
//***************************************************************
class	CTime:public	CScene
{
public:
	CTime(int	nPriority = 6);																					//インストラクタ
	~CTime();																				//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CTime	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);					//セッティング
	static	void	SetTime(int	nScore);
	static	bool	TimeUp(void);
private:

	static	CNumber	*m_apNumber[3];
	static	CScene2d	*m_ap2d;
	static	int	m_nTime;
	int	m_nSpan;

};

#endif