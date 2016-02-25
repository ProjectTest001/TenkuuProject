//***************************************************************
//
//	manager.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/19
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"manager.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"camera.h"
#include	"scenebillboard.h"
#include	"light.h"
#include	"player.h"
#include	"number.h"
#include	"score.h"
#include	"time.h"
#include	"title.h"
#include	"game.h"
#include	"rezult.h"
#include	"fade.h"
#include	"debugproc.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
CRenderer	*CManager::m_pRenderer;
CInputKeyboard	*CManager::m_pInputkeyboard = NULL;
CCamera	*CManager::m_pCamera = NULL;
CLight	*CManager::m_pLight = NULL;
CScene3d	*CManager::m_pScene3d = NULL;
CScore		*CManager::m_pScore = NULL;
CTitle	*CManager::m_pTitle = NULL;
CGame	*CManager::m_pGame = NULL;
CRezult	*CManager::m_pRezult = NULL;
int	CManager::m_mode = MODE_TITLE;
int	CManager::m_amode = MODE_TITLE;
CFade	*CManager::m_pFade = NULL;
CDebugProc	*CManager::m_pDebug = NULL;
CTexture	*CManager::m_pTexture = NULL;

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CManager::CManager()
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CManager::~CManager()
{

}

//***************************************************************
//	������
//***************************************************************
HRESULT	CManager::Init(HINSTANCE	hInstance, HWND	hWnd, BOOL	bWindow)
{

	//�N���X����
	m_pRenderer = new	CRenderer;
	m_pCamera = new	CCamera;
	m_pLight = new	CLight;
	m_pTitle = new	CTitle;
	//m_pGame = new	CGame;
	m_pFade = new	CFade;
	m_pTexture = new	CTexture;
	//m_pDebug = new	CDebugProc;

		//DirectX������
		if(FAILED(m_pRenderer->Init(hWnd,bWindow)))
		{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
		}

		//�e�N�X�`��������
		if(FAILED(m_pTexture->Init(m_pRenderer->GetDevice())))
		{
					MessageBox(NULL,"directX initialize",
								"error",MB_OK);
					return	-1;
		}

		//���C�g�̏�����
		if(FAILED(m_pLight->Init(m_pRenderer->GetDevice())))
		{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
		}

		//�J�����̏�����
		if(FAILED(m_pCamera->Init(CCamera::PLAYER_CAMERA)))
		{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
		}

		//�L�[���͂̃N���X����
		m_pInputkeyboard = new	CInputKeyboard;

		//�L�[���͂̏�����
		m_pInputkeyboard->Init(hInstance,hWnd);

		//�t�F�[�h�̏�����
		m_pFade->Init(m_pRenderer->GetDevice(),FADE_TEXTURE);

		//�f�o�b�N�����̏�����
		//m_pDebug->Init(m_pRenderer->GetDevice());

	//�^�C�g��������
		if(FAILED(m_pTitle->Init()))
	{
				MessageBox(NULL,"directX initialize",
							"error",MB_OK);
				return	-1;
	}

	return	S_OK;
}


//***************************************************************
//	�I��
//***************************************************************
void	CManager::Uninit()
{
	//�������
	CScene::ReleaseAll();

	if(m_pRenderer)
	{
		m_pRenderer->Uninit();
		delete	m_pRenderer;
		m_pRenderer = NULL;
	}

	if(m_pInputkeyboard)
	{
		m_pInputkeyboard->Uninit();
		delete	m_pInputkeyboard;
		m_pInputkeyboard = NULL;
	}

	if(m_pLight)
	{
		m_pLight->Uninit();
		delete	m_pLight;
		m_pLight = NULL;
	}

	if(m_pTexture)
	{
		m_pTexture->UnInit();
		delete	m_pTexture;
		m_pTexture = NULL;
	}
}

//***************************************************************
//	�X�V
//***************************************************************
void	CManager::Update()
{
	//�L�[�{�[�h���͂̍X�V����
	m_pInputkeyboard->Update();

	//�t�F�[�h�X�V
	m_pFade->Update();

	//�t�F�[�h�C�����I�������烂�[�h�؂�ւ�
	if(m_pFade->GetStatus() == CFade::FADEIN_END)
	{
		SetMode((MODE)m_amode);
	}

	//�J�����̍X�V����
	m_pCamera->Update();

	switch(m_mode)
	{
	case	MODE_TITLE:

			m_pTitle->Update();

		break;

	case	MODE_GAME:

		m_pGame->Update();

		break;
	case	MODE_REZULT_CLEAR:
		m_pRezult->Update();
		break;

	case	MODE_REZULT_GAMEOVER:
		m_pRezult->Update();
		break;
	}
}

//***************************************************************
//	�`��
//***************************************************************
void	CManager::Draw()
{
	switch(m_mode)
	{
	case	MODE_TITLE:
		m_pTitle->Draw();
		break;
	case	MODE_GAME:
		m_pGame->Draw();
		break;

	case	MODE_REZULT_CLEAR:
		m_pRezult->Draw();
		break;

	case	MODE_REZULT_GAMEOVER:
		m_pRezult->Draw();
		break;
	}

	//�f�o�b�N�\��
	//m_pDebug->Draw();
}

//***************************************************
//	���[�h�؂�ւ��֐�
//	�����F
//	MODE	mode:�؂�ւ���̃��[�h�ϐ�
//	�߂�l�F
//	�Ȃ�
//***************************************************
void	CManager::SetMode(MODE	mode)
{
	//���[�h�؂�ւ�
	m_mode = mode;

	//���[�h�I������
	switch(m_mode)
	{
		case	MODE_TITLE:
		if(m_pRezult)
		{
			m_pRezult->Uninit();
			delete	m_pRezult;
			m_pRezult = NULL;
		}
		m_pTitle = new	CTitle;
		m_pTitle->Init();
			break;
		case	MODE_GAME:
			if(m_pTitle)
			{
				m_pTitle->Uninit();
				delete	m_pTitle;
				m_pTitle = NULL;
			}
			m_pGame = new	CGame;
			m_pGame->Init();

			break;
		case	MODE_REZULT_CLEAR:
			if(m_pGame)
			{
				m_pGame->Uninit();
				delete	m_pGame;
				m_pGame = NULL;
			}
			m_pRezult = new	CRezult;
			m_pRezult->Init(CRezult::GAME_CLEAR);

			break;
		case	MODE_REZULT_GAMEOVER:
			if(m_pGame)
			{
				m_pGame->Uninit();
				delete	m_pGame;
				m_pGame = NULL;
			}
			m_pRezult = new	CRezult;
			m_pRezult->Init(CRezult::GAME_OVER);

			break;
	}

	//�t�F�[�h�A�E�g�J�n
	m_pFade->Start(CFade::FADEOUT,60);
}

//**********************************************
//	���[�h�؂�ւ��֐�
//	����
//	MODE	mode�F�Ώۂ̃��[�h
//	�߂�l
//	�Ȃ�
//**********************************************
void	CManager::ChangeMode(MODE	mode)
{
	m_amode = mode;
	m_pFade->Start(CFade::FADEIN,60);
}