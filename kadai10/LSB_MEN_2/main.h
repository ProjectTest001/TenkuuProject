//*****************************************************************************
//
//
//
//
//*****************************************************************************
#ifndef	MAIN_H_
#define	MAIN_H_


//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define	SCREEN_WIDTH	(800)		//ウィンドウ横幅
#define	SCREEN_HEIGHT	(600)		//ウィンドウ縦幅
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#define	RAZIAN				(3.14f / 180.0f)	//ラジアン補正

//モデルパーツ構造体
typedef	enum
{
	MODELPARTS_WAIST = 0,		//腰
	MODELPARTS_BODY,			//身体
	MODELPARTS_NECK,			//首
	MODELPARTS_HEAD,			//頭
	MODELPARTS_RIGHTARM,		//右腕
	MODELPARTS_RIGHTELBOW,		//右肘
	MODELPARTS_RIGHTHAND,		//右手
	MODELPARTS_LEFTARM,			//左腕
	MODELPARTS_LEFTELBOW,		//左肘
	MODELPARTS_LEFTHAND,		//左手
	MODELPARTS_RIGHTLEG,		//右太もも
	MODELPARTS_RIGHTKNEE,		//右膝
	MODELPARTS_RIGHTFOOT,		//右足
	MODELPARTS_LEFTLEG,			//左太もも
	MODELPARTS_LEFTKNEE,		//左膝
	MODELPARTS_LEFTFOOT,		//左足
	MODELPARTS_MAX,				//パーツ総数
}MODELPARTS;

//モーション用構造体
//モーションデータ
typedef	struct
{
	float	posx;
	float	posy;
	float	posz;

	float	rotx;
	float	roty;
	float	rotz;

}KEY;

//キー情報構造体
typedef	struct
{
	int	nFrame;	//再生フレーム数
	KEY	aKEY[MODELPARTS_MAX];	//パーツ情報
}KEY_INFO;

//キー情報の集合構造体
typedef	struct
{
	KEY_INFO	*pKey;
	int	NumFrame;
}MOTIONDATA;

#endif