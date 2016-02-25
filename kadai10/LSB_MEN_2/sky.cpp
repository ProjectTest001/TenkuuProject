//***************************************************************
//
//	sky.cpp
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
#include	"sky.h"
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
CSky::CSky()
{
	//������
	m_pD3DVtxBuff = NULL;
	m_pD3DIndexBuff = NULL;
}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CSky::~CSky()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//D3DXCOLOR	color�F�z�F�J���\
//�߂�l
//HRESULT:�I���R�[�h
//***************************************************************
HRESULT	CSky::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
				   int	cut,float	heght,int	cutY,float	rot,int	TexNo)
{
	//���l������
	m_Vertex_3d.vtx = vtx;						//���W
	m_Vertex_3d.diffuse = color;				//�z�F
	m_Vertex_3d.vertex.y = (float)(cutY);	//�x���W�̕������i�{�P�͒��_���̕⊮�j
	m_Vertex_3d.vertex.x = (float)(cut + 1.0f);	//�~�̕������i�{�P�͒��_���̕⊮�j
	m_Vertex_3d.Rot_vtx.x = rot;
	m_Vertex_3d.Scail_vtx.y = heght;			//����
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) + (m_Vertex_3d.vertex.y - (m_Vertex_3d.vertex.y * 1 / 4) )) * 2;
	m_nTex = TexNo;

	//�󔽓]���̖@���΍�
	D3DXVECTOR3	nor;

	if(rot == 180.0f)
	{
		nor = D3DXVECTOR3(0.0f,-1.0f,0.0f);
	}
	else
	{
		nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	}
	//�o�b�t�@�ݒ�i�h�[���j
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.y) * 2,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}

			if(FAILED(pDevice->CreateIndexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.index * 2,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff,
											NULL)))
			{
				return	E_FAIL;
			}

			//�o�b�t�@�ݒ�i�t�^�j
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.vertex.x + 1,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff2,
											NULL)))
			{
				return	E_FAIL;
			}

			if(FAILED(pDevice->CreateIndexBuffer((sizeof(VERTEX_3D)) * (UINT)m_Vertex_3d.vertex.x + 2,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff2,
											NULL)))
			{
				return	E_FAIL;
			}

//*************************************************************
//�h�[������
//*************************************************************
				//�A�����b�N�ϐ�
				VERTEX_3D	*pv;
				WORD	*pi;

					//���b�N����
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//�摜�̏������̗���
				int	yCount = 0;
				int	xCount = 0;

				//�e���_���W��������
				for(int	y = 0 ; y < (int)m_Vertex_3d.vertex.y  ; y++)
				{
					for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x;x++)
					{
						int	nCount_i = yCount * (int)m_Vertex_3d.vertex.x + xCount;
						float	NewVec = (vec / cutY) * (y+1);
						pv[nCount_i].vtx.x = sinf(D3DXToRadian((float)(360.0f / cut) * x)) * NewVec;
						pv[nCount_i].vtx.z = cosf(D3DXToRadian((float)(360.0f / cut) * x)) * NewVec;
						pv[nCount_i].vtx.y = sinf(cosf(D3DXToRadian((float)(90.0f / cutY) * (y+1)))) * vec;
						pv[nCount_i].tex.x = (float)(1.0f / m_Vertex_3d.vertex.x) * x;
						pv[nCount_i].tex.y = (float)(1.0f / m_Vertex_3d.vertex.y) * y;
						pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
						pv[nCount_i].hor = nor;
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
				if(gz != (int)m_Vertex_3d.vertex.y )
				{
					pi[n] = a;
					n++;
				}
			}
					//���b�N
					m_pD3DIndexBuff->Unlock();

//***************************************************************
//�t�^����
//***************************************************************
				//�A�����b�N�ϐ�
				VERTEX_3D	*pv2;
				WORD	*pi2;

					//���b�N����
					m_pD3DVtxBuff2->Lock(0,0,(void**)&pv2,0);

						for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x ;x++)
						{
							if(x == 0)
							{
								pv2[x].vtx.x = 0.0f;
								pv2[x].vtx.z = 0.0f;
							}
							else
							{
								pv2[x].vtx.x = sinf(D3DXToRadian((float)(360.0f / cut) * (cut - (x-1) ))) * (vec / m_Vertex_3d.vertex.y);
								pv2[x].vtx.z = cosf(D3DXToRadian((float)(360.0f / cut) * (cut - (x-1) ))) * (vec / m_Vertex_3d.vertex.y);
							}
							pv2[x].vtx.y = sinf(cosf(D3DXToRadian(0.0f))) * vec;
							pv2[x].tex.x = (float)x;
							pv2[x].tex.y = 1.0f;
							pv2[x].diffuse = m_Vertex_3d.diffuse;
							pv2[x].hor = nor;
						}
					//���b�N
					m_pD3DVtxBuff2->Unlock();

					//�C���f�b�N�X�o�b�t�@�̃A�����b�N
					m_pD3DIndexBuff2->Lock(0,0,(void**)&pi2,0);

						for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x + 1;x++)
						{
							if(x == (int)m_Vertex_3d.vertex.x)
							{
								pi2[x] = 1;
							}
							else
							{
								pi2[x] = x;
							}
						}
					//���b�N
					m_pD3DIndexBuff2->Unlock();

		m_Vertex_3d.Rot_vtx.y = 0.0f;

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
CSky	*CSky::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
					  int	cut,float	heght,int	cutY,float	rot,int	TexNo)
{
	//�|�C���^�錾
	CSky	*pSky;

	//�N���X����
	pSky = new	CSky;

	//������
	pSky->Init(pDevice, vtx,vec, color,cut,heght,cutY,rot,TexNo);

	return	pSky;
}

//***************************************************************
//	�I��
//***************************************************************
void	CSky::Uninit()
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

	//�o�b�t�@���
	if(m_pD3DVtxBuff2 != NULL )
	{
		m_pD3DVtxBuff2->Release();
		m_pD3DVtxBuff2 = NULL;
	}

	//�C���f�b�N�X�o�b�t�@���
	if(m_pD3DIndexBuff2 != NULL)
	{
		m_pD3DIndexBuff2->Release();
		m_pD3DIndexBuff2 = NULL;
	}

}

//***************************************************************
//	�X�V
//***************************************************************
void	CSky::Update()
{
	m_Vertex_3d.Rot_vtx.y += 0.001f;
}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CSky::Draw(LPDIRECT3DDEVICE9 pDevice)
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
	D3DXMatrixRotationYawPitchRoll(&mRotate, m_Vertex_3d.Rot_vtx.y,0.0f, D3DXToRadian(m_Vertex_3d.Rot_vtx.x));

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
											(int)((m_Vertex_3d.vertex.x) * (m_Vertex_3d.vertex.y) * 3) );

	//�o�b�t�@�w��
	pDevice->SetStreamSource(0,m_pD3DVtxBuff2,0,sizeof(VERTEX_3D));
	pDevice->SetIndices(m_pD3DIndexBuff2);

			//�摜�\��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,
											0,
											0,
											(UINT)m_Vertex_3d.vertex.x + 3,
											0,
											(int)((m_Vertex_3d.vertex.x) + 3) );

}
