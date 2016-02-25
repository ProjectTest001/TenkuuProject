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
FRUSTUM	CCamera::m_frustum = {NULL};
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
											300.0f);

		//�v���W�F�N�V�������Z�b�g
		pDevice->SetTransform(D3DTS_PROJECTION,
									&m_mtxProjection);

		//�����䐶��
		MakeFrustum();

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
	else
	{
		Player.MoveFlag = true;
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

//******************************************
//	�����䐶���֐�
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//******************************************
void	CCamera::MakeFrustum()
{
	//�R�_�v�Z�ϐ��錾
	D3DXVECTOR3	p0,p1,p2;
	float	fTan = tan(D3DXToRadian(60) * 0.5f);
	float	fTanDivAspect = fTan /  (float)(SCREEN_WIDTH / SCREEN_HEIGHT);
	float	fFarMulTan = 300.0f * fTan;
	float	fFarMulTanDivAspect = 300.0f * fTanDivAspect;

	m_frustum.NearClip = 0.1f;
	m_frustum.FarClip = 300.0f;

	//�����ʐ���
	p0.x = 0.0f;	p0.y = 0.0f;	p0.z = 0.0f;
	p1.x = -fFarMulTanDivAspect;	p1.y = -fFarMulTan;	p1.z = 300.0f;
	p2.x = p1.x;	p2.y = -p1.y;	p2.z = p1.z;

	MakePlaneFrom3Points(p0,p1,p2,m_frustum.LeftPlane);

	//�E���ʐ���
	p0.x = 0.0f;	p0.y = 0.0f;	p0.z = 0.0f;
	p1.x = fFarMulTanDivAspect;	p1.y = fFarMulTan;	p1.z = 300.0f;
	p2.x = p1.x;	p2.y = -p1.y;	p2.z = p1.z;

	MakePlaneFrom3Points(p0,p1,p2,m_frustum.RightPlane);

	//�㕽�ʐ���
	p0.x = 0.0f;	p0.y = 0.0f;	p0.z = 0.0f;
	p1.x = -fFarMulTanDivAspect;	p1.y = fFarMulTan;	p1.z = 300.0f;
	p2.x = -p1.x;	p2.y = p1.y;	p2.z = p1.z;

	MakePlaneFrom3Points(p0,p1,p2,m_frustum.TopPlane);

	//�����ʐ���
	p0.x = 0.0f;	p0.y = 0.0f;	p0.z = 0.0f;
	p1.x = fFarMulTanDivAspect;	p1.y = -fFarMulTan;	p1.z = 300.0f;
	p2.x = -p1.x;	p2.y = p1.y;	p2.z = p1.z;

	MakePlaneFrom3Points(p0,p1,p2,m_frustum.BottomPlane);


}

//******************************************
//	���ʐ����֐�
//	����
//	D3DXVECTOR3 &p0:�P�_��
//	D3DXVECTOR3 &p1:�Q�_��
//	D3DXVECTOR3 &p2:�R�_��
//	�߂�l
//	�Ȃ�
//******************************************
void	CCamera::MakePlaneFrom3Points(D3DXVECTOR3 &p0, D3DXVECTOR3 &p1, D3DXVECTOR3 &p2,PLANE	&Plane)
{
	D3DXVECTOR3	v0,v1,v2;

	v0 = p1 - p0;
	v1 = p2 - p0;

	//�O��
	D3DXVec3Cross(&v2,&v0,&v1);

	//���K��(v2);
	D3DXVec3Normalize(&v2,&v2);

	Plane.a = v2.x;	Plane.b = v2.y;	Plane.c = v2.z;
	Plane.d = -( (v2.x * p0.x ) + ( v2.y * p0.y ) + (v2.z * p0.z ) );
}


bool	CCamera::IsView_CullFrustum(D3DXVECTOR3 &BSPos, float BSRad)
{
	float	Dist;
	D3DXVECTOR3	vViewPos;
	vViewPos.z = m_mtxView._13 * BSPos.x + m_mtxView._23 * BSPos.y + m_mtxView._33 * BSPos.z + m_mtxView._43;

	//�O�����e�ʂ���O�̏ꍇ
	if( ( vViewPos.z + BSRad ) < m_frustum.NearClip)
	{
		return	false;
	}

	//������e�ʂ�艜
	if( ( vViewPos.z - BSRad ) > m_frustum.FarClip)
	{
		return	false;
	}

	vViewPos.x = m_mtxView._11 * BSPos.x + m_mtxView._21 * BSPos.y + m_mtxView._31 * BSPos.z + m_mtxView._41;
	Dist = (vViewPos.x * m_frustum.LeftPlane.a ) + (vViewPos.z * m_frustum.LeftPlane.c);
	//�����ʂ��o�Ă���
	if( Dist > BSRad)
	{
		return	false;
	}

	Dist = (vViewPos.x * m_frustum.RightPlane.a ) + (vViewPos.z * m_frustum.RightPlane.c);
	//�E���ʂ��o�Ă���
	if( Dist > BSRad)
	{
		return	false;
	}

	vViewPos.y = m_mtxView._12 * BSPos.x + m_mtxView._22 * BSPos.y + m_mtxView._32 * BSPos.z + m_mtxView._42;
	Dist = (vViewPos.y * m_frustum.TopPlane.b ) + (vViewPos.z * m_frustum.TopPlane.c);
	//�㑤�ʂ��o�Ă���
	if( Dist > BSRad)
	{
		return	false;
	}

	Dist = (vViewPos.y * m_frustum.BottomPlane.b ) + (vViewPos.z * m_frustum.BottomPlane.c);
	//�����ʂ��o�Ă���
	if(Dist > BSRad)
	{
		return	false;
	}


	//�J�����͈͓̔��̏ꍇ
	return	true;
}

//************************************************
//	�J�����̋����𑪂�֐�
//	����
//	D3DXVECTOR3 pPos:�Ώۂ̍��W
//	�߂�l
//	float:����
//************************************************
float	CCamera::CalcLenZCamera2Object(D3DXVECTOR3 pPos)
{
#if	1
	D3DXVECTOR3	vLook(m_mtxView._13,m_mtxView._23,m_mtxView._33);
	float	fZ = D3DXVec3Dot(&pPos,&vLook);

	fZ += m_mtxView._43;
#else
	D3DXVECTOR3	vLook = m_posCameraR - m_posCameraP;

	//���K��(v2);
	D3DXVec3Normalize(&vLook,&vLook);

	float	fZ = D3DXVec3Dot(&pPos,&vLook);

	fZ += -D3DXVec3Dot(&m_posCameraP,&vLook);

#endif

	return(fZ);
}

