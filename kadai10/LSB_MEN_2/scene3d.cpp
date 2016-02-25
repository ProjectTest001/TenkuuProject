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
#include	"renderer.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"field.h"
#include	"camera.h"
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
CScene3d::CScene3d()
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CScene3d::~CScene3d()
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
HRESULT	CScene3d::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo)
{

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
CScene3d	*CScene3d::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo)
{
	//�|�C���^�錾
	CScene3d	*pScene3d;

	//�N���X����
	pScene3d = new	CScene3d;

	//������
	pScene3d->Init(pDevice, vtx, color,TexNo);

	return	pScene3d;
}

//***************************************************************
//	�I��
//***************************************************************
void	CScene3d::Uninit()
{

	//�������
	//�o�b�t�@���
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

}

//***************************************************************
//	�X�V
//***************************************************************
void	CScene3d::Update()
{

}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CScene3d::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�傫���ݒ�
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

	//����
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

	//�p�x�ݒ�
	D3DXMatrixRotationYawPitchRoll(&mRotate, 0.0f, D3DXToRadian(0.0f), 0.0f);

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

		//�t�H�[�}�b�g�̎w��
		pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0,
				Texture);

			//�摜�\��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}


//***************************************************************
//	�n�ʂ̍����̎擾
//	����
//	D3DXVECTOR3	pos:�Ώۂ̈ʒu
//	�߂�l
//	float�F���鍂��
//***************************************************************
float	CScene3d::GetHeight(D3DXVECTOR3 pos)
{
	int	camera = CCamera::GetCameraMode();

	if(camera != CCamera::PLAYER_CAMERA)
	{
		return	0;
	}
	//�n�ʏ��擾
	VERTEX_3D	pField = CField::GetVertex();
	
	//�v�Z���ʂ�[�߂�ϐ�
	float	fHeight = pos.y;

	for(int	z = 0 ; z <  pField.vertex.z - 1.0f ; z++)
	{
		for(int	x = 0 ; x <  pField.vertex.x - 1.0f; x++)
		{
			int	nCount_i = z * (int)pField.vertex.x + x;

			//�x�N�g���ϐ��錾
			const	D3DXVECTOR3	aVtx[4] = 
			{
				pField.DataVtx[x + (int)pField.vertex.x * (z + 1)],			//����
				pField.DataVtx[x + (int)pField.vertex.x * z],				//����
				pField.DataVtx[x + (int)pField.vertex.x * (z + 1) + 1],		//�E��
				pField.DataVtx[x + (int)pField.vertex.x * z + 1],			//�E��
			};

			D3DXVECTOR3	vec0;
			D3DXVECTOR3	vec1;
			int	Count = 0;

			for(int	nCnt = 0; nCnt < 3 ; nCnt++)
			{
					//�x�N�g���ϐ�
					vec0 = aVtx[(int)(nCnt + 1) % 3 + 1] - aVtx[nCnt + 1];
					vec1 = pos - aVtx[nCnt + 1];

					//�E���̖�
				if((vec0.z * vec1.x - vec0.x * vec1.z) <= 0 )
				{
					Count++;
					if(Count > 2)
					{
						fHeight = GetHeightPolygon(pos,aVtx[1],aVtx[3],aVtx[2]);
						return	fHeight;
					}
				}
			}

			Count = 0;

			for(int	nCnt = 0; nCnt < 3 ; nCnt++)
			{
					//�x�N�g���ϐ�
					vec0 = aVtx[nCnt] - aVtx[(int)(nCnt + 1) % 3];
					vec1 = pos - aVtx[(int)(nCnt + 1) % 3];

					//�����̖�
				if((vec0.z * vec1.x - vec0.x * vec1.z) <= 0 )
				{
					Count++;
					if(Count > 2)
					{
						fHeight = GetHeightPolygon(pos,aVtx[0],aVtx[1],aVtx[2]);
						return	fHeight;
					}
				}
			}

		}
	}
	//���όv�Z
//pos.y = m_Vertex_3d.vtx.y - pos.x + m_Vertex_3d.vtx.x - pos.z + m_Vertex_3d.vtx.z;
	return	fHeight;
}

//*
//
//*
float	CScene3d::GetHeightPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2)
{
	float	fHeight = 0.0f;
	D3DXVECTOR3	vec0;
	D3DXVECTOR3	vec1;
	D3DXVECTOR3	nor;

	vec0 = vtx0 - vtx1;
	vec1 = vtx0 - vtx2;

	nor.x = vec0.y * vec1.z - vec0.z * vec1.y;
	nor.y = vec0.z * vec1.x - vec0.x * vec1.z;
	nor.z = vec0.x * vec1.y - vec0.y * vec1.x;

	fHeight = vtx0.y - (( nor.x * pos.x - nor.x * vtx0.x + nor.z * pos.z - nor.z * vtx0.z  ) / nor.y);
	return	fHeight;
}