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

//*****************************************************************************
//	�ÓI�ϐ�
//*****************************************************************************
bool	CPlayer::m_bDeath = false;

//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
int	g_spanshot = SPAN_SHOT;

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
	}

	//�W�����v
	if(pKeyBoard->GetkeyboardTrigger(DIK_SPACE) && !jump)
	{
		m_Vertex_3d.Speed_vtx.y = 1.0f;
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

	//�ړ����Ă��邩�ǂ����̃t���O�w��
	if(m_Vertex_3d.vtx == oldVtx)
	{
		m_Vertex_3d.MoveFlag = false;
	}
	else
	{
		m_Vertex_3d.MoveFlag = true;
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

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&m_mtxWorld);

			//�傫���ݒ�
			D3DXMatrixScaling(&mScale, m_Vertex_3d.Scail_vtx.x, m_Vertex_3d.Scail_vtx.y, m_Vertex_3d.Scail_vtx.z);

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

		//���b�V���ǂݍ���
		LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)m_pD3DXMatBuff->GetBufferPointer();

			//�`��J�n
			for(unsigned int i = 0 ; i < m_nNumMat ; i++)
			{
				//�}�e���A���Z�b�g
				pDevice->SetMaterial(&pMaterial[i].MatD3D);

				if(Texture)
				{
					//�e�N�X�`���\��t��
					pDevice->SetTexture(0,
						Texture);
				}

				//�`��
				m_pMesh->DrawSubset(i);
			}
			
		//�}�e���A�������ɖ߂�
		pMaterial->MatD3D.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
		pMaterial->MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pMaterial->MatD3D.Emissive = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pDevice->SetMaterial(&pMaterial->MatD3D);

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
							CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//������߂肱��ł��邩
						else	if(m_Vertex_3d.Speed_vtx.y > 0.0f && m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y > pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) && 
															m_Vertex_3d.vtx.y + m_Vertex_3d.Scail_vtx.y < pVtx.vtx.y + CScene3d::GetHeight(pVtx.vtx) + pVtx.Scail_vtx.y)
						{
							//�ʒu�␳
							m_Vertex_3d.Speed_vtx.y = 0.0f;
							//�e����
							CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
						//���ɂ��邩
						else
						{
							m_Vertex_3d.PosNowY = 0.0f;
							//�e����
							CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);
							break;
						}
					}
				}
			}
			pScene  = pSceneNext;
		}
	}

	m_Vertex_3d.PosNowY = 0.0f;

	//�e����
	CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3,SHADOW_TEXTURE);

}

