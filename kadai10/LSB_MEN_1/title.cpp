//***************************************************************
//
//	title.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/07/11
//
//***************************************************************

//*****************************************************************************
//	�C���N���[�h
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
//	�ÓI�ϐ�
//*****************************************************************************
CRenderer	*CTitle::m_pRenderer = NULL;

//*****************************************************************************
//	�C���X�g���N�^
//*****************************************************************************
CTitle::CTitle()
{

}

//*****************************************************************************
//	�f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{

}

//*****************************************************************************
//	����������
//*****************************************************************************
HRESULT	CTitle::Init()
{
	//�����_���[�̎擾
	m_pRenderer = CManager::GetRenderer();

	//�J�����̏�����
	CCamera::Init(CCamera::TITLE_CAMERA);

	//�v���C���[
	//CPlayer::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,-0.5f,0.0f));

	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(100.0f,-30.0f,0.0f),D3DXVECTOR2(512.0f,512.0f),CTitle2d::NONE,TITLE_TEXTURE);
	CTitle2d::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(150.0f,550.0f,0.0f),D3DXVECTOR2(512.0f,30.0f),CTitle2d::NONE,TEXT2_TEXTURE);

	//���G�t�F�N�g�摜
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
//	�I��
//*****************************************************************************
void	CTitle::Uninit()
{
	//�������
	CScene::UninitAll();

}

//*****************************************************************************
//	�X�V����
//*****************************************************************************
void	CTitle::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

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
//	�`�揈��
//*****************************************************************************
void	CTitle::Draw()
{
	m_pRenderer->Draw();
}