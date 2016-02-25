//***************************************************************
//
//	title.cpp
//	name:Masatugu Kamada
//	更新日：2012/07/11
//
//***************************************************************

//*****************************************************************************
//	インクルード
//*****************************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	<dinput.h>
#include	"texture.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"scenebillboard.h"
#include	"manager.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"camera.h"
#include	"rezult.h"
#include	"sound.h"
#include	"fade.h"

//*****************************************************************************
//	静的変数
//*****************************************************************************
CRenderer	*CRezult::m_pRenderer = NULL;

//*****************************************************************************
//	インストラクタ
//*****************************************************************************
CRezult::CRezult()
{

}

//*****************************************************************************
//	デストラクタ
//*****************************************************************************
CRezult::~CRezult()
{

}

//*****************************************************************************
//	初期化処理
//*****************************************************************************
HRESULT	CRezult::Init(int	mode)
{
	m_pRenderer = CManager::GetRenderer();

	//カメラの初期化
	CCamera::Init(CCamera::NOMAL_CAMERA);

	switch(mode)
	{
		case	GAME_OVER:
			CScene_x::Create(m_pRenderer->GetDevice(),D3DXVECTOR3((float)(rand()%6 - 3),(float)(rand()%20 + 10),(float)(rand()%6 - 3)),GAME_OVER_TEXTURE_FILE1,WHITE_TEXTURE);
			CScene_x::Create(m_pRenderer->GetDevice(),D3DXVECTOR3((float)(rand()%6 - 3),(float)(rand()%20 + 10),(float)(rand()%6 - 3)),GAME_OVER_TEXTURE_FILE2,WHITE_TEXTURE);
			CScene_x::Create(m_pRenderer->GetDevice(),D3DXVECTOR3((float)(rand()%6 - 3),(float)(rand()%20 + 10),(float)(rand()%6 - 3)),GAME_OVER_TEXTURE_FILE3,WHITE_TEXTURE);
			CScene_x::Create(m_pRenderer->GetDevice(),D3DXVECTOR3((float)(rand()%6 - 3),(float)(rand()%20 + 10),(float)(rand()%6 - 3)),GAME_OVER_TEXTURE_FILE3,WHITE_TEXTURE);
			CScene_x::Create(m_pRenderer->GetDevice(),D3DXVECTOR3((float)(rand()%6 - 3),(float)(rand()%20 + 10),(float)(rand()%6 - 3)),GAME_OVER_TEXTURE_FILE3,WHITE_TEXTURE);
			CScene_x::Create(m_pRenderer->GetDevice(),D3DXVECTOR3((float)(rand()%6 - 3),(float)(rand()%20 + 10),(float)(rand()%6 - 3)),GAME_OVER_TEXTURE_FILE3,WHITE_TEXTURE);

			//CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(200.0f,400.0f,0.0f),D3DXVECTOR2(400,100),CTitle2d::REZULT_TYPE,GAME_OVER_TEXTURE);
			PlaySound(BGM_02,false);
			break;
		case	GAME_CLEAR:
			//CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT),CTitle2d::REZULT_TYPE,GAME_CLEAR_TEXTURE);
			PlaySound(BGM_03,false);
			break;
	}

	//時間初期化
	m_nTime = 0;

	return	S_OK;
}

//*****************************************************************************
//	終了
//*****************************************************************************
void	CRezult::Uninit()
{
	//解放処理
	CScene::UninitAll();
	StopSound();

}

//*****************************************************************************
//	更新処理
//*****************************************************************************
void	CRezult::Update()
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

	if(pKeyBoard->GetkeyboardPress(DIK_RETURN))
	{

		CManager::ChangeMode(CManager::MODE_TITLE);
	}

	m_pRenderer->Update();

	m_nTime++;

	if(m_nTime == 200)
	{
		//CScene2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(150.0f,-25.0f,0.0f),D3DXVECTOR2(512.0f,100.0f),CScene2d::MOVE_KEY,TEXT_TEXTURE);
	}
}

//*****************************************************************************
//	描画処理
//*****************************************************************************
void	CRezult::Draw()
{
	m_pRenderer->Draw();

}