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
CSceneBillboard::CSceneBillboard(int	nPriority):CScene(nPriority)
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CSceneBillboard::~CSceneBillboard()
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
HRESULT	CSceneBillboard::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo)
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
					m_Vertex_3d.vtx = vtx;
					m_Vertex_3d.diffuse = color;
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	�|���S������
//�����F
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//D3DXCOLOR	color�F�z�F�J���\
//�߂�l
//CSceneBillboard	���N���X
//***************************************************************
CSceneBillboard	*CSceneBillboard::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo)
{
	//�|�C���^�錾
	CSceneBillboard	*pSceneBillboard;

	//�N���X����
	pSceneBillboard = new	CSceneBillboard;

	//������
	pSceneBillboard->Init(pDevice,vtx,color,TexNo);

	return	pSceneBillboard;
}

//***************************************************************
//	�I��
//***************************************************************
void	CSceneBillboard::Uninit()
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
void	CSceneBillboard::Update()
{

}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//***************************************************************
void	CSceneBillboard::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�J�����֌W�ϐ��錾
	D3DXMATRIX	mtxView;
	CCamera	*pCamera;

	//�J�������擾
	pCamera = CManager::GetCamera();

	mtxView = pCamera->GetViewMatrix();

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

	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		D3DXMatrixInverse(&matViewInv,NULL,&matViewInv);

		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&matViewInv);
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
