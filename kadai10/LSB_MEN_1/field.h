//***************************************************************
//
//	field.h
//	name:Masatugu Kamada
//	更新日：2012/05/29
//
//***************************************************************

#ifndef	FIELD_H_
#define	FIELD_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************

//*****************************************************************************
//構造体
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CField:public	CScene3d
{
public:
	CField();																									//インストラクタ
	~CField();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
					D3DXVECTOR3	Rot,float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CField	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
								D3DXVECTOR3	Rot,float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo);					//セッティング
	static	VERTEX_3D	GetVertex(void){return	m_Vertex_3d;};												//頂点情報の取得

private:
	static	VERTEX_3D	m_Vertex_3d;																			//３Ｄデータ構造体
	D3DXVECTOR3	*m_pNormalBuff;																					//法線のワーク用ポインタ
};



#endif