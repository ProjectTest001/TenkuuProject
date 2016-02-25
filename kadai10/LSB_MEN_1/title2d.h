//***************************************************************
//
//	title2d.h
//	name:Masatugu Kamada
//	create:2012/10/20
//	update：2012/10/20
//
//***************************************************************

#ifndef	TITLE2D_H_
#define	TITLE2D_H_

//***************************************************************
//	マクロ定義
//***************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CTitle2d:public	CScene2d
{
public:

	typedef	enum
	{
		NONE = 0,
		MOVE_TYPE,
		MOVE_KEY,
		MOVE_TUTORIAL,
		TYPE_MAX,
	}TYPE;

	CTitle2d();																					//インストラクタ
	~CTitle2d();																				//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CTitle2d	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);					//セッティング

private:
	//LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//バッファ
	//VERTEX_2D	m_Vertex_2d;																	//２Ｄデータ構造体
	int	m_nType;
	bool	bmove;
	//int	m_nTex;																					//画像番号
};






#endif