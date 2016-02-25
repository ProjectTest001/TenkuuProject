//*****************************************************************************
//
//	player.cpp
//	name�FMasatugu Kamada
//	�X�V���F2012/06/25
//
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h
//*****************************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<stdio.h>
#include	<math.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene_x.h"
#include	"item.h"
#include	"player.h"
#include	"manager.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"camera.h"
#include	"scene3d.h"
#include	"field.h"
#include	"enemy.h"
#include	"number.h"
#include	"score.h"
#include	"ster.h"
#include	"time.h"
#include	"gimmick.h"
#include	"debugproc.h"
#include	"shadow.h"
#include	"texture.h"
#include	"shine.h"
#include	"xfile.h"
#include	"model.h"
#include	"script.h"

//*****************************************************************************
//	�ÓI�ϐ�
//*****************************************************************************
bool	CPlayer::m_bDeath = false;
MOTIONDATA	*CPlayer::m_apKey = NULL;

//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
int	g_spanshot = SPAN_SHOT;

//���f���̃p�[�c�̈ʒu�ƌ������
static	float	g_akeyDefault[MODELPARTS_MAX][6] = 
{
	//���W				//�p�x
	{0.0f,2.3f,0.0f,  0.0f,0.0f,0.0f},			//��
	{0.0f,0.2f,0.0f,  0.0f,0.0f,0.0f},			//�g��
	{0.0f,2.6f,0.0f,  0.0f,0.0f,0.0f},			//��
	{0.0f,0.1f,0.0f,  0.0f,0.0f,0.0f},			//��
	{0.05f,1.75f,0.0f,  0.0f,0.0f,0.0f},		//�E�r
	{0.75f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//�E�I
	{0.73f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//�E��
	{-0.05f,1.75f,0.0f,  0.0f,0.0f,0.0f},		//���r
	{-0.75f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//���I
	{-0.73f,0.0f,0.0f,  0.0f,0.0f,0.0f},			//����
	{-0.1f,-0.43f,0.0f,  0.0f,0.0f,0.0f},			//�E������
	{0.0f,-0.75f,0.0f,  0.0f,0.0f,0.0f},			//�E�G
	{0.0f,-0.7f,0.0f,  0.0f,0.0f,0.0f},			//�E��
	{0.1f,-0.43f,0.0f,  0.0f,0.0f,0.0f},			//��������
	{0.0f,-0.75f,0.0f,  0.0f,0.0f,0.0f},			//���G
	{0.0f,-0.7f,0.0f,  0.0f,0.0f,0.0f},			//����
};

//*****************************************************************************
//
//	�v���C���[�N���X�֐�
//
//*****************************************************************************

//*****************************************************************************
//	�R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer()
{

}

//*****************************************************************************
//	�f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
//	�v���C���[����
//*****************************************************************************
CPlayer	*CPlayer::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo)
{
	CPlayer	*pPlayer;
	pPlayer = new	CPlayer;
	pPlayer->Init(pDevice,vtx,rot,TexNo);

	return	pPlayer;
}
//*****************************************************************************
//	������
//*****************************************************************************
HRESULT	CPlayer::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo)
{
		//���f���ǂݍ���
	if( FAILED(D3DXLoadMeshFromX("model/�_�l��.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"�ǂݍ���","�G���[",MB_OK);
		}

	//�X�e�[�^�X������
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vertex_3d.Scail_vtx = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Vertex_3d.Rot_vtx = rot;
	m_bDeath = false;
	clear = false;
	m_pSceneLink = NULL;
	m_Vertex_3d.PosNowY = 0.0f;
	m_nTex = TexNo;

	//���g�̉e�̐�����������
	m_pShadow = new	CShadow();
	m_pShadow->Init(pDevice,m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),D3DXVECTOR3(1,1,1),0,SHADOW_TEXTURE);

	//�p�[�c������
	for(int	i = LSB_ID; i < LSB_ID + LSB_NUM; i++)
	{
		//���f���f�[�^����
		m_apModel[i] = CModel::Create(pDevice,i,D3DXVECTOR3(g_akeyDefault[i][0],g_akeyDefault[i][1],g_akeyDefault[i][2]),
								D3DXVECTOR3(g_akeyDefault[i][3],g_akeyDefault[i][4],g_akeyDefault[i][5]),BLUE_TEXTURE);
	}
	//���f���K�w�\���ݒ�
	m_apModel[MODELPARTS_WAIST]->SetParent(NULL);
	m_apModel[MODELPARTS_BODY]->SetParent(m_apModel[MODELPARTS_WAIST]);
	m_apModel[MODELPARTS_NECK]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_HEAD]->SetParent(m_apModel[MODELPARTS_NECK]);
	m_apModel[MODELPARTS_RIGHTARM]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_RIGHTELBOW]->SetParent(m_apModel[MODELPARTS_RIGHTARM]);
	m_apModel[MODELPARTS_RIGHTHAND]->SetParent(m_apModel[MODELPARTS_RIGHTELBOW]);
	m_apModel[MODELPARTS_LEFTARM]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_LEFTELBOW]->SetParent(m_apModel[MODELPARTS_LEFTARM]);
	m_apModel[MODELPARTS_LEFTHAND]->SetParent(m_apModel[MODELPARTS_LEFTELBOW]);
	m_apModel[MODELPARTS_RIGHTLEG]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_RIGHTKNEE]->SetParent(m_apModel[MODELPARTS_RIGHTLEG]);
	m_apModel[MODELPARTS_RIGHTFOOT]->SetParent(m_apModel[MODELPARTS_RIGHTKNEE]);
	m_apModel[MODELPARTS_LEFTLEG]->SetParent(m_apModel[MODELPARTS_BODY]);
	m_apModel[MODELPARTS_LEFTKNEE]->SetParent(m_apModel[MODELPARTS_LEFTLEG]);
	m_apModel[MODELPARTS_LEFTFOOT]->SetParent(m_apModel[MODELPARTS_LEFTKNEE]);

	//���[�V�����f�[�^�擾
	m_apKey = CScript::GetPlayerMotion();

	//���[�V�����̐ݒ�
	m_motionType = MOTIONTYPE_NEUTRAL;

	switch(m_motionType)
	{
		case	MOTIONTYPE_NEUTRAL:
			m_pKeyInfo = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_NEUTRAL].NumFrame;
			m_bLoopMotion = true;

			break;
	}

	m_nKey = 0;
	m_nCountMotion = 0;
	m_bMotion = false;
	m_bFinishMotion = false;

	m_pKeyInfoBlend = NULL;
	m_nNumBlend = 0;
	m_nKeyBlend = 0;
	m_nCountMotionBlend = 0;
	m_bLoopMotionBlend = false;

	m_nFrameBlend = 0;					//�u�����h����ۂɂ�����t���[����
	m_nCountBlend = 0;					//�u�����h���̃J�E���^
	m_bBlendMotion = false;				//�u�����h���邩�ǂ���
	m_bBlendNow = false;

	return	S_OK;
}

