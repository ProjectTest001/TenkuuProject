//***************************************************************
//
//	mountion.cpp
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
#include	"scene.h"
#include	"scene3d.h"
#include	"mountion.h"
#include	"texture.h"

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
CMountion::CMountion()
{
	//������
	m_pD3DVtxBuff = NULL;
	m_pD3DIndexBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CMountion::~CMountion()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//float	vec:�ő唼�a
//D3DXCOLOR	color�F�z�F�J���\
//int	cut:�~�̕�����
//float	heght:����
//int	cutY:�c�̕�����
//�߂�l
//HRESULT:�I���R�[�h
//***************************************************************
HRESULT	CMountion::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,int	cut,float	heght,int	cutY,int	TexNo)
{
	//���l������
	m_Vertex_3d.vtx = vtx;						//���W
	m_Vertex_3d.diffuse = color;				//�z�F
	m_Vertex_3d.vertex.y = (float)cutY + 1.0f;	//�x���W�̕������i�{�P�͒��_���̕⊮�j
	m_Vertex_3d.vertex.x = (float)cut + 1.0f;	//�~�̕������i�{�P�͒��_���̕⊮�j
	m_Vertex_3d.Scail_vtx.y = heght;			//����
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) + (m_Vertex_3d.vertex.y - (m_Vertex_3d.vertex.y * 2 / 3) )) * 2;
	m_nTex = TexNo;

			//�o�b�t�@�ݒ�
	if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y),
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

				//�摜�̏������̗���
				int	yCount = 0;
				int	xCount = 0;

				//�e���_���W��������
				for(int	y = 0 ; y < (int)m_Vertex_3d.vertex.y ; y++)
				{
					for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x;x++)
					{
						int	nCount_i = yCount * (int)m_Vertex_3d.vertex.x + xCount;
						pv[nCount_i].vtx.x = sinf((float)((D3DX_PI * 2) / cut) * x) * vec;
						pv[nCount_i].vtx.z = cosf((float)((D3DX_PI * 2) / cut) * x) * vec;
						pv[nCount_i].vtx.y = m_Vertex_3d.Scail_vtx.y - (m_Vertex_3d.Scail_vtx.y / (m_Vertex_3d.vertex.y - 1)) * (float)y;
						pv[nCount_i].tex.x = (float)xCount;
						pv[nCount_i].tex.y = (float)(1.0f / m_Vertex_3d.vertex.y) * y;
						pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
						pv[nCount_i].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						xCount++;
					}
					yCount++;
					xCount = 0;
				}
					//���b�N
					m_pD3DVtxBuff->Unlock();

					//�C���f�b�N�X�o�b�t�@�̃A�����b�N
					m_pD3DIndexBuff->Lock(0,0,(void**)&pi,0);

									//�C���f�b�N�X�������ݗp�ϐ��錾
				int	n = 0;	//�m�����ϐ�
				int	a;		//�i���o�[�ݒ�ϐ�

				//�C���f�b�N�X�ݒ�
			for(int	gz = 0; gz < (int)m_Vertex_3d.vertex.y - 1 ;gz++)
			{
				//�ŏ��̓X���[
				if(n != 0)
				{
					pi[n] = (a + 1) + (int)m_Vertex_3d.vertex.x;
					n++;
				}

					//�C���f�b�N�X��������
					for(int	gx = 0; gx < (int)m_Vertex_3d.vertex.x ;gx++)
					{
							a = gz * (int)m_Vertex_3d.vertex.x  + gx;

						pi[n+0] = a + (int)m_Vertex_3d.vertex.x;
						pi[n+1] = a;
						n += 2;
					}

				//�Ō�̓X���[
				if(gz != (int)m_Vertex_3d.vertex.y  - 1)
				{
					pi[n] = a;
					n++;
				}
			}
					//���b�N
					m_pD3DIndexBuff->Unlock();

	return	S_OK;
}

//***************************************************************
//	�|���S������
//�����F
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//D3DXCOLOR	color�F�z�F�J���\
//�߂�l
//CScene3d	���N���X
//***************************************************************
CMountion	*CMountion::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,int	cut,float	heght,int	cutY,int	TexNo)
{
	//�|�C���^�錾
	CMountion	*pMountion;

	//�N���X����
	pMountion = new	CMountion;

	//������
	pMountion->Init(pDevice, vtx,vec, color,cut,heght,cutY,TexNo);

	return	pMountion;
}

//***************************************************************
//	�I��
//***************************************************************
void	CMountion::Uninit()
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

}

//***************************************************************
//	�X�V
//***************************************************************
void	CMountion::Update()
{

}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CMountion::Draw(LPDIRECT3DDEVICE9 pDevice)
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
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

	//����
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

	//�p�x�ݒ�
	D3DXMatrixRotationYawPitchRoll(&mRotate, 0.0f, 0.0f, 0.0f);

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
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
											0,
											0,
											(UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y),
											0,
											(int)((m_Vertex_3d.vertex.x) * (m_Vertex_3d.vertex.y) * 2) );


}
