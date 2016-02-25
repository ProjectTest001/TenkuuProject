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
#include	"scene.h"
#include	"scene3d.h"
#include	"wall.h"
#include	"scenebillboard.h"
#include	"bullet.h"
#include	"field.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
bool	CWall::m_bHit = false;

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
CWall::CWall()
{
	//������
	m_pD3DVtxBuff = NULL;
}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CWall::~CWall()
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
HRESULT	CWall::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Rot,
					float	width,float	heght,int	cutX,int	cutY,int	TexNo)
{
	//���l������
	m_Vertex_3d.vtx = vtx;						//���W
	m_Vertex_3d.diffuse = color;				//�z�F
	m_Vertex_3d.Rot_vtx = Rot;					//��]�p�x
	m_Vertex_3d.vertex.x = (float)cutX + 1.0f;	//�w���W�̕������i�{�P�͒��_���̕⊮�j
	m_Vertex_3d.vertex.y = (float)cutY + 1.0f;	//�x���W�̕������i�{�P�͒��_���̕⊮�j
	m_Vertex_3d.Scail_vtx.x = width;			//��
	m_Vertex_3d.Scail_vtx.y = heght;			//����
	m_nTex = TexNo;

	//�C���f�b�N�X��
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) + (m_Vertex_3d.vertex.y - (m_Vertex_3d.vertex.y * 2 / 3) )) * 2;

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
					for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x ;x++)
					{
						int	nCount_i = yCount * (int)m_Vertex_3d.vertex.x + xCount;
						pv[nCount_i].vtx.x = (m_Vertex_3d.Scail_vtx.x / (-2)) + (m_Vertex_3d.Scail_vtx.x / (m_Vertex_3d.vertex.x - 1)) * (float)x;
						pv[nCount_i].vtx.y = m_Vertex_3d.Scail_vtx.y - (m_Vertex_3d.Scail_vtx.y / (m_Vertex_3d.vertex.y - 1)) * (float)y;
						pv[nCount_i].tex.x = (float)xCount;
						pv[nCount_i].tex.y = (float)yCount;
						pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
						pv[nCount_i].hor = D3DXVECTOR3(0.0f,0.0f,-1.0f) + pv[nCount_i].vtx;
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
					pi[n] = (a + 1) + (WORD)m_Vertex_3d.vertex.x;
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
//D3DXVECTOR3	Rot:��]�p�x
//float	width:��
//float	heght:����
//int	cutX:�w�̕�����
//int	cutY:�x�̕�����
//�߂�l
//CWall	���N���X
//***************************************************************
CWall	*CWall::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Rot,
					   float	width,float	heght,int	cutX,int	cutY,int	TexNo)
{
	//�|�C���^�錾
	CWall	*pWall;

	//�N���X����
	pWall = new	CWall;

	//������
	pWall->Init(pDevice, vtx, color,Rot,width,heght,cutX,cutY,TexNo);

	return	pWall;
}

//***************************************************************
//	�I��
//***************************************************************
void	CWall::Uninit()
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
void	CWall::Update()
{
	
}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CWall::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D	pField = CField::GetVertex();
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
	D3DXMatrixRotationYawPitchRoll(&mRotate, D3DXToRadian(m_Vertex_3d.Rot_vtx.y + pField.Rot_vtx.y),
												D3DXToRadian(m_Vertex_3d.Rot_vtx.x + pField.Rot_vtx.x),
												D3DXToRadian(m_Vertex_3d.Rot_vtx.z + pField.Rot_vtx.z));

	//����
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

	//���W�ݒ�
	D3DXMatrixTranslation(&mTrans, sinf(D3DXToRadian(m_Vertex_3d.Rot_vtx.y + pField.Rot_vtx.y)) * (m_Vertex_3d.vtx.x + (pField.Scail_vtx.x / 2)),
									m_Vertex_3d.vtx.y,
									cosf(D3DXToRadian(m_Vertex_3d.Rot_vtx.y + pField.Rot_vtx.y)) * (m_Vertex_3d.vtx.z + (pField.Scail_vtx.z / 2)));

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

