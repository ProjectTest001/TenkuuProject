//***************************************************************
//
//	field.cpp
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
#include	"field.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
VERTEX_3D	CField::m_Vertex_3d;

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
CField::CField()
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CField::~CField()
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
HRESULT	CField::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
					 D3DXVECTOR3	Rot,float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo)
{
	//���l������
	m_Vertex_3d.vtx = vtx;							//���W
	m_Vertex_3d.diffuse = color;
	m_Vertex_3d.Rot_vtx = Rot;
	m_Vertex_3d.Scail_vtx.x = Xwidth;
	m_Vertex_3d.Scail_vtx.z = Zwidth;
	m_Vertex_3d.vertex.x = (float)cutX + 1.0f;
	m_Vertex_3d.vertex.z = (float)cutZ + 1.0f;
	m_Vertex_3d.index = (int)( (m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z) + (m_Vertex_3d.vertex.z - (m_Vertex_3d.vertex.z * 2 / 3) )) * 2;
	m_nTex = TexNo;

	//����̉ۑ�̎R������ׂ̕ϐ�
	float	mountion[17 * 17] = {
			21.0f,20.5f,15.0f,7.0f ,5.0f ,0.0f ,1.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,4.0f ,3.0f ,
			20.5f,20.5f,15.0f,7.0f ,5.0f ,0.0f ,1.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,4.0f ,4.0f ,
			15.0f,15.0f,13.0f,7.0f ,5.0f ,0.0f ,1.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,2.0f ,2.0f ,
			10.0f,10.0f,11.0f,5.0f ,0.0f ,1.0f ,4.0f ,4.0f ,2.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,10.0f,
			5.0f ,5.0f ,5.0f ,5.0f ,0.0f ,1.0f ,4.0f ,3.0f ,2.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,11.0f,13.0f,
			0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,4.0f ,4.0f ,3.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,11.0f,13.0f,
			1.0f ,1.0f ,1.0f ,1.0f ,4.0f ,4.0f ,3.0f ,4.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,-10.0f,11.0f,12.0f,
			3.0f ,4.0f ,4.0f ,4.0f ,4.0f ,3.0f ,4.0f ,6.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,
			1.0f ,2.0f ,3.0f ,3.0f ,3.0f ,0.0f ,6.0f ,8.0f ,6.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,
			1.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,6.0f ,1.0f ,0.0f ,0.0f ,0.0f ,10.0f,10.0f,10.0f,8.0f ,8.0f ,
			1.0f ,2.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,2.0f ,6.0f ,2.5f ,10.0f,10.0f,10.0f,6.0f ,6.0f ,
			1.0f ,2.0f ,3.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,6.0f ,8.0f ,2.5f ,3.0f ,10.0f,10.0f,3.0f ,3.0f ,
			1.0f ,2.0f ,5.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,3.0f ,6.0f ,0.7f ,3.0f ,10.0f,10.0f,1.0f ,1.0f ,
			1.0f ,2.0f ,5.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,3.0f ,1.0f ,3.0f ,10.0f,10.0f,0.0f ,0.0f ,
			1.0f ,2.0f ,1.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.0f ,0.0f ,3.0f ,14.0f,14.0f,0.0f ,0.0f ,
			0.0f ,0.0f ,0.0f ,3.0f ,3.0f ,3.0f ,2.0f ,1.0f ,0.0f ,0.0f ,0.0f ,0.0f ,3.0f ,3.0f ,3.0f ,0.0f ,0.0f ,
			0.0f ,0.0f ,0.0f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f ,0.0f ,0.0f ,0.0f ,0.0f ,1.5f ,0.0f ,0.0f ,0.0f ,0.0f ,};

			//�o�b�t�@�ݒ�
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * (UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z),
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

			m_Vertex_3d.DataVtx = new	D3DXVECTOR3[(int)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z)];

				//�A�����b�N�ϐ�
				VERTEX_3D	*pv;
				WORD	*pi;

					//���b�N����
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//�摜�̏������̗���
				int	zCount = 0;
				int	xCount = 0;

			//�e���_���W��������
			for(int	z = 0; z < (int)m_Vertex_3d.vertex.z ; z++)
			{
				for(int	x = 0 ; x < (int)m_Vertex_3d.vertex.x ; x++)
				{
					int	nCount_i = zCount * (int)m_Vertex_3d.vertex.x + xCount;
					pv[nCount_i].vtx.x = (m_Vertex_3d.Scail_vtx.x / (-2)) + (m_Vertex_3d.Scail_vtx.x / (m_Vertex_3d.vertex.x - 1.0f)) * (float)x;
					pv[nCount_i].vtx.y = mountion[nCount_i];
					pv[nCount_i].vtx.z = (m_Vertex_3d.Scail_vtx.z / 2) - (m_Vertex_3d.Scail_vtx.z / (m_Vertex_3d.vertex.z - 1.0f)) * (float)z;
					m_Vertex_3d.DataVtx[nCount_i] = pv[nCount_i].vtx;
					pv[nCount_i].tex.x = (float)xCount;
					pv[nCount_i].tex.y = (float)zCount;
					pv[nCount_i].diffuse = m_Vertex_3d.diffuse;
					xCount++;
				}
				zCount++;
				xCount = 0;
			}

			//�x�N�g���v�Z�p�ϐ�
			D3DXVECTOR3	vec0;
			D3DXVECTOR3	vec1;

			//�@���̖ʐ����m��
			m_pNormalBuff = new	D3DXVECTOR3[cutX * cutZ * 2];

			//�@���̐ݒ�
			for(int	z = 0; z < cutZ ; z++)
			{
				for(int	x = 0; x < cutX;x++)
				{
					int	nCount_i = z * cutX + x;

						//�����̖�
						vec0 = pv[x + (int)m_Vertex_3d.vertex.x * z].vtx - pv[x + (int)m_Vertex_3d.vertex.x * (z + 1)].vtx;
						vec1 = pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx - pv[x + (int)m_Vertex_3d.vertex.x * z].vtx;
						m_pNormalBuff[nCount_i * 2].x = vec0.y * vec1.z - vec0.z * vec1.y;
						m_pNormalBuff[nCount_i * 2].y = vec0.z * vec1.x - vec0.x * vec1.z;
						m_pNormalBuff[nCount_i * 2].z = vec0.x * vec1.y - vec0.y * vec1.x;

						//�E���̖�
						vec0 = pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx - pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx;
						vec1 = pv[x + (int)m_Vertex_3d.vertex.x * z].vtx - pv[x + (int)m_Vertex_3d.vertex.x * (z + 1) + 1].vtx;
						m_pNormalBuff[nCount_i * 2 + 1].x = vec0.y * vec1.z - vec0.z * vec1.y;
						m_pNormalBuff[nCount_i * 2 + 1].y = vec0.z * vec1.x - vec0.x * vec1.z;
						m_pNormalBuff[nCount_i * 2 + 1].z = vec0.x * vec1.y - vec0.y * vec1.x;

				}
			}


			int	Xcut = cutX;
			int	Zcut = cutZ;

			for(int	z = 0; z < m_Vertex_3d.vertex.z ; z++)
			{
				for(int	x = 0; x < m_Vertex_3d.vertex.x; x++)
				{
					int	nCount_i = z * (int)m_Vertex_3d.vertex.x + x;
					if(z == 0)
					{
						//�����̏ꍇ
						if(x == 0)
						{
							pv[nCount_i].hor = (m_pNormalBuff[0] + m_pNormalBuff[1]) / 2;
						}
						//�E���̏ꍇ
						else	if(x == cutX)
						{
							pv[nCount_i].hor = m_pNormalBuff[Xcut * 2 - 1];
						}
						//�ŉ����̏ꍇ
						else
						{
								pv[nCount_i].hor = (m_pNormalBuff[(x * 2) - 1] + 
													m_pNormalBuff[(x * 2)] + 
													m_pNormalBuff[(x * 2) + 1]) / 3;
						}
					}
					else	if(z == cutZ)
					{
						//����O�̏ꍇ
						if(x == 0)
						{
							pv[nCount_i].hor = m_pNormalBuff[Xcut * 2 * (z - 1)];
						}
						//�E��O�̏ꍇ
						else	if(x == (m_Vertex_3d.vertex.x - 1))
						{
							pv[nCount_i].hor = (m_pNormalBuff[Xcut * Zcut * 2 - 1] + 
												m_pNormalBuff[Xcut * Zcut * 2 - 2]) / 2;
						}
						//�Ŏ�O�̏ꍇ
						else
						{
							pv[nCount_i].hor = (m_pNormalBuff[((x * 2) - 2) + (Zcut * 2 * (z - 1))] +
												m_pNormalBuff[((x * 2) - 1) +(Zcut * 2 * (z - 1) )] + 
												m_pNormalBuff[(x * 2) + (Zcut * 2 * (z - 1))]) / 3;
						}
					}
					else
					{
						//���[�̏ꍇ
						if(x == 0)
						{
							pv[nCount_i].hor = (m_pNormalBuff[(Xcut * 2) * z] +
												m_pNormalBuff[(Xcut * 2) * z + 1] + 
												m_pNormalBuff[(Xcut * 2) * (z - 1)]) / 3;
						}
						//�E�[�̏ꍇ
						else	if(x == cutX)
						{
							pv[nCount_i].hor = (m_pNormalBuff[(Xcut * 2 * z) - 1] +
												m_pNormalBuff[(Xcut * 2 * z) - 2] + 
												m_pNormalBuff[(Xcut * 2 ) * (z + 1) - 1] ) / 3;
						}
						//��L�S�Ăɑ����Ȃ��ꍇ
						else
						{
							pv[nCount_i].hor = (m_pNormalBuff[(x * 2 - 2) + ((z -1) * Xcut * 2)] +
												m_pNormalBuff[(x * 2 - 1) + ((z -1) * Xcut * 2)] + 
												m_pNormalBuff[(x * 2) + ((z -1) * Xcut * 2)] + 
												m_pNormalBuff[(x * 2 - 1) + (z * Xcut * 2)] + 
												m_pNormalBuff[(x * 2) + (z * Xcut * 2)] + 
												m_pNormalBuff[(x * 2 + 1) + (z * Xcut * 2)]) / 6;
						}
					}
					//���K��
					D3DXVec3Normalize(&pv[nCount_i].hor,&pv[nCount_i].hor);
					nCount_i++;
				}
			}

					//���b�N
					m_pD3DVtxBuff->Unlock();

					//�C���f�b�N�X�o�b�t�@�̃A�����b�N
					m_pD3DIndexBuff->Lock(0,0,(void**)&pi,0);

									//�C���f�b�N�X�������ݗp�ϐ��錾
				int	n = 0;	//�m�����ϐ�
				int	a;		//�i���o�[�ݒ�ϐ�


				//�C���f�b�N�X�ݒ�
	for(int	gz = 0; gz < (int)m_Vertex_3d.vertex.z  - 1 ;gz++)
	{
		//�ŏ��̓X���[
		if(n != 0)
		{
			pi[n] = (a + 1) + (int)m_Vertex_3d.vertex.x ;
			n++;
		}
			for(int	gx = 0; gx < (int)m_Vertex_3d.vertex.x  ;gx++)
			{
					a = gz * (int)m_Vertex_3d.vertex.x  + gx;

				pi[n+0] = a + (int)m_Vertex_3d.vertex.x ;
				pi[n+1] = a;
				n += 2;
			}

		//�Ō�̓X���[
		if(gz != (int)m_Vertex_3d.vertex.z  - 1)
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
CField	*CField::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Rot,
						float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo)
{
	//�|�C���^�錾
	CField	*pField;

	//�N���X����
	pField = new	CField;

	//������
	pField->Init(pDevice, vtx, color,Rot,Xwidth,Zwidth,cutX,cutZ,TexNo);

	return	pField;
}

//***************************************************************
//	�I��
//***************************************************************
void	CField::Uninit()
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

	//���W���̉��
	if(m_Vertex_3d.DataVtx != NULL)
	{
		delete	m_Vertex_3d.DataVtx;
		m_Vertex_3d.DataVtx = NULL;
	}

}

//***************************************************************
//	�X�V
//***************************************************************
void	CField::Update()
{

}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CField::Draw(LPDIRECT3DDEVICE9 pDevice)
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
	D3DXMatrixRotationYawPitchRoll(&mRotate, D3DXToRadian(m_Vertex_3d.Rot_vtx.y), D3DXToRadian(m_Vertex_3d.Rot_vtx.x), D3DXToRadian(m_Vertex_3d.Rot_vtx.z));

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
											(UINT)(m_Vertex_3d.vertex.x * m_Vertex_3d.vertex.z),
											0,
											(int)((m_Vertex_3d.vertex.x) * (m_Vertex_3d.vertex.z) * 2) );


}
