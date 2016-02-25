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
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"fade.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
int	CFade::m_status = NONE;

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
CFade::CFade(int	nPriority):CScene(nPriority)
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CFade::~CFade()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CFade::Init(LPDIRECT3DDEVICE9 pDevice,int	TexNo)
{
	//������
	m_Vertex_2d.vtx = D3DXVECTOR3(-SCREEN_WIDTH,0.0f,0.0f);
	m_status = NONE;
	m_nTex = TexNo;

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
						pv[0].vtx = D3DXVECTOR3(-SCREEN_WIDTH, 0, 0.0f);
						pv[1].vtx = D3DXVECTOR3(0, 0,0.0f);
						pv[2].vtx = D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f);
						pv[3].vtx = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);

						//�o�[�X�̕␳�l
						pv[0].rhw = 
						pv[1].rhw = 
						pv[2].rhw = 
						pv[3].rhw = 1.0f;

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

	return	S_OK;
}

//***************************************************************
//	�t�F�[�h�̐؂�ւ��֐�
//
//***************************************************************
void	CFade::Start(CFade::STATUS status, int Time)
{
	m_status = status;

}
//***************************************************************
//	�I��
//***************************************************************
void	CFade::Uninit()
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
void	CFade::Update()
{
	switch(m_status)
	{
	case	FADEIN:
		m_Vertex_2d.vtx.x += 11.5f;

		if(m_Vertex_2d.vtx.x >SCREEN_WIDTH)
		{
			m_Vertex_2d.vtx.x = SCREEN_WIDTH;
			m_status = FADEIN_END;
		}

		break;
	case	FADEIN_END:

		break;
	case	FADEOUT:
		m_Vertex_2d.vtx.x += 110.5f;

		if(m_Vertex_2d.vtx.x >SCREEN_WIDTH * 2)
		{
			m_Vertex_2d.vtx.x = 0;
			m_status = FADEOUT_END;
		}

		break;
	case	FADEOUT_END:
		m_status = NONE;
		break;
	}

}
//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//***************************************************************
void	CFade::Draw(LPDIRECT3DDEVICE9 pDevice)
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
					pv[0].vtx = D3DXVECTOR3(-SCREEN_WIDTH + m_Vertex_2d.vtx.x, 0, 0.0f);
					pv[1].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x, 0,0.0f);
					pv[2].vtx = D3DXVECTOR3(-SCREEN_WIDTH + m_Vertex_2d.vtx.x, SCREEN_HEIGHT,0.0f);
						pv[3].vtx = D3DXVECTOR3(m_Vertex_2d.vtx.x,SCREEN_HEIGHT,0.0f);

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
