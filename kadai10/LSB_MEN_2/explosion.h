//***************************************************************
//
//	explosion.h
//	name:Masatugu Kamada
//	更新日：2012/06/02
//
//***************************************************************

#ifndef	EXPLOSION_H_
#define	EXPLOSION_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************


//***************************************************************
//	クラス定義
//***************************************************************
class	CExplosion:public	CSceneBillboard
{
public:
	CExplosion(int	nPriority = 5);																								//コンストラクタ
	~CExplosion();																								//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo);									//初期化
	void	Uninit(void);																						//終了
	void	Update(void);																						//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//描画
	static	CExplosion	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo);									//セッティング

private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//バッファ
	VERTEX_3D	m_Vertex_3d;																					//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																						//マトリックス
	float	m_Time;																								//爆発エフェクトの寿命
	int	m_nTex;																					//画像番号
};



#endif

