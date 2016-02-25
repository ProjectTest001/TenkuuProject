//***************************************************************
//
//	camera.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/30
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
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
//	�ÓI�ϐ�
//***************************************************************
D3DXVECTOR3	CCamera::m_posCameraP;					//���W
D3DXVECTOR3	CCamera::m_posCameraR;					//�����_
D3DXVECTOR3	CCamera::m_posCameraU;					//�������x�N�g��
D3DXVECTOR3	CCamera::m_Rot;							//�p�x
D3DXMATRIX	CCamera::m_mtxView;						//�r���[�}�g���b�N�X
D3DXMATRIX	CCamera::m_mtxProjection;				//�v���W�F�N�V����
int	CCamera::m_CameraTimer = 0;						//�^�C�}�[
float	CCamera::Time = 0.0f;						//���`��Ԑ��l
int	CCamera::m_CameraMode = NOMAL_CAMERA;			//�J�������[�h
//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CCamera::CCamera()
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CCamera::~CCamera()
{

}

//***************************************************************
//	������
//	�����F
//	int	mode:�J�������[�h
//	�߂�l�F
//	HRESULT�F�I���R�[�h
//***************************************************************
HRESULT	CCamera::Init(int	mode)
{
	//�J�������W
	m_posCameraP = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//�����_
	m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�������̃x�N�g���l
	m_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�J�����̊p�x
	m_Rot.y = -0.5f;

	//�J������~����
	m_CameraTimer = CAMERA_TIMER;

	//�J�������`�⊮�p�ϐ�
	Time = 0.0f;

	//�J�������[�h�̏�����
	m_CameraMode = mode;

	return	S_OK;
}

//***************************************************************
//	�I��
//	�����F
//	�Ȃ�
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CCamera::Uninit()
{

}

//***************************************************************
//	�X�V
//	�����F
//	�Ȃ�
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CCamera::Update()
{

	//���[�h�ɂ���ăJ�����̍X�V���e���ς��
	switch(m_CameraMode)
	{
		//�ʏ�
		case	NOMAL_CAMERA:

			break;
		//�^�C�g���p�J����
		case	TITLE_CAMERA:

			break;
		//�Q�[�����̃v���C���[��ǂ����߂̃J����
		case	PLAYER_CAMERA:
			PlayerCamera();
		break;
		//�}�E�X����p�J����
		case	MAUSE_CAMERA:

			break;
		//��]�p�J����
		case	ROT_CAMERA:

			break;
		//�C�x���g�p�J����
		case	IVENT_CAMERA:

			break;

	}
}

//***************************************************************
//	�r���[���擾
//	�����F
//	�Ȃ�
//	�߂�l�F
//	D3DXMATRIX�F�J�����̃r���[���
//***************************************************************
D3DXMATRIX	CCamera::GetViewMatrix(void)
{
	return	m_mtxView;
}

//***************************************************************
//	�J�����̃Z�b�e�B���O
//	�����F
//	LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CCamera::SetCamera(LPDIRECT3DDEVICE9	pDevice)
{
		//�J�����̐ݒ�
		D3DXMatrixIdentity(&m_mtxView);

		//�r���[�ݒ�
		D3DXMatrixLookAtLH(&m_mtxView,
							&m_posCameraP,
							&m_posCameraR,
							&m_posCameraU);

		//�r���[���Z�b�g
		pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);

		//�v���W�F�N�V����������
		D3DXMatrixIdentity(&m_mtxProjection);

		//�v���W�F�N�V�����ݒ�
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
											D3DXToRadian(60),
											(float)SCREEN_WIDTH / SCREEN_HEIGHT,
											0.1f,
											1000.0f);

		//�v���W�F�N�V�������Z�b�g
		pDevice->SetTransform(D3DTS_PROJECTION,
									&m_mtxProjection);

}

//**********************************************************
//	�v���C���[�ǔ��p�J�����֐�
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//**********************************************************
void	CCamera::PlayerCamera(void)
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

	//�v���C���[�̈ʒu���擾
	VERTEX_3D	Player = CGame::GetPlayer();

	//Y�L�[�ŃJ�����C��
	if(pKeyBoard->GetkeyboardPress(DIK_Y))
	{
		Player.MoveFlag = false;
		m_CameraTimer = 0;
	}

	//�v���C���[�����񂾂狭���I��
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

				//�J���������X�V
				m_posCameraR = Player.vtx + (SPos + (EPos - SPos) * Time);
		*/
				//�J���������X�V
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

					//�ړI�̌���p�x
					float	PurposeRot = Player.Rot_vtx.y;
					
					//���݂̃J�����p�x�ƖړI�̊p�x�̍������Z�o
					float	ResultRot =  PurposeRot - m_Rot.y;

						while(ResultRot >= 1)
						{
							ResultRot -= 1 * 2;
						}

						while(ResultRot <= -1)
						{
							ResultRot += 1 * 2;
						}

					//����̌���p�x���Z�o
					m_Rot.y += ResultRot * 0.02f;

					//�J�����ړ�
					m_posCameraP.x = m_posCameraR.x +  sinf(D3DX_PI * m_Rot.y + D3DX_PI) * CAMERA_VETCTOR;
					m_posCameraP.z = m_posCameraR.z +  cosf(D3DX_PI * m_Rot.y + D3DX_PI) * CAMERA_VETCTOR;
				}
			}

}



