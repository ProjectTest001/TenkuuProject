//***************************************************************
//
//	number.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/07/03
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
#include	"number.h"
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
CNumber::CNumber(int	nPriority)
{
	//������
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CNumber::~CNumber()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CNumber::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo)
{
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
						pv[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, 0.0f);
						pv[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y,0.0f);
						pv[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + heght,0.0f);
						pv[3].vtx = D3DXVECTOR3(vtx.x + width,vtx.y + heght,0.0f);

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
						pv[1].tex = D3DXVECTOR2(0.0625f,0.0f);		//1.0f,0.0f�ŉE��w��
						pv[2].tex = D3DXVECTOR2(0.0f,0.125f);		//0.0f,1.0f�ō����w��
						pv[3].tex = D3DXVECTOR2(0.0625f,0.125f);		//1.0f,1.0f�ŉE���w��

					//���b�N
					m_pD3DVtxBuff->Unlock();

					//���̑�������
					m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	�|���S������
//����
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//�߂�l
//CScene2d�F���N���X
//***************************************************************
CNumber	*CNumber::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo)
{
	//�|�C���^�錾
	CNumber	*pNumber;

	//�N���X����
	pNumber = new	CNumber;

	//������
	pNumber->Init(pDevice,vtx,width,heght,TexNo);

	return	pNumber;

}

//***************************************************************
//	�I��
//***************************************************************
void	CNumber::Uninit()
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
void	CNumber::Update()
{

}

//***************************************************************
//	�����̃Z�b�g
//***************************************************************
void	CNumber::SetNumber(int	nNumber)
{
	float	fNumber = (float)nNumber * 0.0625f;

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//�A�����b�N�ϐ�
	VERTEX_2D	*pv;

		//���b�N����
		m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

			// �e�N�X�`���t�u
			pv[0].tex = D3DXVECTOR2(fNumber,0.0f);		//0.0f,0.0f�ō���w��
			pv[1].tex = D3DXVECTOR2(fNumber + 0.0625f,0.0f);		//1.0f,0.0f�ŉE��w��
			pv[2].tex = D3DXVECTOR2(fNumber,0.125f);		//0.0f,1.0f�ō����w��
			pv[3].tex = D3DXVECTOR2(fNumber + 0.0625f,0.125f);		//1.0f,1.0f�ŉE���w��

	//���b�N
	m_pD3DVtxBuff->Unlock();

}

//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//***************************************************************
void	CNumber::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

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