//*****************************************************************************
//	�I��
//*****************************************************************************
void	CPlayer::Uninit()
{
	//�������

	//���b�V�����
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�o�b�t�@���
	if(m_pD3DXMatBuff != NULL)
	{
		m_pD3DXMatBuff->Release();
		m_pD3DXMatBuff = NULL;
	}

}

//*****************************************************************************
//	�X�V
//*****************************************************************************
void	CPlayer::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

	//�J�����ϐ��Ǝ擾
	D3DXVECTOR3	CameraRot = CCamera::GetCameraRot();

	//�n�ʂ̍����̎擾�ϐ�
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//�ߋ��̍��W���L�^
	D3DXVECTOR3	oldVtx = m_Vertex_3d.vtx;

	//�M�~�b�N�̉e���𔽉f������
	if(m_pSceneLink)
	{
			//�M�~�b�N���擾
			VERTEX_3D	pVtx;
			m_pSceneLink->GetVtx(&pVtx);

			m_Vertex_3d.vtx += pVtx.Speed_vtx;
			//m_Vertex_3d.Rot_vtx.y += 0.005f;

		//�v���C���[�̊p�x�̏C��
		while(m_Vertex_3d.Rot_vtx.y >= 1)
		{
			m_Vertex_3d.Rot_vtx.y -= 1 * 2;
		}

		while(m_Vertex_3d.Rot_vtx.y <= -1)
		{
			m_Vertex_3d.Rot_vtx.y += 1 * 2;
		}

	}
	//�v���C���[�̍���̊p�x

	//���S�����ꍇ
	if(m_bDeath)
	{
		//���S�G�t�F�N�g����
		m_Vertex_3d.Scail_vtx -= D3DXVECTOR3(0.02f,0.02f,0.02f);
		m_Vertex_3d.Rot_vtx.y += 0.2f;
		m_Vertex_3d.vtx.y += 0.1f;

		//�v���C���[�����ł�����Q�[���I��
		if(m_Vertex_3d.Scail_vtx.x < 0.0f)
		{
			CScene::Release();
			CManager::ChangeMode(CManager::MODE_REZULT_GAMEOVER);
		}

		//�ȉ��̏������s�킸�ɏI��
		return;
	}

	//�ړ�����
		//���ړ�
	if(pKeyBoard->GetkeyboardPress(DIK_W))
	{
		//�p�x�w��
		if(pKeyBoard->GetkeyboardPress(DIK_D))
		{
			PurposeRot = 0.25f + CameraRot.y;
		}
		else	if(pKeyBoard->GetkeyboardPress(DIK_A))
		{
			PurposeRot = -0.25f + CameraRot.y;
		}
		else
		{
			PurposeRot = 0.0f + CameraRot.y;
		}

			ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;

	}
	//��O�ړ�
	else	if(pKeyBoard->GetkeyboardPress(DIK_S))
	{
		if(pKeyBoard->GetkeyboardPress(DIK_D))
		{
			PurposeRot = 0.75f + CameraRot.y;
		}
		else	if(pKeyBoard->GetkeyboardPress(DIK_A))
		{
			PurposeRot = -0.75f + CameraRot.y;
		}
		else
		{
			PurposeRot = 1.0f + CameraRot.y;
		}

		ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;

	}
	//���ړ�
	else	if(pKeyBoard->GetkeyboardPress(DIK_A))
	{
		PurposeRot = -0.5f + CameraRot.y ;

		ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;

	}
	//�E�ړ�
	else	if(pKeyBoard->GetkeyboardPress(DIK_D))
	{
		//�ړI�̊p�x�̎w��
		PurposeRot = 0.5f + CameraRot.y;

		//�p�x�̌��ʂ��v�Z
		ResultRot =  PurposeRot - m_Vertex_3d.Rot_vtx.y;

		m_Vertex_3d.MoveFlag = true;
	}
	else
	{
		m_Vertex_3d.MoveFlag = false;
	}

	//�ړ�����
	if(m_Vertex_3d.MoveFlag)
	{
		while(ResultRot >= 1)
		{
			ResultRot -= 1 * 2;
		}

		while(ResultRot <= -1)
		{
			ResultRot += 1 * 2;
		}

		m_Vertex_3d.Rot_vtx.y += ResultRot * PLAYER_ROT;

		m_Vertex_3d.Speed_vtx.x += sin(D3DX_PI * PurposeRot) * MOVE;
		m_Vertex_3d.Speed_vtx.z += cos(D3DX_PI * PurposeRot) * MOVE;

		if(!jump && !m_bMotion)
		{
			if(m_bBlendMotion)
			{
				m_bBlendMotion = false;
			}
			SetMotion(MOTIONTYPE_WALK,10,m_bMotion);
		}
	}
	else
	{
		if(GetMotion() == MOTIONTYPE_WALK)
		{
			m_bFinishMotion = true;
		}
	}

	//�W�����v
	if(pKeyBoard->GetkeyboardTrigger(DIK_SPACE) && !jump)
	{
		m_Vertex_3d.Speed_vtx.y = 1.0f;
		SetMotion(MOTIONTYPE_JUMP,10,false);
	}
	else	if(pKeyBoard->GetkeyboardTrigger(DIK_1))
	{
		SetMotion(MOTIONTYPE_PUNCH,10,m_bMotion);
	}
	//�d��
	m_Vertex_3d.Speed_vtx.y -= 0.03f;

	//��C��R
	m_Vertex_3d.Speed_vtx.y -= m_Vertex_3d.Speed_vtx.y * 0.05f;

	//��R���C
	m_Vertex_3d.Speed_vtx.x -= m_Vertex_3d.Speed_vtx.x * 0.2f;
	m_Vertex_3d.Speed_vtx.z -= m_Vertex_3d.Speed_vtx.z * 0.2f;

	//�ړ�
	m_Vertex_3d.vtx.x += m_Vertex_3d.Speed_vtx.x;
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;
	m_Vertex_3d.vtx.z += m_Vertex_3d.Speed_vtx.z;

	//�R�C����S�Ď擾������
	if(CScore::GetScore() >= 500 && !clear)
	{
		CSter::Create(CRenderer::GetDevice(),D3DXVECTOR3(-48.0f,0.0f,48.0f),YEROWW_TEXTURE);
		clear = true;
	}
	//���ȏ㗎���Ŏ��S
	if(m_Vertex_3d.vtx.y < -5.0f)
	{
		m_bDeath = true;
		PlaySound(SE_00,false);
	}

	//���ԏI���ł��A�E�g
	if(CTime::TimeUp())
	{
		m_bDeath = true;
		PlaySound(SE_00,false);
	}

	//�n�ʂɂ��邩�̔���
	if(m_Vertex_3d.vtx.y < pScene3d->GetHeight(m_Vertex_3d.vtx))
	{
		//�����̎w��
		m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx);
		jump = false;
		if(m_motionType == MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_NEUTRAL,8,true);
		}

	}
	//���ɕ����Ă���ꍇ
	else
	{
		jump = true;
	}

	//�M�~�b�N�X�V����
	HitGimmick();

	//�ǂɂԂ��������̔���
	if(HitWall())
	{
		m_Vertex_3d.vtx = oldVtx;
	}

	//���[�V�����̍X�V
	UpdateMotion();

	//�P�����[�V�������I�������ꍇ
	if(m_bFinishMotion)
	{
			if(m_bBlendMotion)
			{
				m_bBlendMotion = false;
			}
			if(GetMotion() == MOTIONTYPE_WALK)
			{
				SetMotion(MOTIONTYPE_NEUTRAL,20,true);
			}
			else
			{
				SetMotion(MOTIONTYPE_NEUTRAL,10,false);
			}
			m_bMotion = false;
			m_bFinishMotion = false;
	}

}

