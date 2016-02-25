//***************************************************************
//
//	scene2d.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SCENE2D_H_
#define	SCENE2D_H_

//***************************************************************
//	マクロ定義
//***************************************************************
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//	フォーマット指定

//ポリゴン画像情報
#define	POLYGON_X	(50.0f)	//Ｘ座標
#define	POLYGON_Y	(30.0f)		//Ｙ座標
#define	POLYGON_W	(156.0f)	//幅
#define	POLYGON_H	(356.0f)		//高さ

//***************************************************************
//	クラス定義
//***************************************************************
class	CScene2d:public	CScene
{
public:


	CScene2d(int	nPriority = 6);																					//インストラクタ
	~CScene2d();																				//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);													//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CScene2d	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);					//セッティング

private:
	//LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//バッファ
	//VERTEX_2D	m_Vertex_2d;																	//２Ｄデータ構造体
	int	m_nType;
	bool	bmove;
	//int	m_nTex;																					//画像番号

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//バッファ
	VERTEX_2D	m_Vertex_2d;																	//２Ｄデータ構造体

	int	m_nTex;																					//画像番号

};


#endif