//***************************************************************
//
//	mountion.h
//	name:Masatugu Kamada
//	更新日：2012/05/29
//
//***************************************************************

#ifndef	MOUNTION_H_
#define	MOUNTION_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//*****************************************************************************
//構造体
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CMountion:public	CScene3d
{
public:
	CMountion();																									//インストラクタ
	~CMountion();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
											int	cut,float	heght,int	cutY,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CMountion	*Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
															int	cut,float	heght,int	cutY,int	TexNo);					//セッティング

private:


};



#endif