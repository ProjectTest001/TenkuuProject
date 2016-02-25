//***************************************************************
//
//	wall.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/29
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"renderer.h"
#include	"manager.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"wall.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"field.h"
#include	"shadow.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//	����
//	int	nPriority�F�K�w�ԍ�
//	�߂�l
//	�Ȃ�
//***************************************************************
CShadow::CShadow()
{
	//������
	m_pD3DVtxBuff = NULL;
}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CShadow::~CShadow()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//D3DXCOLOR	color�F�z�F�J���\
//D3DXVECTOR3	Rot:��]�p�x
//float	width:��
//float	heght:����
//int	cutX:�w�̕�����
//int	cutY:�x�̕�����
//�߂�l
//HRESULT:�I���R�[�h
//***************************************************************
HRESULT	CShadow::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo)
{
	//�n�ʂ̍����̎擾�ϐ�
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//���l������
	m_Vertex_3d.vtx = vtx;						//���W
	m_Vertex_3d.vtx.y += 0.1f;
	m_Vertex_3d.diffuse = color;				//�z�F
	m_Vertex_3d.Scail_vtx = Scail;
	if(life != 0)
	{
		m_ShadowPoint = 1 / (float)life;
	}
	else
	{
		m_ShadowPoint = 0.0f;
	}
	m_nTex = TexNo;

	//�C���f�b�N�X��
	m_Vertex_3d.index = 4;

			//�o�b�t�@�ݒ�
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * 4,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}

			if(FAILED(pDevice->CreateIndexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.index,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff,
											NULL)))
			{
				return	E_FAIL;
			}

				//�A�����b�N�ϐ�
				VERTEX_3D	*pv;
				WORD	*pi;

					//���b�N����
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

					pv[0].vtx = D3DXVECTOR3(-0.5f,0.0f,0.5f);
					pv[1].vtx = D3DXVECTOR3(0.5f,0.0f,0.5f);
					pv[2].vtx = D3DXVECTOR3(-0.5f,0.0f,-0.5f);
					pv[3].vtx = D3DXVECTOR3(0.5f,0.0f,-0.5f);

					pv[0].diffuse = D3DXCOLOR(1,1,1,1);
					pv[1].diffuse = D3DXCOLOR(1,1,1,1);
					pv[2].diffuse = D3DXCOLOR(1,1,1,1);
					pv[3].diffuse = D3DXCOLOR(1,1,1,1);

					pv[0].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
					pv[1].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
					pv[2].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
					pv[3].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);

					pv[0].tex = D3DXVECTOR2(0.0f,0.0f);
					pv[1].tex = D3DXVECTOR2(1.0f,0.0f);
					pv[2].tex = D3DXVECTOR2(0.0f,1.0f);
					pv[3].tex = D3DXVECTOR2(1.0f,1.0f);


					//���b�N
					m_pD3DVtxBuff->Unlock();

					//�C���f�b�N�X�o�b�t�@�̃A�����b�N
					m_pD3DIndexBuff->Lock(0,0,(void**)&pi,0);

					pi[0] = 0;
					pi[1] = 1;
					pi[2] = 2;
					pi[3] = 3;


					//���b�N
					m_pD3DIndexBuff->Unlock();

	//�����̎w��
	m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx) + 0.1f;


	return	S_OK;
}

//***************************************************************
//	�|���S������
//�����F
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//D3DXCOLOR	color�F�z�F�J���\
//D3DXVECTOR3	Rot:��]�p�x
//float	width:��
//float	heght:����
//int	cutX:�w�̕�����
//int	cutY:�x�̕�����
//�߂�l
//CWall	���N���X
//***************************************************************
CShadow	*CShadow::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo)
{
	//�|�C���^�錾
	CShadow	*pWall;

	//�N���X����
	pWall = new	CShadow;

	//������
	pWall->Init(pDevice, vtx, color,Scail,life,TexNo);

	return	pWall;
}

//***************************************************************
//	�I��
//***************************************************************
void	CShadow::Uninit()
{
	//�������
	//�o�b�t�@���
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@���
	if(m_pD3DIndexBuff != NULL)
	{
		m_pD3DIndexBuff->Release();
		m_pD3DIndexBuff = NULL;
	}

		CScene::Release();

}

//***************************************************************
//	�X�V
//***************************************************************
void	CShadow::Update()
{
	//�n�ʂ̍����̎擾�ϐ�
	CScene3d	*pScene3d;
	pScene3d = CManager::GetScene3D();

	//�G�t�F�N�g����
	m_Vertex_3d.Scail_vtx.x -= m_ShadowPoint;
	m_Vertex_3d.Scail_vtx.y -= m_ShadowPoint;
	m_Vertex_3d.Scail_vtx.z -= m_ShadowPoint;

	//�����̎w��
	m_Vertex_3d.vtx.y = pScene3d->GetHeight(m_Vertex_3d.vtx) + 0.1f;

	if(m_Vertex_3d.Scail_vtx.x < 0.0f)
	{
		Uninit();
	}
}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CShadow::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::ADD);

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�傫���ݒ�
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

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

	//�o�b�t�@�w��
	pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pD3DIndexBuff);

		//�t�H�[�}�b�g�̎w��
		pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0,
				Texture);

			//�摜�\��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);


}

