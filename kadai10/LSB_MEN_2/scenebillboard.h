//***************************************************************
//
//	scenebillboard.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SCENEBILLBOARD_H_
#define	SCENEBILLBOARD_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CSceneBillboard:public	CScene
{
public:
	CSceneBillboard(int	nPriority = 5);																									//インストラクタ
	~CSceneBillboard();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CSceneBillboard	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);					//セッティング

private:

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//バッファ
	VERTEX_3D	m_Vertex_3d;																					//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																						//マトリックス
	int	m_nTex;																					//画像番号
};



#endif