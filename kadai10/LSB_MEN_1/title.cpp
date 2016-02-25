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
#include	"sound.h"
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"scenebillboard.h"
#include	"title2d.h"
#include	"manager.h"
#include	"camera.h"
#include	"light.h"
#include	"field.h"
#include	"title.h"
#include	"texture.h"
#include	"fade.h"
//*****************************************************************************
//	静的変数
//*****************************************************************************
CRenderer	*CTitle::m_pRenderer = NULL;

//*****************************************************************************
//	インストラクタ
//*****************************************************************************
CTitle::CTitle()
{

}

//*****************************************************************************
//	デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{

}

//*****************************************************************************
//	初期化処理
//*****************************************************************************
HRESULT	CTitle::Init()
{
	//レンダラーの取得
	m_pRenderer = CManager::GetRenderer();

	//カメラの初期化
	CCamera::Init(CCamera::TITLE_CAMERA);

	//プレイヤー
	//CPlayer::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,-0.5f,0.0f));

	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(100.0f,-30.0f,0.0f),D3DXVECTOR2(512.0f,512.0f),CTitle2d::NONE,TITLE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(150.0f,550.0f,0.0f),D3DXVECTOR2(512.0f,30.0f),CTitle2d::NONE,TEXT2_TEXTURE);

	//風エフェクト画像
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(100.0f,20.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(210.0f,200.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(420.0f,240.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(230.0f,150.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(340.0f,500.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(550.0f,400.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(100.0f,20.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(610.0f,10.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(720.0f,290.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(830.0f,180.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(940.0f,510.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(50.0f,600.0f,0.0f),D3DXVECTOR2(100.0f,50.0f),CTitle2d::MOVE_TYPE,LINE_TEXTURE);

	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-SCREEN_WIDTH,0,0.0f),D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT),CTitle2d::MOVE_TUTORIAL,TUTORIAL_TEXTURE);

	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(280.0f,450.0f,0.0f),D3DXVECTOR2(512.0f,100.0f),CTitle2d::MOVE_KEY,TEXT_TEXTURE);

	PlaySound(BGM_01,true);
	return	S_OK;
}

//*****************************************************************************
//	終了
//*****************************************************************************
void	CTitle::Uninit()
{
	//解放処理
	CScene::UninitAll();

}

//*****************************************************************************
//	更新処理
//*****************************************************************************
void	CTitle::Update()
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

	if(pKeyBoard->GetkeyboardPress(DIK_RETURN))
	{
		if(CFade::GetStatus() == (int)CFade::NONE)
		{
			CManager::ChangeMode(CManager::MODE_GAME);
		}

	}

	m_pRenderer->Update();
}

//*****************************************************************************
//	描画処理
//*****************************************************************************
void	CTitle::Draw()
{
	m_pRenderer->Draw();
}