//***************************************************************
//
//	renderer.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/19
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
#include	"camera.h"
#include	"number.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************
LPDIRECT3DDEVICE9	CRenderer::m_D3DDevice = NULL;
int	CRenderer::m_nType = NOMAL;
//***************************************************************
//	�C���X�g���N�^
//***************************************************************
CRenderer::CRenderer()
{
	//������
	m_pD3D = NULL;
	m_D3DDevice = NULL;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CRenderer::~CRenderer()
{

}

//***************************************************************
//	������
//***************************************************************
HRESULT	CRenderer::Init(HWND hWindow, BOOL bwindow)
{
	//������
	m_pD3D = Direct3DCreate9(
				D3D_SDK_VERSION);
	//�ǂݍ��݂Ɏ��s�����ꍇ
	if(m_pD3D == NULL)
	{
		return	E_FAIL;
	}
	//�\���ݒ�
	D3DDISPLAYMODE	dm;
	D3DPRESENT_PARAMETERS	pp;

	//displaymode �m�F
	if(FAILED( m_pD3D->GetAdapterDisplayMode(
						D3DADAPTER_DEFAULT,&dm) ))
	{
		return	E_FAIL;
	}
	//�e��\���ݒ�
	ZeroMemory(&pp,sizeof(pp));
	// 0 clear
	pp.BackBufferCount = 1;		//����ʂ̐ݒ�
	pp.BackBufferWidth = SCREEN_WIDTH;		//���ݒ�
	pp.BackBufferHeight = SCREEN_HEIGHT;		//�����ݒ�

	//��ʐ؂�ւ����̎w��
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = bwindow;		//window mode

	// �[�x�o�b�t�@
	pp.EnableAutoDepthStencil = true;
	// 16bit �g��
	pp.AutoDepthStencilFormat = D3DFMT_D16;

	//�S��ʃ��[�h�i�n�e�e�̏ꍇ�j
	if(bwindow)
	{
		pp.BackBufferFormat = D3DFMT_UNKNOWN;
		// �S��ʂ̂Ƃ��̐؂�ւ��^�C�~���O
		pp.FullScreen_RefreshRateInHz = 0;
		pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	}
	//�S��ʃ��[�h�i�n�m�̏ꍇ�j
	else
	{
		pp.BackBufferFormat = D3DFMT_R5G6B5;
		// �S��ʂ̂Ƃ��̐؂�ւ��^�C�~���O
		pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	}

	//�\�����u�쐬
	if(FAILED( m_pD3D->CreateDevice(
						D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,			//hardware
						hWindow,				//�����N����window
						D3DCREATE_HARDWARE_VERTEXPROCESSING,	//���_����hardware
						&pp,					//�\���ݒ�
						&m_D3DDevice) ))				//�\�����u�i�������j
	{
		if(FAILED( m_pD3D->CreateDevice(
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,			//hardware
							hWindow,				//�����N����window
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//���_����software
							&pp,					//�\���ݒ�
							&m_D3DDevice) ))				//�\�����u�i�������j
		{
			if(FAILED( m_pD3D->CreateDevice(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_REF,			//hardware
								hWindow,				//�����N����window
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//���_����software
								&pp,					//�\���ݒ�
								&m_D3DDevice) ))				//�\�����u�i�������j
			{
				MessageBox(NULL,"�f�o�C�X�G���[",
						"�G���[",MB_OK);
				return	E_FAIL;
			}
		}
	}

	//�`��ݒ�
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

	//�J�����O�i�A�ʏ����j���Ȃ�
	m_D3DDevice->SetRenderState(D3DRS_ZENABLE,true);

	// Z buffer(�[�x�o�b�t�@�j�L��
	//�������̎w��
	m_D3DDevice->SetRenderState(
					D3DRS_CULLMODE,D3DCULL_CCW);
	m_D3DDevice->SetRenderState(
					D3DRS_ZENABLE,
						D3DCULL_NONE);
	m_D3DDevice->SetRenderState(
					D3DRS_ALPHABLENDENABLE,true);
	m_D3DDevice->SetRenderState(
					D3DRS_SRCBLEND,
						D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(
					D3DRS_DESTBLEND,
						D3DBLEND_INVSRCALPHA);

	//�@�T���v���[�ݒ�
	// �@�e�N�X�`���J�Ԃ��w��
	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_ADDRESSU,
			D3DTADDRESS_WRAP);			//�����̌J�Ԃ��w��

	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_ADDRESSV,
			D3DTADDRESS_WRAP);			//�c���̌J�Ԃ��w��

	//�g��k�����̎w��
	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER,
			D3DTEXF_POINT);				//�k�����̎w��

	m_D3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER,
			D3DTEXF_POINT);				//�g�厞�̎w��

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_COLOROP,
						D3DTOP_MODULATE);

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_COLORARG1,
						D3DTA_TEXTURE);

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_COLORARG2,
						D3DTA_CURRENT);
						
	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_ALPHAOP,
						D3DTOP_SELECTARG1);			//�`�q�f�P�Ƃ`�q�f�Q�̃��l����Z���ă��̒l���擾

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_ALPHAARG1,
						D3DTA_TEXTURE);				//�e�N�X�`���̃��l

	m_D3DDevice->SetTextureStageState(0,
						D3DTSS_ALPHAARG2,
						D3DTA_CURRENT);				//���_�̃��l