//*****************************************************************************
//	�`��
//	�����F
//	LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//	�߂�l�F
//	�Ȃ�
//*****************************************************************************
void	CPlayer::Draw(LPDIRECT3DDEVICE9	pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&m_mtxWorld);

			//�傫���ݒ�
			D3DXMatrixScaling(&mScale, 0.6f, 0.6f, 0.6f);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//�p�x�ݒ�
			D3DXMatrixRotationYawPitchRoll(&mRotate, D3DX_PI * m_Vertex_3d.Rot_vtx.y + D3DX_PI, D3DX_PI * m_Vertex_3d.Rot_vtx.x, D3DX_PI * m_Vertex_3d.Rot_vtx.z);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//���W�ݒ�
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x, m_Vertex_3d.vtx.y, m_Vertex_3d.vtx.z);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

			//�Z�b�e�B���O
			pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

		//���f���̊e�p�[�c�̕`��
		for(int	i = 0 ; i < MODELPARTS_MAX; i++)
		{
			if(m_apModel[i])
			{
				m_apModel[i]->Draw(pDevice);
			}
		}

}

//*********************************************
//	�ǂƂ̓����蔻��
//
//*********************************************
bool	CPlayer::HitWall(void)
{
	CDebugProc::Print("%f",m_Vertex_3d.vertex.x);
	bool	Hit = false;
	//�n�ʏ��擾
	VERTEX_3D	pField = CField::GetVertex();

	//�x�N�g���ϐ��錾
	const	D3DXVECTOR3	aVtx[4] = 
	{
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2) ),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//����
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//�E��
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//�E��
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2)),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//����
	};
	
	//�p�x������������̏C���ϐ�
	D3DXVECTOR3	aVtxNew[4];
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
		aVtxNew[nCount].x = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x + cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z;
		aVtxNew[nCount].z = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z - cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x;
	}


	//�����蔻�葪��
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
				//�e�ƕǂ̃x�N�g���֌W�̌v�Z
				D3DXVECTOR3	nVtx = aVtxNew[(int)(nCount + 1) % 4] - aVtxNew[nCount];
				D3DXVECTOR3	BulletVtx = m_Vertex_3d.vtx - aVtxNew[nCount];

			//�O�όv�Z�ŕ��̐����ɂȂ����ꍇ�A�����������ɂ���
			if( (nVtx.z * BulletVtx.x- nVtx.x * BulletVtx.z) < 0 )
			{
				Hit = true;
			}
	}

	return	Hit;
}

