//***************************************************************
//
//	game.cpp
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
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"manager.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"camera.h"
#include	"player.h"
#include	"scenebillboard.h"
#include	"light.h"
#include	"field.h"
#include	"mountion.h"
#include	"sky.h"
#include	"wall.h"
#include	"enemy.h"
#include	"item.h"
#include	"coin.h"
#include	"number.h"
#include	"score.h"
#include	"time.h"
#include	"game.h"
#include	"fade.h"
#include	"pose.h"
#include	"gimmick.h"
#include	"debugproc.h"
#include	"texture.h"
#include	"building.h"

//*****************************************************************************
//	�ÓI�ϐ�
//*****************************************************************************
CScene3d	*CGame::m_pScene3d = NULL;
CRenderer	*CGame::m_pRenderer = NULL;
CScore		*CGame::m_pScore = NULL;
CPose	*CGame::m_pPose = NULL;
CPlayer	*CGame::m_pPlayer[MAX_PLAYER] = {NULL};

//*****************************************************************************
//	�C���X�g���N�^
//*****************************************************************************
CGame::CGame()
{

}

//*****************************************************************************
//	�f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{

}

//*****************************************************************************
//	����������
//*****************************************************************************
HRESULT	CGame::Init()
{
	m_pRenderer = CManager::GetRenderer();
	PlaySound(BGM_00,true);
	//�J�����̏�����
	CCamera::Init(CCamera::PLAYER_CAMERA);

			//�X�R�A�̏�����
			if(FAILED(m_pScore->Create(m_pRenderer->GetDevice(),D3DXVECTOR3(400.0f,0.0f,0.0f),30,50 ) ))
			{
					MessageBox(NULL,"directX initialize",
								"error",MB_OK);
					return	-1;
			}

			//�^�C���̏�����
			if(FAILED(m_pTime->Create(m_pRenderer->GetDevice(),D3DXVECTOR3(50.0f,12.0f,0.0f),30,50 ) ))
			{
					MessageBox(NULL,"directX initialize",
								"error",MB_OK);
					return	-1;
			}

			//�n�ʐ���
			m_pScene3d = CField::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1,1,1,1),D3DXVECTOR3(0.0f,0.0f,0.0f),
				100.0f,100.0f,16,16,FIELD_TEXTURE);

		//�ǐ���
		CWall::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1,1,1,1),D3DXVECTOR3(0.0f,0.0f,0.0),100.0f,30.0f,20,20,WALL_TEXTURE);
		CWall::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1,1,1,1),D3DXVECTOR3(0.0f,90.0f,0.0),100.0f,30.0f,20,20,WALL_TEXTURE);
		CWall::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1,1,1,1),D3DXVECTOR3(0.0f,180.0f,0.0),100.0f,30.0f,20,20,WALL_TEXTURE);
		CWall::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR(1,1,1,1),D3DXVECTOR3(0.0f,270.0f,0.0),100.0f,30.0f,20,20,WALL_TEXTURE);

		//�󐶐�
		CSky::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),250.0f,D3DXCOLOR(1,1,1,1),45,50,60,0,SKY_TEXTURE);
		CSky::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),250.0f,D3DXCOLOR(1,1,1,1),45,50,60,180,SKY_TEXTURE);

		//�w���f��
		//�v���C���[
		m_pPlayer[0] = new	CPlayer;
		m_pPlayer[0]->Init(m_pRenderer->GetDevice(),D3DXVECTOR3(49.0f,10.0f,49.0f),D3DXVECTOR3(0.0f,-0.5f,0.0f),WHITE_TEXTURE);

		//�G
		CEnemy::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-15.0f,0.0f,15.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),0.05f,0.01f,1.0f,CEnemy::ROLING,WHITE_TEXTURE);
		CEnemy::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-15.0f,0.0f,-15.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1.0f,0.5f,0.8f,CEnemy::JUMPING,WHITE_TEXTURE);
		CEnemy::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(48.0f,0.0f,-20.0f),D3DXVECTOR3(0.0f,-0.001f,0.0f),0.03f,0.5f,1.0f,CEnemy::NOMAL_MOVE,WHITE_TEXTURE);
		CEnemy::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(15.0f,0.0f,-15.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1.0f,0.5f,1.3f,CEnemy::PLAYER_JUMPING,WHITE_TEXTURE);
		CEnemy::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-3.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),0.07f,0.03f,1.0f,CEnemy::ROLL_JUMPING,WHITE_TEXTURE);
		//CEnemy::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(48.0f,0.0f,20.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),0.01f,0.03f,1.0f,CEnemy::TRACKING);

		//�R�C��
		CCoin::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,0.0f),YEROWW_TEXTURE);
		CCoin::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(37.5f,24.0f,12.375f),YEROWW_TEXTURE);
		CCoin::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-15.0f,0.0f,15.0f),YEROWW_TEXTURE);
		CCoin::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(15.0f,3.0f,-15.0f),YEROWW_TEXTURE);
		CCoin::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-15.0f,0.0f,-15.0f),YEROWW_TEXTURE);

		//��
		for(int	i = -50;i < 50 ; i++)
		{
			CBuilding::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(0.0f,0.0f,(float)i),D3DXCOLOR(1,1,1,1),D3DXVECTOR3(2.0f,3.0f,2.0f),TREE_TEXTURE);
		}

		//�M�~�b�N�i�ړ����j
		//CGimmick::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-40.0f,5.0f,42.0f),D3DXVECTOR3(5.0f,2.5f,5.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
		//CGimmick::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-40.0f,8.0f,35.0f),D3DXVECTOR3(5.0f,2.5f,5.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
		//CGimmick::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-35.0f,12.0f,31.0f),D3DXVECTOR3(5.0f,2.5f,5.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
		//CGimmick::Create(m_pRenderer->GetDevice(),D3DXVECTOR3(-30.0f,13.0f,28.0f),D3DXVECTOR3(5.0f,2.5f,5.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

		//�|�[�Y�ϐ�������
		m_pPose = new	CPose;
		m_pPose->Init(m_pRenderer->GetDevice());

		//���̑�
		m_bSwitch = false;
	return	S_OK;
}

//*****************************************************************************
//	�I��
//*****************************************************************************
void	CGame::Uninit()
{
	//�������
	CScene::UninitAll();
	m_pPose->Uninit();
	StopSound();
}

//*****************************************************************************
//	�X�V����
//*****************************************************************************
void	CGame::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

	//�|�[�Y��ʂɍs�����߂̏���
	if(pKeyBoard->GetkeyboardPress(DIK_P) && !m_bSwitch)
	{
		if(!m_pPose->GetPose())
		{
			m_pPose->SetPose(true);
		}
		else
		{
			m_pPose->SetPose(false);
		}
		m_bSwitch = true;
	}
	else
	{
		m_bSwitch = false;
	}


	if(!m_pPose->GetPose())
	{
		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}
	else
	{
		m_pPose->Update();
	}
}

//*****************************************************************************
//	�`�揈��
//*****************************************************************************
void	CGame::Draw()
{
	if(!m_pPose->GetPose())
	{
		m_pRenderer->Draw();
	}
	else
	{
		m_pPose->Draw(m_pRenderer->GetDevice());
	}
}