/*
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_D3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
*/
	//m_D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	return	S_OK;
}

//***************************************************************
//	�I��
//***************************************************************
void	CRenderer::Uninit()
{
	//�������
	if(m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	//�f�o�C�X���
	if(m_D3DDevice != NULL)
	{
		m_D3DDevice->Release();
		m_D3DDevice = NULL;
	}
}

//***************************************************************
//	�X�V
//***************************************************************
void	CRenderer::Update()
{
	//�S�X�V
	CScene::UpdateAll();
}

//***************************************************************
//	�`��
//***************************************************************
void	CRenderer::Draw()
{

			//��ʃN���A
	m_D3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET |
					D3DCLEAR_ZBUFFER),
					//�t���[���o�b�t�@�Ɛ[�x�o�b�t�@�N���A
					D3DCOLOR_RGBA(0,0,0,0),
					//�N���A�F
					1.0f,
					//�N���A	�y�l
					0);	//�X�e���V���l
	if(SUCCEEDED( m_D3DDevice->BeginScene() ))
	{

		//�J�����Z�b�g
		CCamera::SetCamera(m_D3DDevice);

		//�S�`��
		CScene::DrawAll(m_D3DDevice);

		//�`��I��
		m_D3DDevice->EndScene();
		
	}

	//����ʂƕ\��ʂ�؂�ւ�
	m_D3DDevice->Present(NULL,NULL,NULL,NULL);
}

//***************************************************************
//	�f�o�C�X��n���֐�
//	����
//	����
//	�߂�l:
//	LPDIRECT3DDEVICE9	�擾����f�o�C�X
//***************************************************************
LPDIRECT3DDEVICE9	CRenderer::GetDevice()
{
	return	m_D3DDevice;
}

//***************************************************************
//	�`��^�C�v�̕ύX�֐�
//	����
//	CRenderer::RENDER_TYPE type�F�`��^�C�v
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CRenderer::SetRenderType(CRenderer::RENDER_TYPE type)
{
	//�`��^�C�v���ύX�����Ɠ����ꍇ�͈ȉ��̏������s��Ȃ�
	if(m_nType == type)
	{
		return;
	}

	m_nType = type;

	switch(m_nType)
	{
	case	NOMAL:
	m_D3DDevice->SetRenderState(
					D3DRS_SRCBLEND,
						D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(
					D3DRS_DESTBLEND,
						D3DBLEND_INVSRCALPHA);

	break;
	case	KASAN:
		m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		m_D3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		m_D3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
		break;

	}
}