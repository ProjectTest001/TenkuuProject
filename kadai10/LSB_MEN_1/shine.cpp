//*****************************************************
//
//	shine.cpp
//	name:MasatuguKamada
//	create:2012/11/08
//	update:2012/11/08
//
//*****************************************************

//*****************************************************
//	�C���N���[�h
//*****************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"scenebillboard.h"
#include	"shine.h"
#include	"camera.h"
#include	"manager.h"
#include	"texture.h"


//******************************************************
//	���C���֐�
//******************************************************

//******************************************************
//	�R���X�g���N�^
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//******************************************************
CShine::CShine()
{

}

//******************************************************
//	�f�X�g���N�^
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//******************************************************
CShine::~CShine()
{

}

//******************************************************
//	������
//	����
//	LPDIRECT3DDEVICE9	pDevice:�f�o�C�X�|�C���^
//	D3DXVECTOR3 pos:���W
//	D3DXCOLOR color:�z�F
//	int life:����
//	D3DXVECTOR3 Scail:�g�k
//	float Speed:�������x
//	int TexNo:�摜�ԍ�
//	�߂�l
//	HRESULT�F�I���R�[�h
//******************************************************
HRESULT	CShine::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3 pos, D3DXCOLOR color, int life, D3DXVECTOR3 Scail, float Speed, int TexNo)
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
						pv[0].diffuse = color;
						pv[1].diffuse = color;
						pv[2].diffuse = color;
						pv[3].diffuse = color;

						// �e�N�X�`���t�u
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0f�ō���w��
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0f�ŉE��w��
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0f�ō����w��
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0f�ŉE���w��

					//���b�N
					m_pD3DVtxBuff->Unlock();

					//���l������
					m_Vertex_3d.vtx = pos;						//���W
					m_Vertex_3d.vtx.y += 1.0f;
					m_Vertex_3d.diffuse = color;				//�z�F
					m_Vertex_3d.Scail_vtx = Scail;				//�g�k
					m_nLife = life;								//����
					m_fSpeed = Speed;							//�������x
					m_nTex = TexNo;								//�摜�ԍ�

	return	S_OK;
}

//******************************************************
//	������
//	����
//	LPDIRECT3DDEVICE9	pDevice:�f�o�C�X�|�C���^
//	D3DXVECTOR3 pos:���W
//	D3DXCOLOR color:�z�F
//	int life:����
//	D3DXVECTOR3 Scail:�g�k
//	float Speed:�������x
//	int TexNo:�摜�ԍ�
//	�߂�l
//	HRESULT�F�I���R�[�h
//******************************************************
CShine	*CShine::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3 pos, D3DXCOLOR color, int life, D3DXVECTOR3 Scail,
					   float Speed, int TexNo)
{
	CShine	*pShine;

	pShine = new	CShine;

	pShine->Init(pDevice,pos,color,life,Scail,Speed,TexNo);

	return	pShine;
}

//******************************************************
//	�I��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//******************************************************
void	CShine::UnInit()
{
	//�������
	//�o�b�t�@���
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

}

//******************************************************
//	�X�V
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//******************************************************
void	CShine::Update()
{
	//���C�t����
	m_nLife--;

	//�k��
	m_Vertex_3d.Scail_vtx.x -= m_fSpeed;
	m_Vertex_3d.Scail_vtx.y -= m_fSpeed;
	m_Vertex_3d.Scail_vtx.z -= m_fSpeed;

	//�������Ȃ邩�������؂ꂽ��I��
	if(m_Vertex_3d.Scail_vtx.x < 0.0f || m_Vertex_3d.Scail_vtx.y < 0.0f ||m_Vertex_3d.Scail_vtx.z < 0.0f || m_nLife < 0)
	{
		CScene::Release();
	}
}

//******************************************************
//	�`��
//	����
//	LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//	�߂�l
//	�Ȃ�
//******************************************************
void	CShine::Draw(LPDIRECT3DDEVICE9 pDevice)
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

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::KASAN);

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�傫���ݒ�
	D3DXMatrixScaling(&mScale,m_Vertex_3d.Scail_vtx.x, m_Vertex_3d.Scail_vtx.y, m_Vertex_3d.Scail_vtx.z);

	//����
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		D3DXMatrixInverse(&matViewInv,NULL,&matViewInv);

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