//*********************************************
//	�M�~�b�N�n�X�V����
//
//*********************************************
void	CPlayer::HitGimmick(void)
{
	//�M�~�b�N������
	m_pSceneLink = NULL;

	for(int	i = 0; i < MAX_LIST; i++)
	{
		CScene	*pScene = CScene::GetTopScene(i);
		while(pScene)
		{
			CScene	*pSceneNext = pScene->GetNext();
			CScene::OBJECT_TYPE	Type = pScene->GetType();

			//CGimmick�������ꍇ
			if(Type == CScene::TYPE_GIMMICK)
			{
				//�M�~�b�N�̂S���_�̕ϐ��錾
				D3DXVECTOR3	aVtxScene[4];

				//�M�~�b�N���擾
				VERTEX_3D	pVtx;
				pScene->GetVtx(&pVtx);

				//�M�~�b�N�p�x�ݒ�
				float	fValueSin = sinf(pVtx.Rot_vtx.y);
				float	fValueCos = cos(pVtx.Rot_vtx.y);
				D3DXVECTOR3	VtxMax = pVtx.vtx + pVtx.Scail_vtx;
				D3DXVECTOR3	VtxMin = pVtx.vtx - pVtx.Scail_vtx;

				aVtxScene[0] = D3DXVECTOR3(pVtx.vtx.x - pVtx.Scail_vtx.x ,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z + pVtx.Scail_vtx.z);
				aVtxScene[1] = D3DXVECTOR3(pVtx.vtx.x + pVtx.Scail_vtx.x,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z + pVtx.Scail_vtx.z);
				aVtxScene[2] = D3DXVECTOR3(pVtx.vtx.x + pVtx.Scail_vtx.x,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z - pVtx.Scail_vtx.z);
				aVtxScene[3] = D3DXVECTOR3(pVtx.vtx.x - pVtx.Scail_vtx.x,pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),pVtx.vtx.z - pVtx.Scail_vtx.z);
/*
				aVtxScene[0] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMin.x + fValueCos * VtxMax.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMax.z + fValueSin * VtxMin.x);

				aVtxScene[1] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMax.x + fValueCos * VtxMin.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMax.z - fValueSin * VtxMin.x);

				aVtxScene[2] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMax.x - fValueCos * VtxMin.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMin.z - fValueSin * VtxMax.x);

				aVtxScene[3] = D3DXVECTOR3( pVtx.vtx.x + fValueSin * VtxMin.x - fValueCos * VtxMax.z,
											pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx),
											pVtx.vtx.z + fValueCos * VtxMin.z + fValueSin * VtxMax.x);
*/
				int	HitCount = 0;
				for(int	nCount = 0 ; nCount < 4 ; nCount++)
				{
					//�e�ƕǂ̃x�N�g���֌W�̌v�Z
					D3DXVECTOR3	nVtx = aVtxScene[(int)(nCount + 1) % 4] - aVtxScene[nCount];
					D3DXVECTOR3	PlayerVtx = m_Vertex_3d.vtx - aVtxScene[nCount];

					//�v���C���[���͈͓��ɂ���
					if( (nVtx.z * PlayerVtx.x- nVtx.x * PlayerVtx.z) > 0 )
					{
						HitCount++;
					}

					if(HitCount >= 4)
					{
						//���ɂ���

						//�ォ��߂肱��ł��邩
						if(m_Vertex_3d.Speed_vtx.y < 1.2f && m_Vertex_3d.vtx.y < pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y &&
															m_Vertex_3d.vtx.y > pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx))
						{
							//�ʒu�␳
							m_Vertex_3d.PosNowY = m_Vertex_3d.vtx.y;
							m_Vertex_3d.vtx.y = pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y;
							jump = false;
							m_pSceneLink = pScene;
							//�e����
							//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//������߂肱��ł��邩
						else	if(m_Vertex_3d.Speed_vtx.y > 0.0f && m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y > pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) && 
															m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y < pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y)
						{
							//�ʒu�␳
							m_Vertex_3d.Speed_vtx.y = 0.0f;
							//�e����
							//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//���ɂ��邩
						else
						{
							m_Vertex_3d.PosNowY = 0.0f;
							//�e����
							//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
					}
				}
			}
			pScene  = pSceneNext;
		}
	}

	m_Vertex_3d.PosNowY = 0.0f;

	//�n�ʂ̍����̎擾�ϐ�
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//�e�z�u�w��
	m_pShadow->SetPos(D3DXVECTOR3(m_Vertex_3d.vtx.x,pScene3d->GetHeight(m_Vertex_3d.vtx),m_Vertex_3d.vtx.z));

}

