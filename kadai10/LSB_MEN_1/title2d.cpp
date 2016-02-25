//***************************************************************
//
//	title2d.cpp
//	name:Masatugu Kamada
//	create:2012/10/20
//	update�F2012/10/20
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
#include	"title2d.h"
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
CTitle2d::CTitle2d()
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CTitle2d::~CTitle2d()
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
HRESULT	CTitle2d::Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
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
CTitle2d	*CTitle2d::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo)
{
	//�|�C���^�錾
	CTitle2d	*pScene2d;

	//�N���X����
	pScene2d = new	CTitle2d;

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
void	CTitle2d::Uninit()
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
void	CTitle2d::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

		//�F�̕ω��p�ϐ��i���͂P��ނ̕ω��v�f�ׁ̈A�錾�Ɠ����Ɍv�Z�j
		float	r = (float)(rand()%10 + 1) / 10;
		float	g = (float)(rand()%10 + 1) / 10;
		float	b = (float)(rand()%10 + 1) / 10;
		float	a = (float)(rand()%10 + 1) / 10;

	//�`��̎�ނɂ���Ċe������
	switch(m_nType)
	{
		//���������Ȃ��^�C�v
		case	NONE:
		//�F�ʕω�
		m_Vertex_2d.diffuse = D3DXCOLOR(r,g,b,a);
		break;

		//���̈ړ��̃^�C�v
		case	 MOVE_TYPE:
		m_Vertex_2d.vtx.x -= 2.5f;

		if(m_Vertex_2d.vtx.x < -m_Vertex_2d.Scail.x)
		{
			m_Vertex_2d.vtx.x = SCREEN_WIDTH + m_Vertex_2d.Scail.x * 2;
		}
		break;

		//���͏����ɂ���Ĉړ�����^�C�v
		case	MOVE_KEY:
		//�F�ʕω�
		m_Vertex_2d.diffuse = D3DXCOLOR(r,g,1,1);

		//�ړ�
		if(pKeyBoard->GetkeyboardPress(DIK_LEFT))
		{
			m_Vertex_2d.vtx.x -= 5.05f;
		}
		if(pKeyBoard->GetkeyboardPress(DIK_UP))
		{
			m_Vertex_2d.vtx.y -= 5.05f;
		}
		if(pKeyBoard->GetkeyboardPress(DIK_DOWN))
		{
			m_Vertex_2d.vtx.y += 5.05f;
		}
		if(pKeyBoard->GetkeyboardPress(DIK_RIGHT))
		{
			m_Vertex_2d.vtx.x += 5.05f;
		}
		break;

		//���̓��͂ňړ�����^�C�v
		case	MOVE_TUTORIAL:
		if(pKeyBoard->GetkeyboardPress(DIK_T))
		{
			if(!bmove)
			{
				bmove = true;
			}
		}

		if(bmove)
		{
			if(m_Vertex_2d.vtx.x < 0)
			{
				m_Vertex_2d.vtx.x += 5.05f;
			}
			else
			{
				m_Vertex_2d.vtx.x = 0;
				bmove = false;
			}
		}
		break;
	}

}
//***************************************************************
//	�`��
//	�����F
//	LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//	�߂�l�F
//	�Ȃ�
//***************************************************************
void	CTitle2d::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

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

