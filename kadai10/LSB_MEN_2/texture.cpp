//******************************************************
//
//	texture.cpp
//	name:Masatugu Kamada
//	create:2012/09/28
//	update:2012/09/28
//
//******************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<math.h>
#include	"main.h"
#include	"renderer.h"
#include	"manager.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
LPDIRECT3DTEXTURE9	CTexture::m_pD3DTexture[MAX_TEXTURE] = {NULL};

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CTexture::CTexture()
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CTexture::~CTexture()
{

}

//***************************************************************
//	初期化
//	引数
//	LPDIRECT3DDEVICE9	pDevice:デバイスポインタ
//	戻り値
//	なし
//***************************************************************
HRESULT	CTexture::Init(LPDIRECT3DDEVICE9	pDevice)
{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, WHITE_TEXTURE_FILE, &m_pD3DTexture[WHITE_TEXTURE]);			//白画像
		D3DXCreateTextureFromFile(pDevice, YEROWW_TEXTURE_FILE, &m_pD3DTexture[YEROWW_TEXTURE]);		//黄色画像
		D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_FILE, &m_pD3DTexture[BULLET_TEXTURE]);		//弾丸画像
		D3DXCreateTextureFromFile(pDevice, FIELD_TEXTURE_FILE, &m_pD3DTexture[FIELD_TEXTURE]);			//フィールド画像
		D3DXCreateTextureFromFile(pDevice, WALL_TEXTURE_FILE, &m_pD3DTexture[WALL_TEXTURE]);			//壁画像
		D3DXCreateTextureFromFile(pDevice, SKY_TEXTURE_FILE, &m_pD3DTexture[SKY_TEXTURE]);				//空画像
		D3DXCreateTextureFromFile(pDevice, MOUNTION_TEXTURE_FILE, &m_pD3DTexture[MOUNTAIN_TEXTURE]);	//山画像
		D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURE_FILE, &m_pD3DTexture[EXPLOSION_TEXTURE]);	//爆発画像
		D3DXCreateTextureFromFile(pDevice, NUMBER_TEXTURE_FILE, &m_pD3DTexture[NUMBER_TEXTURE]);		//数字画像
		D3DXCreateTextureFromFile(pDevice, TIME_TEXTURE_FILE, &m_pD3DTexture[TIME_TEXTURE]);			//時間画像
		D3DXCreateTextureFromFile(pDevice, SCORE_TEXTURE_FILE, &m_pD3DTexture[SCORE_TEXTURE]);			//スコア画像	
		D3DXCreateTextureFromFile(pDevice, FADE_TEXTURE_FILE, &m_pD3DTexture[FADE_TEXTURE]);			//フェード用画像
		D3DXCreateTextureFromFile(pDevice, TEXT_TEXTURE_FILE, &m_pD3DTexture[TEXT_TEXTURE]);			//文字画像(PUSH ENTER)
		D3DXCreateTextureFromFile(pDevice, TEXT2_TEXTURE_FILE, &m_pD3DTexture[TEXT2_TEXTURE]);			//文字画像（チュートリアル案内）
		D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_FILE, &m_pD3DTexture[TITLE_TEXTURE]);			//タイトル画像
		D3DXCreateTextureFromFile(pDevice, LINE_TEXTURE_FILE, &m_pD3DTexture[LINE_TEXTURE]);			//ライン画像
		D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_FILE, &m_pD3DTexture[TUTORIAL_TEXTURE]);	//チュートリアル画像
		D3DXCreateTextureFromFile(pDevice, GAME_OVER_TEXTURE_FILE, &m_pD3DTexture[GAME_OVER_TEXTURE]);	//ゲームオーバ画像
		D3DXCreateTextureFromFile(pDevice, GAME_CLEAR_TEXTURE_FILE, &m_pD3DTexture[GAME_CLEAR_TEXTURE]);//ゲームクリア画像
		D3DXCreateTextureFromFile(pDevice, SHADOW_TEXTURE_FILE, &m_pD3DTexture[SHADOW_TEXTURE]);		//影画像
		D3DXCreateTextureFromFile(pDevice, GIMMICK_TEXTURE_FILE, &m_pD3DTexture[GIMMICK_TEXTURE]);		//ギミック画像
		D3DXCreateTextureFromFile(pDevice, STOP_TEXTURE_FILE, &m_pD3DTexture[STOP_TEXTURE]);			//ストップ表示画像
		D3DXCreateTextureFromFile(pDevice, TREE_TEXTURE_FILE, &m_pD3DTexture[TREE_TEXTURE]);			//木画像
		D3DXCreateTextureFromFile(pDevice, BLUE_TEXTURE_FILE, &m_pD3DTexture[BLUE_TEXTURE]);			//青画像
		D3DXCreateTextureFromFile(pDevice, TITLE2_TEXTURE_FILE, &m_pD3DTexture[24]);
		D3DXCreateTextureFromFileEx(pDevice,WALL_TEXTURE_FILE,D3DX_DEFAULT,D3DX_DEFAULT,3,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,
			D3DX_DEFAULT,0,NULL,NULL,&m_pD3DTexture[WALL_TEXTURE]);
	return	S_OK;
}

//***************************************************************
//	終了
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
void	CTexture::UnInit()
{
	for(int	i = 0; i < MAX_TEXTURE; i++)
	{
		if(m_pD3DTexture[i])
		{
			m_pD3DTexture[i]->Release();
			m_pD3DTexture[i] = NULL;
		}
	}

}