//***************************************************
//	���[�V�����̐ݒ�
//	����
//	MOTIONTYPE	type�F���[�V�����^�C�v
//	int	nFrameBlend:�u�����h���̃J�E���^
//	bool	bBlend:�u�����h���邩�ǂ���
//	�߂�l
//	�Ȃ�
//***************************************************
void	CPlayer::SetMotion(CPlayer::MOTIONTYPE type,int	nFrameBlend,bool	bBlend)
{
	//�u�����h�������s���Ă���ꍇ
	if(m_bBlendMotion)
	{
		return;
	}

	m_motionType = type;
	switch(m_motionType)
	{
		//�������Ȃ�
	case	MOTIONTYPE_NEUTRAL:
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_NEUTRAL].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_NEUTRAL].NumFrame;
			m_bLoopMotion = true;
		}
		break;

		//����
	case	MOTIONTYPE_WALK:
		//�u�����h����ꍇ
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_WALK].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_WALK].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_WALK].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_WALK].NumFrame;
			m_bLoopMotion =true;
		}
		break;

		//�p���`
	case	MOTIONTYPE_PUNCH:
		//�u�����h����ꍇ
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_PUNCH].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_PUNCH].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_PUNCH].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_PUNCH].NumFrame;
			m_bLoopMotion =false;
		}

		break;

		//�L�b�N
	case	MOTIONTYPE_KICK:

		break;

	case	MOTIONTYPE_KICK2:

		break;

		//�W�����v
	case	MOTIONTYPE_JUMP:
		//�u�����h����ꍇ
		if(bBlend)
		{
			m_pKeyInfoBlend = &m_apKey[MOTIONTYPE_JUMP].pKey[0];
			m_nNumBlend = m_apKey[MOTIONTYPE_JUMP].NumFrame;
			m_bLoopMotionBlend = false;
		}
		else
		{
			m_pKeyInfo = &m_apKey[MOTIONTYPE_JUMP].pKey[0];
			m_nNumber = m_apKey[MOTIONTYPE_JUMP].NumFrame;
			m_bLoopMotion =false;
		}

		break;
	case	MOTIONTYPE_JUMPEND:

		break;
	case	MOTIONTYPE_HIT:
		break;

		
	}

	//�u�����h����ꍇ
	if(bBlend)
	{
		m_nKeyBlend = 0;
		m_nCountMotionBlend = 0;
		m_nFrameBlend = nFrameBlend;
		m_nCountBlend = 0;
		m_bBlendMotion = true;
	}
	else
	{
		m_nKey = 0;
		m_nCountMotion = 0;
		m_nCountBlend = 0;
		m_bMotion = true;
	}

	//m_bFinishMotion = false;
}

