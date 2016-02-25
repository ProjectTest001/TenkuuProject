//***************************************************************
//
//	number.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SCORE_H_
#define	SCORE_H_

//***************************************************************
//	マクロ定義
//***************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
class	CScore:public	CScene
{
public:
	CScore(int	nPriority = 6);																					//インストラクタ
	~CScore();																				//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CScore	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);					//セッティング
	static	void	SetScore(int	nScore);
	static	int	GetScore(void){return	m_nScore;};

private:
	static	CNumber	*m_apNumber[8];
	static	CScene2d	*m_ap2d;
	static	int	m_nScore;

};

#endif