//***************************************************************
//
//	scenebillboard.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	CAMERA_H_
#define	CAMERA_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define	CAMERA_MOVE	(0.5f)		//移動量
#define	CAMERA_VETCTOR		(12.0f)		//視点と注視点の距離
#define	CAMERA_TIMER		(1)		//カメラ停止時間

//***************************************************************
//	クラス定義
//***************************************************************
class	CCamera
{
public:
	CCamera();														//インストラクタ
	~CCamera();														//デストラクタ

	//カメラの処理分け
	typedef	enum
	{
		NOMAL_CAMERA = 0,		//通常時
		TITLE_CAMERA,			//タイトル時のカメラ
		PLAYER_CAMERA,			//プレイヤー追尾カメラ
		MAUSE_CAMERA,			//マウスによる移動方法
		ROT_CAMERA,				//回転モード
		IVENT_CAMERA,			//イベント発生時
		CAMERA_MAX,
	}CAMERA_MODE;

	static	HRESULT	Init(int	mode);											//初期化
	void	Uninit(void);												//終了
	void	Update(void);												//更新
	static	void	SetCamera(LPDIRECT3DDEVICE9	pDevice);				//カメラのセッティング
	static	D3DXMATRIX	GetViewMatrix(void);							//ビュー情報取得
	static	D3DXVECTOR3	GetCameraRot(void){return	m_Rot;};			//カメラ回転の情報取得
	static	int	GetCameraMode(void){return	m_CameraMode;};				//カメラモードの情報取得
	static	void	SetCameraMode(int	mode){m_CameraMode = mode;};	//カメラモードの切り替え
	void	PlayerCamera(void);											//プレイヤー追尾関数
private:
	//カメラポジション変数
	static	D3DXVECTOR3	m_posCameraP;								//カメラ座標
	static	D3DXVECTOR3	m_posCameraR;								//カメラ注視点
	static	D3DXVECTOR3	m_posCameraU;								//カメラ↑方向ベクトル

	static	D3DXMATRIX	m_mtxView;									//ビューマトリックス
	static	D3DXMATRIX	m_mtxProjection;							//プロジェクションマトリックス

	static	D3DXVECTOR3	m_Rot;										//カメラ回転変数
	static	int	m_CameraTimer;										//カメラ停止時間
	static	float	Time;										//カメラ線形補完用変数
	static	int	m_CameraMode;										//カメラモード変数

};



#endif