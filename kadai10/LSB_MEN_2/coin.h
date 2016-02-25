//***************************************************************
//
//	coin.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	COIN_H_
#define	COIN_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
class	CCoin:public	CItem
{
public:
	CCoin();																					//インストラクタ
	~CCoin();																				//デストラクタ
	virtual	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice, D3DXVECTOR3 vtx,int	TexNo);								//初期化
	virtual	void	Uninit(void);																		//終了
	virtual	void	Update(void);																		//更新
	virtual	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CScene_x	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo);					//セッティング

private:
	bool	get;
	float	vec;
};


#endif