//******************************************************
//	���[�V�����̍X�V
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//******************************************************
void	CPlayer::UpdateMotion()
{
	for(int	i = 0; i < MODELPARTS_MAX ; i++)
	{
		KEY	*pKey,*pKeyNext;		//���݂̃L�[�Ǝ��̃L�[�|�C���^

		float	fDiffMotion;		//����
		float	fRateMotion;		//�Đ��t���[�������Βl

		float	fPosX,fPosY,fPosZ;		//���W
		float	fRotX,fRotY,fRotZ;		//�p�x

		//�L�[���̎擾
		if(!m_bBlendNow)
		{
			pKey = &m_pKeyInfo[m_nKey].aKEY[i];
		}
		else
		{
			pKey = &m_pKeyInfoBlend[m_nKeyBlend].aKEY[i];
		}

		//�L�[�J�E���g���ő吔�ł��A���[�v���[�V�����̏ꍇ
		if(m_nKey >= m_nNumber-1 && m_bLoopMotion)
		{
			pKeyNext = &m_pKeyInfo[0].aKEY[i];
		}
		//�L�[�J�E���g���ő吔�ł��A���[�v���[�V�����ł͂Ȃ��ꍇ
		else	if(m_nKey >= m_nNumber-1 && !m_bLoopMotion)
		{
			pKeyNext = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0].aKEY[i];
		}
		else	if(m_bBlendNow)
		{
			pKeyNext = &m_pKeyInfoBlend[m_nKeyBlend+1].aKEY[i];
		}
		else
		{
			pKeyNext = &m_pKeyInfo[m_nKey+1].aKEY[i];
		}

		fRateMotion = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

		//�u�����h���̏ꍇ
		if(m_bBlendMotion)
		{
			//�u�����h�p�ϐ��錾
			KEY	*pKeyBlend,*pKeyNextBlend;
			float	fDiffMotionBlend;			//����
			float	fRateMotionBlend;			//�Đ��t���[�������Βl
			float	fKeyCurrent;				//���݂̃��[�V�����̃|�[�Y��
			float	fKeyBlend;					//�u�����h���[�V�����̃|�[�Y��
			float	fDiffBlend;					//���݂̃��[�V�����̃|�[�Y�̒l�ƃu�����h���[�V�����̃|�[�Y�̒l�̍���
			float	fRateBlend;					//�u�����h�䗦

			pKeyBlend = &m_pKeyInfoBlend[m_nKeyBlend].aKEY[i];

				if(m_nKeyBlend >= m_nNumBlend-1 && m_bLoopMotionBlend)
				{
					pKeyNextBlend = &m_pKeyInfoBlend[0].aKEY[i];
				}
				else	if(m_nKeyBlend >= m_nNumBlend-1 && !m_bLoopMotionBlend)
				{
					pKeyNextBlend = &m_apKey[MOTIONTYPE_NEUTRAL].pKey[0].aKEY[i];
				}
				else
				{
					pKeyNextBlend = &m_pKeyInfoBlend[m_nKeyBlend+1].aKEY[i];
				}

			fRateMotionBlend = (float)m_nCountMotionBlend / (float)m_pKeyInfoBlend[m_nKeyBlend].nFrame;

			//�u�����h���[�V�����̌v�Z
			//�����[�V�����̍����v�Z
			fDiffMotion = pKeyNext->posx - pKey->posx;

			//�����[�V�����̃|�[�Y���v�Z
			fKeyCurrent = pKey->posx + (fDiffMotion * fRateMotion);

			//�����[�V�����ƃu�����h���[�V�����̍����v�Z
			fDiffMotionBlend = pKeyNextBlend->posx - pKeyBlend->posx;

			//�u�����h���[�V�������v�Z
			fKeyBlend = pKeyBlend->posx + (fDiffMotionBlend * fRateMotionBlend);

			//�u�����h�䗦�v�Z
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;

			//�|�[�Y�̍����v�Z
			fDiffBlend = fKeyBlend - fKeyCurrent;

			//�ϐ��w��i�w���W�j
			fPosX = fKeyCurrent + (fDiffBlend * fRateBlend);

			//�ȉ������v�Z��ʂ̕ϐ��Ɏw�肳����
			//�x���W
			fDiffMotion = pKeyNext->posy - pKey->posy;
			fKeyCurrent = pKey->posy + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->posy - pKeyBlend->posy;
			fKeyBlend = pKeyBlend->posy + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fPosY = fKeyCurrent + (fDiffBlend * fRateBlend);

			//�y���W
			fDiffMotion = pKeyNext->posz - pKey->posz;
			fKeyCurrent = pKey->posz + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->posz - pKeyBlend->posz;
			fKeyBlend = pKeyBlend->posz + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fPosZ = fKeyCurrent + (fDiffBlend * fRateBlend);

			//�w�p�x
			fDiffMotion = pKeyNext->rotx - pKey->rotx;
			fKeyCurrent = pKey->rotx + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->rotx - pKeyBlend->rotx;
			fKeyBlend = pKeyBlend->rotx + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fRotX = fKeyCurrent + (fDiffBlend * fRateBlend);

			//�x�p�x
			fDiffMotion = pKeyNext->roty - pKey->roty;
			while(fDiffMotion >= 1)
			{
				fDiffMotion -= 1 * 2;
			}
			while(fDiffMotion <= -1)
			{
				fDiffMotion += 1 * 2;
			}

			fKeyCurrent = pKey->roty + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->roty - pKeyBlend->roty;
			while(fDiffMotionBlend >= 1)
			{
				fDiffMotionBlend -= 1 * 2;
			}
			while(fDiffMotionBlend <= -1)
			{
				fDiffMotionBlend += 1 * 2;
			}

			fKeyBlend = pKeyBlend->roty + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fRotY = fKeyCurrent + (fDiffBlend * fRateBlend);

			//�y�p�x
			fDiffMotion = pKeyNext->rotz - pKey->rotz;
			fKeyCurrent = pKey->rotz + (fDiffMotion * fRateMotion);
			fDiffMotionBlend = pKeyNextBlend->rotz - pKeyBlend->rotz;
			fKeyBlend = pKeyBlend->rotz + (fDiffMotionBlend * fRateMotionBlend);
			fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
			fDiffBlend = fKeyBlend - fKeyCurrent;
			fRotZ = fKeyCurrent + (fDiffBlend * fRateBlend);

		}
		else
		{
			/*
			if(m_bBlendNow)
			{
				//�u�����h�p�ϐ��錾
				KEY	*pKeyBlend,*pKeyNextBlend;
				float	fDiffMotionBlend;			//����
				float	fRateMotionBlend;			//�Đ��t���[�������Βl
				float	fKeyCurrent;				//���݂̃��[�V�����̃|�[�Y��
				float	fKeyBlend;					//�u�����h���[�V�����̃|�[�Y��
				float	fDiffBlend;					//���݂̃��[�V�����̃|�[�Y�̒l�ƃu�����h���[�V�����̃|�[�Y�̒l�̍���
				float	fRateBlend;					//�u�����h�䗦

				pKeyBlend = &m_pKeyInfo[m_nKey].aKEY[i];

					if(m_nKey >= m_nNumber-1)
					{
						pKeyNextBlend = &m_pKeyInfo[0].aKEY[i];
					}
					else
					{
						pKeyNextBlend = &m_pKeyInfo[m_nKey+1].aKEY[i];
					}

				fRateMotionBlend = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

				//�u�����h���[�V�����̌v�Z
				//�����[�V�����̍����v�Z
				fDiffMotion = pKeyNext->posx - pKey->posx;

				//�����[�V�����̃|�[�Y���v�Z
				fKeyCurrent = pKey->posx + (fDiffMotion * fRateMotion);

				//�����[�V�����ƃu�����h���[�V�����̍����v�Z
				fDiffMotionBlend = pKeyNextBlend->posx - pKeyBlend->posx;

				//�u�����h���[�V�������v�Z
				fKeyBlend = pKeyBlend->posx + (fDiffMotionBlend * fRateMotionBlend);

				//�u�����h�䗦�v�Z
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;

				//�|�[�Y�̍����v�Z
				fDiffBlend = fKeyBlend - fKeyCurrent;

				//�ϐ��w��i�w���W�j
				fPosX = fKeyCurrent + (fDiffBlend * fRateBlend);

				//�ȉ������v�Z��ʂ̕ϐ��Ɏw�肳����
				//�x���W
				fDiffMotion = pKeyNext->posy - pKey->posy;
				fKeyCurrent = pKey->posy + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->posy - pKeyBlend->posy;
				fKeyBlend = pKeyBlend->posy + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fPosY = fKeyCurrent + (fDiffBlend * fRateBlend);

				//�y���W
				fDiffMotion = pKeyNext->posz - pKey->posz;
				fKeyCurrent = pKey->posz + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->posz - pKeyBlend->posz;
				fKeyBlend = pKeyBlend->posz + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fPosZ = fKeyCurrent + (fDiffBlend * fRateBlend);

				//�w�p�x
				fDiffMotion = pKeyNext->rotx - pKey->rotx;
				fKeyCurrent = pKey->rotx + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->rotx - pKeyBlend->rotx;
				fKeyBlend = pKeyBlend->rotx + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fRotX = fKeyCurrent + (fDiffBlend * fRateBlend);

				//�x�p�x
				fDiffMotion = pKeyNext->roty - pKey->roty;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}

				fKeyCurrent = pKey->roty + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->roty - pKeyBlend->roty;
				while(fDiffMotionBlend >= 1)
				{
					fDiffMotionBlend -= 1 * 2;
				}
				while(fDiffMotionBlend <= -1)
				{
					fDiffMotionBlend += 1 * 2;
				}

				fKeyBlend = pKeyBlend->roty + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fRotY = fKeyCurrent + (fDiffBlend * fRateBlend);

				//�y�p�x
				fDiffMotion = pKeyNext->rotz - pKey->rotz;
				fKeyCurrent = pKey->rotz + (fDiffMotion * fRateMotion);
				fDiffMotionBlend = pKeyNextBlend->rotz - pKeyBlend->rotz;
				fKeyBlend = pKeyBlend->rotz + (fDiffMotionBlend * fRateMotionBlend);
				fRateBlend = (float)m_nCountBlend / (float)m_nFrameBlend;
				fDiffBlend = fKeyBlend - fKeyCurrent;
				fRotZ = fKeyCurrent + (fDiffBlend * fRateBlend);

			}
			else
			{
			*/
				fDiffMotion = pKeyNext->posx - pKey->posx;
				fPosX = pKey->posx + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->posy - pKey->posy;
				fPosY = pKey->posy + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->posz - pKey->posz;
				fPosZ = pKey->posz + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->rotx - pKey->rotx;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}

				fRotX = pKey->rotx + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->roty - pKey->roty;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}
				fRotY = pKey->roty + (fDiffMotion * fRateMotion);

				fDiffMotion = pKeyNext->rotz - pKey->rotz;
				while(fDiffMotion >= 1)
				{
					fDiffMotion -= 1 * 2;
				}
				while(fDiffMotion <= -1)
				{
					fDiffMotion += 1 * 2;
				}
				fRotZ = pKey->rotz + (fDiffMotion * fRateMotion);
			//}
		}

		m_apModel[i]->SetVertex(D3DXVECTOR3(fPosX,fPosY,fPosZ));
		m_apModel[i]->SetRot(D3DXVECTOR3(fRotX,fRotY,fRotZ));
	}

	//�u�����h���̏ꍇ
	if(m_bBlendMotion)
	{
		m_nCountMotionBlend++;
		//�Y���̃L�[�̍Đ��t���[�����ɒB����
		if(m_nCountMotionBlend >= m_pKeyInfoBlend[m_nKeyBlend].nFrame)
		{
			//�P�����[�V�����ł��A�ŏI�L�[�ɒB����
			if(!m_bLoopMotionBlend && m_nKeyBlend >= m_nNumBlend -1)
			{
				m_bFinishMotion = true;
				m_nCountMotionBlend = 0;
				m_nKeyBlend = 0;
			}
			else	if(m_bLoopMotionBlend && m_nKey >= m_nNumber -1)
			{
				m_nKeyBlend = 0;
				m_nCountMotionBlend = 0;
			}
			else
			{
				if(m_motionType != MOTIONTYPE_JUMP)
				{
					m_nKeyBlend++;

					m_nCountMotionBlend = 0;
				}
			}

		}

		m_nCountBlend++;

		if(m_nCountBlend >= m_nFrameBlend)
		{
			m_nFrameBlend = 1;
			m_nCountBlend = 1;
		}

	}
	else
	{
		//�t���[���㏸
		if(m_motionType != MOTIONTYPE_JUMP || m_nCountMotion < m_pKeyInfo[m_nKey].nFrame)
		{
			m_nCountMotion++;
		}

		//�Y���̃L�[�̍Đ��t���[�����ɒB����
		if(m_nCountMotion >= m_pKeyInfo[m_nKey].nFrame)
		{
			//�P�����[�V�����ł��A�ŏI�L�[�ɒB����
			if(!m_bLoopMotion && m_nKey >= m_nNumber -1)
			{
				m_bFinishMotion = true;
				m_nCountMotion = 0;
				m_nKey = 0;
			}
			else	if(m_bLoopMotion && m_nKey >= m_nNumber -1)
			{
				m_nKey = 0;
				m_nCountMotion = 0;
			}
			else
			{
				if(m_motionType == MOTIONTYPE_JUMP && m_nKey <= m_nNumber)
				{

				}
				else
				{
					m_nKey++;
					m_nCountMotion = 0;
				}
			}
		}

	}
}
