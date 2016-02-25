//***************************************************************
//
//	shadow.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SHADOW_H_
#define	SHADOW_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//*****************************************************************************
//構造体
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CShadow:public	CScene3d
{
public:
	CShadow();																									//インストラクタ
	~CShadow();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CShadow	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo);					//セッティング

private:
	float	m_ShadowPoint;
};

#endif