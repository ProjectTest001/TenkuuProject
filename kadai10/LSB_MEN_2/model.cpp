//***************************************************************
//
//	model.cpp
//	name:Masatugu Kamada
//	update�F2012/11/05
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
//#include	"scene3d.h"
#include	"scene_x.h"
#include	"number.h"
#include	"score.h"
#include	"player.h"
#include	"manager.h"
#include	"game.h"
#include	"model.h"
#include	"texture.h"
#include	"xfile.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CModel::CModel()
{
	m_pParent = NULL;
}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CModel::~CModel()
{

}


//***************************************************************
//	������
//	����
//	LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//	int	nType:�e�ԍ�
//	D3DXVECTOR3	pos:���W
//	D3DXVECTOR3	rot:�p�x
//	int	TexNo:�摜�ԍ�
//	�߂�l
//	HRESULT:�I���R�[�h
//***************************************************************
HRESULT	CModel::Init(LPDIRECT3DDEVICE9	pDevice,int	nType,D3DXVECTOR3	pos,D3DXVECTOR3	rot,int	TexNo)
{
	m_nmodel = nType;


	//�X�e�[�^�X������
	m_Vertex_3d.vtx = pos;			//���W
	m_Vertex_3d.Rot_vtx = rot;		//�p�x
	m_nTex = TexNo;					//�摜�ԍ�

	return	S_OK;
}

//***************************************************************
//	����
//	����
//	LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//	int	nType:�e�ԍ�
//	D3DXVECTOR3	pos:���W
//	D3DXVECTOR3	rot:�p�x
//	int	TexNo:�摜�ԍ�
//	�߂�l
//	*CModel:���f���N���X�|�C���^
//***************************************************************
CModel	*CModel::Create(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int	TexNo)
{
	CModel	*pModel;

	pModel = new	CModel;
	pModel->Init(pDevice,nType,pos,rot,TexNo);

	return	pModel;
}

//***************************************************************
//	�I��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CModel::Uninit(void)
{

}

//***************************************************************
//	�X�V
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CModel::Update(void)
{

}


//*****************************************************************************
//	�`��
//	�����F
//	LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//	�߂�l�F
//	�Ȃ�
//*****************************************************************************
void	CModel::Draw(LPDIRECT3DDEVICE9	pDevice)
{
	//�p�[�c�̐e�}�g���b�N�X�錾
	D3DXMATRIX	mtxParent;

	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mRotate;		//��������W�A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�w�t�@�C�����擾�ϐ�
	LPD3DXMESH	pMesh = CXfile::GetMesh(m_nmodel);
	LPD3DXBUFFER	pBuffer = CXfile::GetBuffer(m_nmodel);
	DWORD	pWord = CXfile::GetWord(m_nmodel);

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�e���f�������݂���ꍇ
	if(m_pParent)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	//���݂��Ȃ��ꍇ
	else
	{
		pDevice->GetTransform(D3DTS_WORLD,&mtxParent);
	}

			//�p�x�ݒ�
			D3DXMatrixRotationYawPitchRoll(&mRotate, D3DX_PI * m_Vertex_3d.Rot_vtx.y, D3DX_PI * m_Vertex_3d.Rot_vtx.x, D3DX_PI * m_Vertex_3d.Rot_vtx.z);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//���W�ݒ�
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x, m_Vertex_3d.vtx.y, m_Vertex_3d.vtx.z);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

			//�e�}�g���b�N�X�Ǝ����̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxParent);

			//�Z�b�e�B���O
			pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

			//���b�V���ǂݍ���
			LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)pBuffer->GetBufferPointer();

			//�`��J�n
			for(unsigned int i = 0 ; i < pWord ; i++)
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
				pMesh->DrawSubset(i);
			}
			
		//�}�e���A�������ɖ߂�
		pMaterial->MatD3D.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
		pMaterial->MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pMaterial->MatD3D.Emissive = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pDevice->SetMaterial(&pMaterial->MatD3D);

}
