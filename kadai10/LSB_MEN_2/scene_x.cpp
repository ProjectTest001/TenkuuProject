//***************************************************************
//
//	scene3d.cpp
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
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"manager.h"
#include	"scene.h"
#include	"scene_x.h"
#include	"texture.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//	����
//	int	nPriority�F�K�w�ԍ�
//	�C�j�V�����C�U
//	CScene(nPriority)�F�K�w�ԍ��󂯓n��
//	�߂�l
//	�Ȃ�
//***************************************************************
CScene_x::CScene_x(int	nPriority):CScene(nPriority)
{
	//������
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CScene_x::~CScene_x()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CScene_x::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo)
{
		//���f���ǂݍ���
	if( FAILED(D3DXLoadMeshFromX(Name,
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"�ǂݍ���","�G���[",MB_OK);

		}

	//������
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.Rot_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
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
CScene_x	*CScene_x::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo)
{
	//�|�C���^�錾
	CScene_x	*pScene_x;

	//�N���X����
	pScene_x = new	CScene_x;

	//������
	pScene_x->Init(pDevice ,vtx,Name,TexNo);

	return	pScene_x;

}
//***************************************************************
//	�I��
//***************************************************************
void	CScene_x::Uninit()
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
void	CScene_x::Update()
{
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

	if(m_Vertex_3d.vtx.y < 0.0f)
	{
		m_Vertex_3d.vtx.y = 0.0f;
	}
}
//***************************************************************
//	�`��
//***************************************************************
void	CScene_x::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&m_mtxWorld);

			//�傫���ݒ�
			D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//�p�x�ݒ�
			D3DXMatrixRotationYawPitchRoll(&mRotate, m_Vertex_3d.Rot_vtx.y,m_Vertex_3d.Rot_vtx.x,m_Vertex_3d.Rot_vtx.z);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//���W�ݒ�
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x,m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z);

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
