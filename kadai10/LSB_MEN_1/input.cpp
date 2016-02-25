//***************************************************************
//
//	input.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/30
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

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
LPDIRECTINPUT8	CInput::m_pDInput = NULL;

//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CInput::CInput()
{
	//�f�o�C�X������
	m_pDIDevice = NULL;
}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CInput::~CInput()
{

}


//***************************************************************
//	������
//����
//HINSTANCE hInst:�C���X�^���X
//HWND hWnd�F�ݒ肵�Ă���E�B���h�E
//�߂�l
//HRESULT�F�I���R�[�h
//***************************************************************
HRESULT	CInput::Init(HINSTANCE hInst, HWND hWnd)
{
	//���͐ݒ�̐����ϐ�
	HRESULT	hr = S_OK;

	if(m_pDInput == NULL)
	{
		//Direct�@Input�C���^�[�t�F�[�X����
			hr = DirectInput8Create(
									hInst,					//�\�t�g�̃C���X�^���X�n���h��
									DIRECTINPUT_VERSION,			//DirectInput�̃o�[�W����
									IID_IDirectInput8,				//�擾����C���^�[�t�F�C�X�̃^�C�v
									(LPVOID*)&m_pDInput,			//�C���^�[�t�F�C�X�̊i�[��
									NULL							//COM�W���̐���I�u�W�F�N�g
									);

			if(FAILED(hr))
			{
				return	E_FAIL;
			}

				hr =m_pDInput->CreateDevice(
											GUID_SysKeyboard,			//�󂯕t������̓f�o�C�X
											&m_pDIDevice,				//IDirectInputDevice8�i�[��
											NULL						//COM�W���̐���I�u�W�F�N�g
										);
			if(FAILED(hr))
			{
				return	E_FAIL;
			}

			//�f�[�^�t�H�[�}�b�g�̐ݒ�
			hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);

			//�������[�h�̐ݒ�
				hr = m_pDIDevice->SetCooperativeLevel(hWnd,
												DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

				//���͂̎�t�J�n
				m_pDIDevice->Acquire();

	}

	return	hr;
}

//***************************************************************
//	�I��
//***************************************************************
void	CInput::Uninit(void)
{
	//�������
	if(m_pDIDevice != NULL)
	{
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if(m_pDInput != NULL)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}

}

