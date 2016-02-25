//***************************************************************
//
//	scene2d.cpp
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
#include	<dinput.h>
#include	"input.h"
#include	"inputkeyboard.h"
#include	"renderer.h"
#include	"manager.h"
#include	"scene.h"
#include	"scene2d.h"
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
CScene2d::CScene2d(int	nPriority):CScene(nPriority)
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CScene2d::~CScene2d()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx:�`��ʒu
//D3DXVECTOR2	Scail:�傫��
//const	char*Name:�t�@�C����
//int	Type:�`��̎��
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CScene2d::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
{
	//������
	m_Vertex_2d.vtx = vtx;									//���W
	m_Vertex_2d.Scail = Scail;								//�傫��
	m_nType = Type;											//�`��̎��
	m_Vertex_2d.diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);	//�F
	bmove = false;											//�ړ��t���O
	//m_Vertex_2d.rhw = 1.0f;

			//�o�b�t�@�ݒ�
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_2D)) * 4,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}

				//�A�����b�N�ϐ�
				VERTEX_2D	*pv;

					//���b�N����
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//�摜�̏������̗���
						//���Wx,y,z
					pv[0].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y, 0.0f);
					pv[1].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x, m_Vertex_2d.vtx.y,0.0f);
						pv[2].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);
						pv[3].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x,m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);

						//�o�[�X�̕␳�l
						pv[0].rhw = 
						pv[1].rhw = 
						pv[2].rhw = 
						pv[3].rhw = 1.0f;

						//���_�F(�ԁA�΁A�j
						pv[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
						pv[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
						pv[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
						pv[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);

						// �e�N�X�`���t�u
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0f�ō���w��
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0f�ŉE��w��
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0f�ō����w��
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0f�ŉE���w��

					//���b�N
					m_pD3DVtxBuff->Unlock();

					//���̑�������
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	�|���S������
//����
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx:�`��ʒu
//D3DXVECTOR2	Scail:�傫��
//const	char*Name:�t�@�C����
//int	Type:�`��̎��
//�߂�l
//CScene2d�F���N���X
//***************************************************************
CScene2d	*CScene2d::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
{
	//�|�C���^�錾
	CScene2d	*pScene2d;

	//�N���X����
	pScene2d = new	CScene2d;

	//������
	pScene2d->Init(pDevice,vtx,Scail,Type,TexNo);

	return	pScene2d;

}

//***************************************************************
//	�I��
//	�����F
//	�Ȃ�
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CScene2d::Uninit()
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
//	�����F
//	�Ȃ�
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CScene2d::Update()
{

}
//***************************************************************
//	�`��
//	�����F
//	LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CScene2d::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//�A�����b�N�ϐ�
	VERTEX_2D	*pv;

		//���b�N����
		m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//�摜�̏������̗���
						//���Wx,y,z
					pv[0].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y, 0.0f);
					pv[1].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x, m_Vertex_2d.vtx.y,0.0f);
					pv[2].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);
					pv[3].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x + m_Vertex_2d.Scail.x,m_Vertex_2d.vtx.y + m_Vertex_2d.Scail.y,0.0f);

						//���_�F(�ԁA�΁A�j
					pv[0].diffuse = m_Vertex_2d.diffuse;
					pv[1].diffuse = m_Vertex_2d.diffuse;
					pv[2].diffuse = m_Vertex_2d.diffuse;
					pv[3].diffuse = m_Vertex_2d.diffuse;

	//���b�N
	m_pD3DVtxBuff->Unlock();

		//�t�H�[�}�b�g�̎w��
		pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0,
				Texture);

			//���_�o�b�t�@�̑��M
			pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_2D));

			//�摜�\��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);



}
