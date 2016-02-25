//***************************************************************
//
//	scenebillboard.cpp
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
#include	"explosion.h"
#include	"texture.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************
int	span = 5;
//***************************************************************
//	�R���X�g���N�^
//	����
//	����
//	�߂�l
//	�Ȃ�
//***************************************************************
CExplosion::CExplosion(int	nPriority):CSceneBillboard(nPriority)
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CExplosion::~CExplosion()
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
HRESULT	CExplosion::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,int	TexNo)
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
						pv[0].vtx = D3DXVECTOR3(-1.5f, 1.5f, 0.0f);
						pv[1].vtx = D3DXVECTOR3(1.5f, 1.5f,0.0f);
						pv[2].vtx = D3DXVECTOR3(-1.5f, -1.5f, 0.0f);
						pv[3].vtx = D3DXVECTOR3(1.5f,-1.5f , 0.0f);

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
						pv[1].tex = D3DXVECTOR2(0.1f,0.0f);		//1.0f,0.0f�ŉE��w��
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0f�ō����w��
						pv[3].tex = D3DXVECTOR2(0.1f,1.0f);		//1.0f,1.0f�ŉE���w��

					//���b�N
					m_pD3DVtxBuff->Unlock();

					//���l������
					m_Vertex_3d.vtx = vtx;
					m_Time = 0.0f;

					//���̑�������
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	�|���S������
//�����F
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//�߂�l
//CExplosion	���N���X
//***************************************************************
CExplosion	*CExplosion::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo)
{
	//�|�C���^�錾
	CExplosion	*pExplosion;

	//�N���X����
	pExplosion = new	CExplosion;

	//������
	pExplosion->Init(pDevice,vtx,TexNo);

	return	pExplosion;
}

//***************************************************************
//	�I��
//***************************************************************
void	CExplosion::Uninit()
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
void	CExplosion::Update()
{
	if(span < 0 )
	{
		if(m_Time > 0.9f)
		{
			CExplosion::Uninit();
			CScene::Release();
		}
		else
		{
			m_Time += 0.1f;
		}
		span = 1;
	}
	else
	{
		span--;
	}
}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CExplosion::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans;		//���W

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�J�����֌W�ϐ��錾
	D3DXMATRIX	mtxView;
	CCamera	*pCamera;

	//�J�������擾
	pCamera = CManager::GetCamera();
	mtxView = pCamera->GetViewMatrix();

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//�A�����b�N�ϐ�
	VERTEX_3D	*pv;

	//���b�N����
	m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

		// �e�N�X�`���t�u
		pv[0].tex = D3DXVECTOR2(m_Time,0.0f);				
		pv[1].tex = D3DXVECTOR2(m_Time + 0.1f,0.0f);		
		pv[2].tex = D3DXVECTOR2(m_Time,1.0f);			
		pv[3].tex = D3DXVECTOR2(m_Time + 0.1f,1.0f);	

	m_pD3DVtxBuff->Unlock();

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���{�[�h�ݒ�
	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		//�C���o�[�X
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
