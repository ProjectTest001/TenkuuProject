//***************************************************************
//
//	scene3d.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SCENE3D_H_
#define	SCENE3D_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//3D指定

//*****************************************************************************
//構造体
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CScene3d:public	CScene
{
public:
	CScene3d();																									//インストラクタ
	~CScene3d();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CScene3d	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);					//セッティング
	static	float	GetHeight(D3DXVECTOR3	pos);												//地面の高さの取得
	static	float	GetHeightPolygon(D3DXVECTOR3	pos,D3DXVECTOR3	vtx0,D3DXVECTOR3	vtx1,D3DXVECTOR3	vtx2);

private:
	D3DXVECTOR3	*m_pNormalBuff;																					//法線のワーク用ポインタ

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//バッファ
	VERTEX_3D	m_Vertex_3d;																					//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																						//マトリックス
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff;																	//インデックスバッファ

	int	m_nTex;																					//画像番号

};



#endif