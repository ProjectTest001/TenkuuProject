//***************************************************************
//
//	model.h
//	name:Masatugu Kamada
//	update：2012/11/05
//
//***************************************************************


#ifndef	MODEL_H_
#define	MODEL_H_

//***************************************************************
//	マクロ定義
//***************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CModel
{
public:
	CModel();																//コンストラクタ
	~CModel();															//デストラクタ


	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,int	nType,D3DXVECTOR3	pos,
							D3DXVECTOR3	rot,int	TexNo);		//初期化
	void	Uninit(void);													//終了
	void	Update(void);													//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);														//描画
	static	CModel	*Create(LPDIRECT3DDEVICE9	pDevice,int	nType,D3DXVECTOR3	pos,
							D3DXVECTOR3	rot,int	TexNo);												//生成
	void	SetParent(CModel	*pModel){m_pParent = pModel;};									//親モデルのセット
	void	SetVertex(D3DXVECTOR3	pos){m_Vertex_3d.vtx = pos;};
	void	SetRot(D3DXVECTOR3	rot){m_Vertex_3d.Rot_vtx = rot;};
	D3DXMATRIX	GetMtxWorld(void){return	m_mtxWorld;};											//モデルマトリックスの取得
	
private:
	CModel	*m_pParent;																			//親モデルへのポインタ
	VERTEX_3D	m_Vertex_3d;																	//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																		//マトリックス
	int	m_nTex;																					//画像番号
	int	m_nmodel;																				//モデル番号

};

#endif