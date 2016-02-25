//***************************************************************
//
//	coin.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
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
#include	"scenebillboard.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"manager.h"
#include	"player.h"
#include	"gimmick.h"
#include	"texture.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
CGimmick::CGimmick()
{
	//������
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CGimmick::~CGimmick()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CGimmick::Init(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo)
{
		//���f���ǂݍ���
	if( FAILED(D3DXLoadMeshFromX("model/�M�~�b�N.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"�ǂݍ���","�G���[",MB_OK);

		}

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CGimmick::SetObjectType(CScene::TYPE_GIMMICK);

	//������
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Scail_vtx = Scail;
	m_Vertex_3d.Rot_vtx = rot;
	m_Vertex_3d.diffuse = D3DXCOLOR(1.0,0.0f,0.0f,1.0f);
	m_Vertex_3d.Speed_vtx = Speed;
	m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	�����֐�
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//D3DXVECTOR3 vtx�F�w����W
//�߂�l
//CScene_x	���N���X
//***************************************************************
CGimmick	*CGimmick::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo)
{
	//�|�C���^�錾
	CGimmick	*pGimmick;

	//�N���X����
	pGimmick = new	CGimmick;

	//������
	pGimmick->Init(pDevice, vtx,Scail,rot,Speed,TexNo);

	
	return	pGimmick;

}
//***************************************************************
//	�I��
//***************************************************************
void	CGimmick::Uninit()
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

	CScene::Release();
}

//***************************************************************
//	�X�V
//***************************************************************
void	CGimmick::Update()
{
	//�ړ�
	m_Vertex_3d.vtx.x += m_Vertex_3d.Speed_vtx.x;
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;
	m_Vertex_3d.vtx.z += m_Vertex_3d.Speed_vtx.z;

}
//***************************************************************
//	�`��
//***************************************************************
void	CGimmick::Draw(LPDIRECT3DDEVICE9 pDevice)
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
			D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//�p�x�ݒ�
			D3DXMatrixRotationYawPitchRoll(&mRotate,D3DX_PI * m_Vertex_3d.Rot_vtx.y + D3DX_PI,0.0f,0.0f);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//���W�ݒ�
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x,CScene3d::GetHeight(m_Vertex_3d.vtx) + 1.0f + m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z);

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

