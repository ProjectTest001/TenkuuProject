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
#include	"scenebillboard.h"
#include	"camera.h"
#include	"manager.h"
#include	"bullet.h"
#include	"field.h"
#include	"explosion.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
VERTEX_3D	CBullet::m_Vertex_3d;

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//	�߂�l
//	�Ȃ�
//***************************************************************
CBullet::CBullet()
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CBullet::~CBullet()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�Ăяo�����Ώۂ̍��W
//D3DXVECTOR3	Rot:�Ăяo�����Ώۂ̌����Ă�p�x
//int	TexNo:�e�N�X�`���ԍ�
//�߂�l
//HRESULT:�I���R�[�h
//***************************************************************
HRESULT	CBullet::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo)
{
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

				//�A�����b�N�ϐ�
				VERTEX_3D	*pv;

					//���b�N����
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//�摜�̏������̗���
						//���Wx,y,z
						pv[0].vtx = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
						pv[1].vtx = D3DXVECTOR3(0.5f, 0.5f,0.0f);
						pv[2].vtx = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
						pv[3].vtx = D3DXVECTOR3(0.5f,-0.5f , 0.0f);

						//�@��
						pv[0].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[1].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[2].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[3].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);


						//���_�F(�ԁA�΁A�j
						pv[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

						// �e�N�X�`���t�u
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0f�ō���w��
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0f�ŉE��w��
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0f�ō����w��
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0f�ŉE���w��

					//���b�N
					m_pD3DVtxBuff->Unlock();

					//���l������
					m_Vertex_3d.vtx = vtx;										//���W
					m_Vertex_3d.Rot_vtx = Rot;										//�p�x
					m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);			//���x
					m_nTex = TexNo;												//�摜�ԍ�

	return	S_OK;
}

//***************************************************************
//	�|���S������
//�����F
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�Ăяo�����Ώۂ̍��W
//D3DXVECTOR3	Rot:�Ăяo�����Ώۂ̌����Ă�p�x
//int	TexNo:�e�N�X�`���ԍ�
//�߂�l
//CBullet	���N���X
//***************************************************************
CBullet	*CBullet::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo)
{
	//�|�C���^�錾
	CBullet	*pBullet;

	//�N���X����
	pBullet = new	CBullet;

	//������
	pBullet->Init(pDevice,vtx,Rot,TexNo);

	return	pBullet;
}

//***************************************************************
//	�I��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CBullet::Uninit()
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
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CBullet::Update()
{

	//�n�ʏ��擾
	VERTEX_3D	pField = CField::GetVertex();
	
	//�x�N�g���ϐ��錾
	const	D3DXVECTOR3	aVtx[4] = 
	{
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2) ),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//����
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//�E��
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//�E��
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2)),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//����
	};
	
	//�p�x������������̏C���ϐ�
	D3DXVECTOR3	aVtxNew[4];
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
		aVtxNew[nCount].x = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x + cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z;
		aVtxNew[nCount].z = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z - cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x;
	}

	//���x
	m_Vertex_3d.Speed_vtx.x -= sin(D3DX_PI * m_Vertex_3d.Rot_vtx.x) * 0.08f;
	m_Vertex_3d.Speed_vtx.z -= cos(D3DX_PI * m_Vertex_3d.Rot_vtx.x) * 0.08f;

	//��R���C
	m_Vertex_3d.Speed_vtx.x -= m_Vertex_3d.Speed_vtx.x * 0.3f;
	//m_Vertex_3d.Speed_vtx.y -= m_Vertex_3d.Speed_vtx.y * 0.3f;		//�x���W�̌v�Z�͍��͎g��Ȃ�
	m_Vertex_3d.Speed_vtx.z -= m_Vertex_3d.Speed_vtx.z * 0.3f;

		//�ړ�
		m_Vertex_3d.vtx.x += m_Vertex_3d.Speed_vtx.x;
		m_Vertex_3d.vtx.z += m_Vertex_3d.Speed_vtx.z;

	//�����蔻�葪��
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
				//�e�ƕǂ̃x�N�g���֌W�̌v�Z
				D3DXVECTOR3	nVtx = aVtxNew[(int)(nCount + 1) % 4] - aVtxNew[nCount];
				D3DXVECTOR3	BulletVtx = m_Vertex_3d.vtx - aVtxNew[nCount];

			//�O�όv�Z�ŕ��̐����ɂȂ����ꍇ�A�����������ɂ���
			if( (nVtx.z * BulletVtx.x- nVtx.x * BulletVtx.z) < 0 )
			{
				//�����G�t�F�N�g������A����
				CExplosion::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,EXPLOSION_TEXTURE);
				//CBullet::Uninit();
				CScene::Release();
				break;
			}
	}
}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//�߂�l
//�Ȃ�
//***************************************************************
void	CBullet::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�J�����֌W�ϐ��錾
	D3DXMATRIX	mtxView;
	CCamera	*pCamera;

	//�J�������擾
	pCamera = CManager::GetCamera();		//�J�����|�C���^
	mtxView = pCamera->GetViewMatrix();		//�r���[�}�g���b�N�X

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���{�[�h����
	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		D3DXMatrixInverse(&matViewInv,NULL,&matViewInv);

		//����
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&matViewInv);

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
