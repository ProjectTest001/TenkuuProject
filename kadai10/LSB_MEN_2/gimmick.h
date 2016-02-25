//***************************************************************
//
//	gimmick.h
//	name:Masatugu Kamada
//	更新日：2012/09/11
//
//***************************************************************

#ifndef	GIMMICK_H_
#define	GIMMICK_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//***************************************************************
//	クラス定義
//***************************************************************
class	CGimmick:public	CScene_x
{
public:
	CGimmick();																					//インストラクタ
	~CGimmick();																				//デストラクタ
	virtual	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice, D3DXVECTOR3 vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo);								//初期化
	virtual	void	Uninit(void);																		//終了
	virtual	void	Update(void);																		//更新
	virtual	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//描画
	static	CGimmick	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo);					//セッティング
	void	GetVtx(VERTEX_3D	*Vtx){*Vtx = m_Vertex_3d;};

private:
	LPD3DXMESH	m_pMesh;																		//メッシュ
	LPD3DXBUFFER	m_pD3DXMatBuff;																//バッファ
	DWORD		m_nNumMat;																		//描画変数
	VERTEX_3D	m_Vertex_3d;																	//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																		//マトリックス
	int	m_nTex;																					//画像番号
};


#endif