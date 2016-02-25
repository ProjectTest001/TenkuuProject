//***************************************************************
//
//	scene_x.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SCENE_X_H_
#define	SCENE_X_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
class	CScene_x:public	CScene
{
public:
	CScene_x(int	nPriority = 4);																					//インストラクタ
	~CScene_x();																				//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo);								//初期化
	void	Uninit(void);																		//終了
	void	Update(void);																		//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CScene_x	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo);					//セッティング

private:

protected:

	LPD3DXMESH	m_pMesh;																		//メッシュ
	LPD3DXBUFFER	m_pD3DXMatBuff;																//バッファ
	DWORD		m_nNumMat;																		//描画変数
	VERTEX_3D	m_Vertex_3d;																	//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																		//マトリックス
	int	m_nTex;																					//画像番号

};



#endif