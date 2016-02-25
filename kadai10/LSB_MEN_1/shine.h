//*****************************************************
//
//	shine.h
//	name:MasatuguKamada
//	create:2012/11/08
//	update:2012/11/08
//
//*****************************************************

#ifndef	SHINE_H_
#define	SHINE_H_

//*****************************************************
//	マクロ定義
//*****************************************************

//*****************************************************
//	クラス関数
//*****************************************************
class	CShine:public	CSceneBillboard
{
public:
	CShine();								//コンストラクタ
	~CShine();								//デストラクタ

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	pos,D3DXCOLOR	color,int	life,D3DXVECTOR3	Scail,
					float	Speed,int	TexNo);							//初期化
	void	UnInit();						//終了
	void	Update();						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);							//描画
	static	CShine	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	pos,D3DXCOLOR	color,int	life,D3DXVECTOR3	Scail,
					float	Speed,int	TexNo);		//生成

private:
	int	m_nLife;					//ライフ
	float	m_fSpeed;				//減少速度

};

#endif