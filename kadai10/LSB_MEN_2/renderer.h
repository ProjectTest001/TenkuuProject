//***************************************************************
//
//	renderer.h
//	name:Masatugu Kamada
//	更新日：2012/05/19
//
//***************************************************************

#ifndef	RENDERER_H_
#define	RENDERER_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
//テクスチャ情報
#define	WHITE_TEXTURE_FILE	("TEXTURE/白紙.png")				//モデル画像
#define	YEROWW_TEXTURE_FILE	("TEXTURE/黄色.png")				//モデル画像
#define	BLUE_TEXTURE_FILE	("TEXTURE/blue.png")				//青画像（プレイヤーに使う）
#define	BULLET_TEXTURE_FILE	("TEXTURE/bullet.png")				//弾画像
#define	FIELD_TEXTURE_FILE	("TEXTURE/field.png")				//地面画像
#define	WALL_TEXTURE_FILE	("TEXTURE/壁.png")					//壁画像
#define	SKY_TEXTURE_FILE	("TEXTURE/空.bmp")					//空画像
#define	MOUNTION_TEXTURE_FILE	("TEXTURE/mountain000.png")		//山画像
#define	EXPLOSION_TEXTURE_FILE	("TEXTURE/kirakira.png")		//爆発用画像
#define	NUMBER_TEXTURE_FILE	("TEXTURE/number.png")				//スコア画像
#define	TIME_TEXTURE_FILE	("TEXTURE/time_waku.png")			//時間枠画像
#define	SCORE_TEXTURE_FILE	("TEXTURE/score_waku.png")			//スコア枠画像
#define	FADE_TEXTURE_FILE	("TEXTURE/fade.png")				//フェードイン・アウト用画像
#define	TEXT_TEXTURE_FILE	("TEXTURE/mozi.png")				//文字画像（PUSH　ENTER）
#define	TEXT2_TEXTURE_FILE	("TEXTURE/チュートリアル.png")		//文字画像（チュートリアル案内）
#define	TITLE_TEXTURE_FILE	("TEXTURE/LSB_MEN_title.png")				//タイトル画像
#define	TITLE2_TEXTURE_FILE	("TEXTURE/karie.png")				//タイトル画像
#define	LINE_TEXTURE_FILE	("TEXTURE/line.png")				//ライン画像
#define	TUTORIAL_TEXTURE_FILE	("TEXTURE/setumei.png")			//説明画像
#define	GAME_OVER_TEXTURE_FILE	("TEXTURE/gameover.png")		//ゲームオーバー画像
#define	GAME_CLEAR_TEXTURE_FILE	("TEXTURE/clear.png")			//ゲームクリア画像
#define	SHADOW_TEXTURE_FILE		("TEXTURE/effect.jpg")			//影画像
#define	GIMMICK_TEXTURE_FILE		("TEXTURE/gimmick000.jpg")	//ギミック画像
#define	TREE_TEXTURE_FILE		("TEXTURE/tree000.png")	//ギミック画像
#define	STOP_TEXTURE_FILE	("TEXTURE/stop.png")				//ポーズ画像


//モデル関連
#define	GAME_OVER_TEXTURE_FILE1	("model/棒１.x")				//ゲームオーバーモデル
#define	GAME_OVER_TEXTURE_FILE2	("model/棒２.x")				//ゲームオーバーモデル
#define	GAME_OVER_TEXTURE_FILE3	("model/棒３.x")				//ゲームオーバーモデル

//***************************************************************
//	クラス定義
//***************************************************************
class	CRenderer
{
public:
	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ
	
	typedef	enum
	{
		NOMAL,				//通常
		ADD,				//加算合成
		SUBTRACTION,		//減算合成
		TYPE_MAX,
	}RENDER_TYPE;

	HRESULT	Init(HWND	hWindow,BOOL	bwindow);			//初期化
	void	Uninit(void);									//終了
	void	Update();										//更新
	void	Draw();											//描画
	static	void	SetRenderType(RENDER_TYPE	type);		//描画タイプの変更

	//デバイスを返す関数
	static	LPDIRECT3DDEVICE9	GetDevice(void);

private:

	LPDIRECT3D9	m_pD3D;
	static	LPDIRECT3DDEVICE9	m_D3DDevice;						//デバイス
	static	int	m_nType;
};

#endif