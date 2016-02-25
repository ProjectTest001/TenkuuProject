//***************************************************************
//
//	bullet.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	BULLET_H_
#define	BULLET_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CBullet:public	CSceneBillboard
{
public:
	CBullet();																									//インストラクタ
	~CBullet();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CBullet	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo);					//セッティング
	static	VERTEX_3D	GetVertex(void){return	m_Vertex_3d;};												//頂点情報の取得

private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//バッファ
	static	VERTEX_3D	m_Vertex_3d;																			//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																						//マトリックス
	int	m_nTex;																									//画像番号
};



#endif

