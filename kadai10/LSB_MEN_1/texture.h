//******************************************************
//
//	texture.h
//	name:Masatugu Kamada
//	create:2012/09/28
//	update:2012/09/28
//
//******************************************************

#ifndef	TEXTURE_H_
#define	TEXTURE_H_

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define	MAX_TEXTURE		(25)

//画像番号
#define	WHITE_TEXTURE	(0)
#define	YEROWW_TEXTURE	(1)
#define	BULLET_TEXTURE	(2)
#define	FIELD_TEXTURE	(3)
#define	WALL_TEXTURE	(4)
#define	SKY_TEXTURE		(5)
#define	MOUNTAIN_TEXTURE	(6)
#define	EXPLOSION_TEXTURE	(7)
#define	NUMBER_TEXTURE	(8)
#define	TIME_TEXTURE	(9)
#define	SCORE_TEXTURE	(10)
#define	FADE_TEXTURE	(11)
#define	TEXT_TEXTURE	(12)
#define	TEXT2_TEXTURE	(13)
#define	TITLE_TEXTURE	(14)
#define	LINE_TEXTURE	(15)
#define	TUTORIAL_TEXTURE	(16)
#define	GAME_OVER_TEXTURE	(17)
#define	GAME_CLEAR_TEXTURE	(18)
#define	SHADOW_TEXTURE	(19)
#define	GIMMICK_TEXTURE	(20)
#define	STOP_TEXTURE	(21)
#define	TREE_TEXTURE	(21)

//*****************************************************************************
//	クラス定義
//*****************************************************************************
class	CTexture
{
public:
	CTexture();
	~CTexture();
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);													//初期化
	void	UnInit(void);																		//終了
	static	LPDIRECT3DTEXTURE9	GetTexture(int	TexNo){return	m_pD3DTexture[TexNo];};			//画像取得

private:

	static	LPDIRECT3DTEXTURE9	m_pD3DTexture[MAX_TEXTURE];															//テクスチャ変数

};

#endif