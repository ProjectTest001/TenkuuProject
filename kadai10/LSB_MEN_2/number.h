//***************************************************************
//
//	number.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	NUMBER_H_
#define	NUMBER_H_

//***************************************************************
//	マクロ定義
//***************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
class	CNumber
{
public:
	CNumber(int	nPriority = 6);																					//インストラクタ
	~CNumber();																				//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CNumber	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo);					//セッティング
	void	SetNumber(int	nNumber);

private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//バッファ
	VERTEX_2D	m_Vertex_2d;																	//２Ｄデータ構造体
	int	m_nTex;																					//画像番号
};

#endif