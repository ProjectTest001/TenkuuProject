//***************************************************************
//
//	camera.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/30
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<math.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"camera.h"
#include	"renderer.h"
#include	"manager.h"
#include	"player.h"
#include	"game.h"

//***************************************************************
//	静的変数
//***************************************************************
D3DXVECTOR3	CCamera::m_posCameraP;					//座標
D3DXVECTOR3	CCamera::m_posCameraR;					//注視点
D3DXVECTOR3	CCamera::m_posCameraU;					//↑方向ベクトル
D3DXVECTOR3	CCamera::m_Rot;							//角度
D3DXMATRIX	CCamera::m_mtxView;						//ビューマトリックス
D3DXMATRIX	CCamera::m_mtxProjection;				//プロジェクション
int	CCamera::m_CameraTimer = 0;						//タイマー
float	CCamera::Time = 0.0f;						//線形補間数値
int	CCamera::m_CameraMode = NOMAL_CAMERA;			//カメラモード
//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CCamera::CCamera()
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CCamera::~CCamera()
{

}

//***************************************************************
//	初期化
//	引数：
//	int	mode:カメラモード
//	戻り値：
//	HRESULT：終了コード
//***************************************************************
HRESULT	CCamera::Init(int	mode)
{
	//カメラ座標
	m_posCameraP = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//注視点
	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//↑方向のベクトル値
	m_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//カメラの角度
	m_Rot.y = -0.5f;

	//カメラ停止時間
	m_CameraTimer = CAMERA_TIMER;

	//カメラ線形補完用変数
	Time = 0.0f;

	//カメラモードの初期化
	m_CameraMode = mode;

	return	S_OK;
}

//***************************************************************
//	終了
//	引数：
//	なし
//	戻り値：
//	なし
//***************************************************************
void	CCamera::Uninit()
{

}

//***************************************************************
//	更新
//	引数：
//	なし
//	戻り値：
//	なし
//***************************************************************
void	CCamera::Update()
{

	//モードによってカメラの更新内容が変わる
	switch(m_CameraMode)
	{
		//通常
		case	NOMAL_CAMERA:

			break;
		//タイトル用カメラ
		case	TITLE_CAMERA:

			break;
		//ゲーム内のプレイヤーを追うためのカメラ
		case	PLAYER_CAMERA:
			PlayerCamera();
		break;
		//マウス操作用カメラ
		case	MAUSE_CAMERA:

			break;
		//回転用カメラ
		case	ROT_CAMERA:

			break;
		//イベント用カメラ
		case	IVENT_CAMERA:

			break;

	}
}

//***************************************************************
//	ビュー情報取得
//	引数：
//	なし
//	戻り値：
//	D3DXMATRIX：カメラのビュー情報
//***************************************************************
D3DXMATRIX	CCamera::GetViewMatrix(void)
{
	return	m_mtxView;
}

//***************************************************************
//	カメラのセッティング
//	引数：
//	LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//	戻り値：
//	なし
//***************************************************************
void	CCamera::SetCamera(LPDIRECT3DDEVICE9	pDevice)
{
		//カメラの設定
		D3DXMatrixIdentity(&m_mtxView);

		//ビュー設定
		D3DXMatrixLookAtLH(&m_mtxView,
							&m_posCameraP,
							&m_posCameraR,
							&m_posCameraU);

		//ビューをセット
		pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);

		//プロジェクション初期化
		D3DXMatrixIdentity(&m_mtxProjection);

		//プロジェクション設定
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
											D3DXToRadian(60),
											(float)SCREEN_WIDTH / SCREEN_HEIGHT,
											0.1f,
											1000.0f);

		//プロジェクションをセット
		pDevice->SetTransform(D3DTS_PROJECTION,
									&m_mtxProjection);

}

//**********************************************************
//	プレイヤー追尾用カメラ関数
//	引数
//	なし
//	戻り値
//	なし
//**********************************************************
void	CCamera::PlayerCamera(void)
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

	//プレイヤーの位置情報取得
	VERTEX_3D	Player = CGame::GetPlayer();

	//Yキーでカメラ修正
	if(pKeyBoard->GetkeyboardPress(DIK_Y))
	{
		Player.MoveFlag = false;
		m_CameraTimer = 0;
	}

	//プレイヤーが死んだら強制終了
	if(Player.Scail_vtx.x != 1.0f)
	{
		return;
	}

			if(Player.MoveFlag)
			{
		/*
				D3DXVECTOR3	EPos =  D3DXVECTOR3(sinf(D3DX_PI * Player.Scail_vtx.y) * (2.0f + Player.Scail_vtx.y) , 0.0f, cosf(D3DX_PI * Player.Scail_vtx.y) * (2.0f + Player.Scail_vtx.y));
				D3DXVECTOR3	SPos = D3DXVECTOR3(sinf(D3DX_PI * Player.Scail_vtx.x) * (2.0f + Player.Scail_vtx.x) , 0.0f, cosf(D3DX_PI * Player.Scail_vtx.x) * (2.0f + Player.Scail_vtx.x));

				if(m_posCameraR != EPos)
				{
					if(Time <= 0.9f)
					{
						Time += 0.03f;
					}
					else
					{
						Time = 0.0f;
					}
				}

				//カメラ自動更新
				m_posCameraR = Player.vtx + (SPos + (EPos - SPos) * Time);
		*/
				//カメラ自動更新
				m_posCameraR = Player.vtx + D3DXVECTOR3(sinf(D3DX_PI * Player.Rot_vtx.y) * (2.0f + Player.Speed_vtx.x) ,
														0.6f,
														cosf(D3DX_PI * Player.Rot_vtx.y) * (2.0f + Player.Speed_vtx.z));;

				m_posCameraP = m_posCameraR + D3DXVECTOR3(sinf(D3DX_PI * m_Rot.y + D3DX_PI) * CAMERA_VETCTOR,
															6.0f - Player.vtx.y + CScene3d::GetHeight(Player.vtx) + Player.PosNowY,
															cosf(D3DX_PI * m_Rot.y + D3DX_PI) * CAMERA_VETCTOR);
				if(pKeyBoard->GetkeyboardPress(DIK_Y))
				{
					m_CameraTimer = 0;
				}
				else
				{
					m_CameraTimer = CAMERA_TIMER;
				}
			}
			else
			{
				m_CameraTimer--;
				if(m_CameraTimer < 0)
				{
				m_posCameraR = Player.vtx + D3DXVECTOR3(sinf(D3DX_PI * Player.Rot_vtx.y) * (2.0f + Player.Speed_vtx.x) ,
														0.6f,
														cosf(D3DX_PI * Player.Rot_vtx.y) * (2.0f + Player.Speed_vtx.z));;

					//目的の見る角度
					float	PurposeRot = Player.Rot_vtx.y;
					
					//現在のカメラ角度と目的の角度の差分を算出
					float	ResultRot =  PurposeRot - m_Rot.y;

						while(ResultRot >= 1)
						{
							ResultRot -= 1 * 2;
						}

						while(ResultRot <= -1)
						{
							ResultRot += 1 * 2;
						}

					//今回の見る角度を算出
					m_Rot.y += ResultRot * 0.02f;

					//カメラ移動
					m_posCameraP.x = m_posCameraR.x +  sinf(D3DX_PI * m_Rot.y + D3DX_PI) * CAMERA_VETCTOR;
					m_posCameraP.z = m_posCameraR.z +  cosf(D3DX_PI * m_Rot.y + D3DX_PI) * CAMERA_VETCTOR;
				}
			}

}



