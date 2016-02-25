//******************************************************
//
//	texture.h
//	name:Masatugu Kamada
//	create:2012/09/28
//	update:2012/09/28
//
//******************************************************

#ifndef	XFILE_H_
#define	XFILE_H_

//*****************************************************************************
//	マクロ定義
//*****************************************************************************

//画像番号

//プレイヤー
#define	LSB_ID (0)
#define	LSB_NUM	(16)

//敵
#define	ROBO_ENEMY_ID	(LSB_ID + LSB_NUM)
#define	ROBO_ENEMY_NUM	(1)

//アイテム
//コイン
#define	COIN_ID	(ROBO_ENEMY_ID + ROBO_ENEMY_NUM)
#define	COIN_NUM	(1)

//星
#define	STAR_ID	(COIN_ID + COIN_NUM)
#define	STAR_NUM	(1)

#define	MAX_XFILE		(STAR_ID + STAR_NUM)

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class	CXfile
{
public:
	CXfile();
	~CXfile();
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);													//初期化
	void	UnInit(void);																		//終了

	//Ｘファイル情報取得
	static	LPD3DXMESH	GetMesh(int	No){return	m_pMesh[No];};	
	static	LPD3DXBUFFER	GetBuffer(int	No){return	m_pD3DXMatBuff[No];};	
	static	DWORD	GetWord(int	No){return	m_nNumMat[No];};		

private:

	static	LPD3DXMESH	m_pMesh[MAX_XFILE];																		//メッシュ
	static	LPD3DXBUFFER	m_pD3DXMatBuff[MAX_XFILE];																//バッファ
	static	DWORD		m_nNumMat[MAX_XFILE];																		//描画変数

};

#endif