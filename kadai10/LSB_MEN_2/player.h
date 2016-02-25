//*****************************************************************************
//
//	player.h
//	name：Masatugu Kamada
//	更新日：2012/05/25
//
//*****************************************************************************

#ifndef	PLAYER_H_
#define	PLAYER_H_


//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define	MOVE	(0.048f)		//移動量
#define	JUMP	(1.5f)		//ジャンプ力
#define	SPAN_SHOT	(5)	//弾の発射間隔
#define	PLAYER_ROT	(0.1f)	//回転速度
//*****************************************************************************
//	構造体
//*****************************************************************************

//*****************************************************************************
//	クラス定義
//*****************************************************************************

//前方参照
class	CShadow;
class	CModel;

//プレイヤークラス
class	CPlayer:public	CScene_x
{
public:

	//モーションの種類
	typedef	enum
	{
		MOTIONTYPE_NEUTRAL = 0,				//何もしていない
		MOTIONTYPE_WALK,					//歩く
		MOTIONTYPE_PUNCH,					//パンチ
		MOTIONTYPE_KICK,					//キック
		MOTIONTYPE_KICK2,					//キック
		MOTIONTYPE_JUMP,					//ジャンプ
		MOTIONTYPE_JUMPEND,					//ジャンプ後の着地
		MOTIONTYPE_HIT,						//のけぞり
		MOTION_MAX,							//総数
	}MOTIONTYPE;

	CPlayer();											//コンストラクタ
	~CPlayer();											//デストラクタ
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo);				//初期化
	void	Uninit(void);								//終了
	void	Update(void);								//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);									//描画
	static	CPlayer	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo);	//生成
	VERTEX_3D	GetVtx(void){return	m_Vertex_3d;};
	bool	HitWall(void);
	static	void	PlayerDeath(void){m_bDeath = true;	PlaySound(SE_00,DMUS_SEGF_SECONDARY);};
	void	HitGimmick(void);

	MOTIONTYPE	GetMotion(void){return	m_motionType;}			//モーション状況取得関数
private:

	float	PurposeRot;																			//目的の角度
	float	ResultRot;																			//プレイヤーの今回の角度
	bool	jump;
	static	bool	m_bDeath;
	bool	clear;
	CScene	*m_pSceneLink;																		//ギミック保存用変数
	CShadow	*m_pShadow;																			//個人用影

	CModel	*m_apModel[MODELPARTS_MAX];																		//各パーツのモデルポインタ

	int	m_nPartsNumber;			//パーツ番号

	//モーション関連
	void	LoadMotionData(void);						//モーションデータ読み込み
	//void	SetMotionData(FILE	*File,KEY_INFO	*KeyData);						//モーションデータのセット
	void	SetMotion(MOTIONTYPE	type,int	nFrameBlend,bool	bBlend);		//モーションの設定
	void	UpdateMotion(void);					//モーションの更新
	MOTIONTYPE	m_motionType;					//現在のモーションの種類
	KEY_INFO	*m_pKeyInfo;						//対象モーションのキーへのポインタ
	int	m_nKey;									//対象モーションのキーNumber
	int	m_nNumber;								//対象モーションのキーの総数
	int	m_nCountMotion;							//モーションカウンタ
	bool	m_bLoopMotion;						//ループモーションかどうか
	bool	m_bMotion;							//モーションしているかどうか
	bool	m_bFinishMotion;					//モーションが終了しているかどうか
	bool	m_bBlendNow;						//ブレンド中かどうか

	//ブレンド関連
	KEY_INFO	*m_pKeyInfoBlend;
	int	m_nNumBlend;
	int	m_nKeyBlend;
	int	m_nCountMotionBlend;
	bool	m_bLoopMotionBlend;

	int	m_nFrameBlend;					//ブレンドする際にかけるフレーム数
	int	m_nCountBlend;					//ブレンド中のカウンタ
	bool	m_bBlendMotion;				//ブレンドするかどうか

	//モーション変数
	static	MOTIONDATA	*m_apKey;

};



#endif