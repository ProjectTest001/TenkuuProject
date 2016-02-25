//***************************************************************
//
//	building.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	BUILDING_H_
#define	BUILDING_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CBuilding:public	CSceneBillboard
{
public:
	CBuilding();																									//インストラクタ
	~CBuilding();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CBuilding	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	TexNo);					//セッティング

private:

protected:
};

#endif