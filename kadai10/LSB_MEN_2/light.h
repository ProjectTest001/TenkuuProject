//*****************************************************************************
//
//	light.h
//	name：Masatugu Kamada
//	更新日：2012/05/26
//
//*****************************************************************************

#ifndef	LIGHT_H_
#define	LIGHT_H_


//*****************************************************************************
//	クラス定義
//*****************************************************************************

class	CLight
{
public:
	CLight();															//コンストラクタ
	~CLight();															//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);												//初期化
	void	Uninit(void);											//終了
	void	Update(void);											//更新
	static	void	SetOffLight(LPDIRECT3DDEVICE9	pDevice){	pDevice->LightEnable(0,FALSE);};
	static	void	SetOnLight(LPDIRECT3DDEVICE9	pDevice){	pDevice->LightEnable(0,TRUE);};

private:

	D3DLIGHT9	m_aLight[3];								//ライト変数

};

#endif
