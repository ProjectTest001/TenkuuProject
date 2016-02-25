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
//class	CBullet;

//プレイヤークラス
class	CPlayer:public	CScene_x
{
public:
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
private:

	float	PurposeRot;																			//目的の角度
	float	ResultRot;																			//プレイヤーの今回の角度
	bool	jump;
	static	bool	m_bDeath;
	bool	clear;
	CScene	*m_pSceneLink;																		//ギミック保存用変数
};



#endif