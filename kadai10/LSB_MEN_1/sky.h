//***************************************************************
//
//	sky.h
//	name:Masatugu Kamada
//	更新日：2012/05/29
//
//***************************************************************

#ifndef	SKY_H_
#define	SKY_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//*****************************************************************************
//構造体
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CSky:public	CScene3d
{
public:
	CSky();																									//インストラクタ
	~CSky();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
											int	cut,float	heght,int	cutY,float	rot,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CSky	*Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
															int	cut,float	heght,int	cutY,float	rot,int	TexNo);					//セッティング

private:

	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff2;																		//フタ用バッファ
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff2;																	//フタ用インデックスバッファ
};



#endif