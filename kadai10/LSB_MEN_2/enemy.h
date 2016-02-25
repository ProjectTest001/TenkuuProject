//*****************************************************************************
//
//	enemy.h
//	name：Masatugu Kamada
//	更新日：2012/06/5
//
//*****************************************************************************

#ifndef	ENEMY_H_
#define	ENEMY_H_


//*****************************************************************************
//	マクロ定義
//*****************************************************************************

//*****************************************************************************
//	構造体
//*****************************************************************************
typedef	struct
{
	float	Speed;		//移動力
	float	RotSpeed;	//回転速度
	float	JumpUp;		//ジャンプ力
	float	Vec;		//指定距離
}ENEMY;
//*****************************************************************************
//	クラス定義
//*****************************************************************************
class	CEnemy:public	CScene_x
{
public:
	CEnemy();											//インストラクタ
	~CEnemy();											//デストラクタ

	typedef	enum
	{
		NOMAL_MOVE = 0,
		ROLING,
		JUMPING,
		ROLL_JUMPING,
		PLAYER_JUMPING,
		TRACKING,
		MOVE_MAX,
	};
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,float	rotspeed,float	jumpup,int	nType,int	TexNo);				//初期化
	void	Uninit(void);								//終了
	void	Update(void);								//更新
	void	Draw(LPDIRECT3DDEVICE9	pDevice);									//描画
	static	CEnemy	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,float	rotspeed,float	jumpup,int	Type,int	TexNo);	//生成
	bool	HitEnemy(D3DXVECTOR3	Pos);

private:
	LPD3DXMESH	m_pMesh;																		//メッシュ
	LPD3DXBUFFER	m_pD3DXMatBuff;																//バッファ
	DWORD		m_nNumMat;																		//描画変数
	VERTEX_3D	m_Vertex_3d;															//３Ｄデータ構造体
	D3DXMATRIX	m_mtxWorld;																		//マトリックス
	int	type;																					//移動の種類
	ENEMY	m_aEnamy;																			//敵ステータス
	int	m_nTex;																					//画像番号
};



#endif