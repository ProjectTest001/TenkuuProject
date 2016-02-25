//*****************************************************************************
//
//	player.cpp
//	name�FMasatugu Kamada
//	create
//	�X�V���F2012/05/25
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
#include	"scene3d.h"
#include	"scene_x.h"
#include	"enemy.h"
#include	"manager.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"camera.h"
#include	"player.h"
#include	"shadow.h"
#include	"texture.h"
#include	"game.h"

//*****************************************************************************
//	�ÓI�ϐ�
//*****************************************************************************

//*****************************************************************************
//
//	�v���C���[�N���X�֐�
//
//*****************************************************************************

//*****************************************************************************
//	�R���X�g���N�^
//*****************************************************************************
CEnemy::CEnemy()
{

}

//*****************************************************************************
//	�f�X�g���N�^
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
//	�G����
//	�����F
//	LPDIRECT3DDEVICE9	pDevice:�f�o�C�X�|�C���^
//	D3DXVECTOR3	vtx:���W
//	D3DXVECTOR3	rot:�����p�x
//	float	speed:�ړ���
//	float	rotspeed:��]���x
//	float	jumpup:�W�����v��
//	int	Type:�s���^�C�v
//	�߂�l�F
//	CEnemy�F���N���X
//*****************************************************************************
CEnemy	*CEnemy::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,float	rotspeed,float	jumpup,int	Type,int	TexNo)
{
	CEnemy	*pEnemy;
	pEnemy = new	CEnemy;
	pEnemy->Init(pDevice,vtx,rot,speed,rotspeed,jumpup,Type,TexNo);

	return	pEnemy;

}
//*****************************************************************************
//	������
//	�����F
//	LPDIRECT3DDEVICE9	pDevice:�f�o�C�X�|�C���^
//	D3DXVECTOR3	vtx:���W
//	D3DXVECTOR3	rot:�����p�x
//	float	speed:�ړ���
//	float	rotspeed:��]���x
//	float	jumpup:�W�����v��
//	int	Type:�s���^�C�v
//	�߂�l�F
//	HRESULT�F�I���R�[�h
//*****************************************************************************
HRESULT	CEnemy::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,
					 float	rotspeed,float	jumpup,int	nType,int	TexNo)
{
		//���f���ǂݍ���
	if( FAILED(D3DXLoadMeshFromX("model/�G.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"�ǂݍ���","�G���[",MB_OK);

		}

	//�X�e�[�^�X������
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vertex_3d.Scail_vtx = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Vertex_3d.Rot_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	type = nType;
	m_aEnamy.Speed = speed;
	m_aEnamy.RotSpeed = rotspeed;
	m_aEnamy.JumpUp = jumpup;
	m_aEnamy.Vec = 25.0f;
	m_nTex = TexNo;

	return	S_OK;
}

//*****************************************************************************
//	�I��
//*****************************************************************************
void	CEnemy::Uninit()
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

	//�����[�X
	CScene::Release();

}

//*****************************************************************************
//	�X�V
//*****************************************************************************
void	CEnemy::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

	//�v���C���[�̈ʒu���擾
	VERTEX_3D	Player = CGame::GetPlayer();

	//�J�����ϐ��Ǝ擾
	D3DXVECTOR3	CameraRot = CCamera::GetCameraRot();

	//�n�ʂ̍����̎擾�ϐ�
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//�ߋ��̍��W���L�^
	D3DXVECTOR3	oldVtx = m_Vertex_3d.vtx;

	//�^�C�v���̏���
	switch(type)
	{
		case	NOMAL_MOVE:
			//�ړ�����
		m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
		m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

		//�w�苗������
		if(m_Vertex_3d.Speed_vtx.z > 0.0f)
		{
			m_aEnamy.Vec -= m_Vertex_3d.Speed_vtx.z;
		}
		else
		{
			m_aEnamy.Vec += m_Vertex_3d.Speed_vtx.z;
		}

		//���ȏ�̋����܂ōs�����ꍇ
		if(m_aEnamy.Vec < 0.0f)
		{
			m_Vertex_3d.Rot_vtx.y += 1.0f;
			m_aEnamy.Vec = 25.0f;
		}
			break;
		case	ROLING:
		//��]
			m_Vertex_3d.Rot_vtx.y += m_aEnamy.RotSpeed;

			//�ړ�����
		m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
		m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

			break;

		case	JUMPING:
		if(m_Vertex_3d.vtx.y == pScene3d->GetHeight(m_Vertex_3d.vtx))
		{
			//�W�����v
			m_Vertex_3d.Speed_vtx.y = m_aEnamy.JumpUp;
		}

			break;
		case	ROLL_JUMPING:
		//��]
			m_Vertex_3d.Rot_vtx.y += m_aEnamy.RotSpeed;

		if(m_Vertex_3d.vtx.y == pScene3d->GetHeight(m_Vertex_3d.vtx))
		{
			//�W�����v
			m_Vertex_3d.Speed_vtx.y = m_aEnamy.JumpUp;
		}

		//�ړ�����
		m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
		m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

			break;
		case	PLAYER_JUMPING:

		if(m_Vertex_3d.vtx.y == pScene3d->GetHeight(m_Vertex_3d.vtx) && pKeyBoard->GetkeyboardPress(DIK_SPACE))
		{
			//�W�����v
			m_Vertex_3d.Speed_vtx.y = m_aEnamy.JumpUp;
		}

		break;

		//�ǐ�
		case	TRACKING:
            // ��]�p�x�v�Z

            // ���όv�Z
            float cos1;                                          // �p�x cos ��
			cos1 = m_Vertex_3d.vtx.x * Player.vtx.x + m_Vertex_3d.vtx.z * Player.vtx.z;	// ����
			m_Vertex_3d.Rot_vtx.y = cos( cos1 );                // �x���ɕϊ�

			//�ړ�
			m_Vertex_3d.Speed_vtx.x += sin(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;
			m_Vertex_3d.Speed_vtx.z += cos(m_Vertex_3d.Rot_vtx.y * D3DX_PI) * m_aEnamy.Speed;

			break;
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

	//�����蔻��
	//�v���C���[�ƐڐG�����ꍇ
	if(HitEnemy(CGame::GetPlayer().vtx))
	{
		CPlayer::PlayerDeath();
	}

	//�n�ʂɂ��邩�̔���
	if(m_Vertex_3d.vtx.y < pScene3d->GetHeight(m_Vertex_3d.vtx))
	{
		//�����̎w��
		m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx);
	}

	//�e����
	//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3);

}

//*****************************************************************************
//	�`��
//	�����F
//	LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//	�߂�l�F
//	�Ȃ�
//*****************************************************************************
void	CEnemy::Draw(LPDIRECT3DDEVICE9	pDevice)
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

//*****************************************************************************
//	�G�Ƃ̓����蔻��
//	�����F
//	D3DXVECTOR3	pos:�Ώۂ̍��W
//	�߂�l
//	bool:�����蔻��
//*****************************************************************************
bool	CEnemy::HitEnemy(D3DXVECTOR3 Pos)
{
	bool	Hit = false;

	if(m_Vertex_3d.vtx.x - 1.5f < Pos.x && m_Vertex_3d.vtx.x + 1.5f> Pos.x &&
		m_Vertex_3d.vtx.y - 1.5f < Pos.y && m_Vertex_3d.vtx.y + 1.5f> Pos.y &&
		m_Vertex_3d.vtx.z - 1.5f < Pos.z && m_Vertex_3d.vtx.z + 1.5f> Pos.z)
		{
			Hit= true;
		}

	return	Hit;
}
