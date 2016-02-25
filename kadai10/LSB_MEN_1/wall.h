//***************************************************************
//
//	wall.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	WALL_H_
#define	WALL_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//*****************************************************************************
//構造体
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CWall:public	CScene3d
{
public:
	CWall();																									//インストラクタ
	~CWall();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
				D3DXVECTOR3	Rot,float	width,float	heght,int	cutX,int	cutY,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CWall	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
							D3DXVECTOR3	Rot,float	width,float	heght,int	cutX,int	cutY,int	TexNo);					//セッティング
	static	bool	HitWall(void){return	m_bHit;};

private:
	static	bool	m_bHit;
};



#endif