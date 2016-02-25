//***************************************************************
//
//	inputkeyboard.cpp
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
#include	"inputkeyboard.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
BYTE	CInputKeyboard::m_akey[MAX_KEY] = {NULL};
BYTE	CInputKeyboard::m_akeyTrigger[MAX_KEY] = {NULL};
BYTE	CInputKeyboard::m_akeyRelease[MAX_KEY] = {NULL};
BYTE	CInputKeyboard::m_akeyRepeatTrigger[MAX_KEY] = {NULL};
int	CInputKeyboard::m_akeyRepeatCount[MAX_KEY] = {0};

//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CInputKeyboard::CInputKeyboard()
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CInputKeyboard::~CInputKeyboard()
{

}

//***************************************************************
//	������
//����
//HINSTANCE hInst:�C���X�^���X
//HWND hWnd�F�ݒ肵���E�B���h�E
//�߂�l
//HRESULT�F�I���R�[�h
//***************************************************************
HRESULT	CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	//�L�[�̐ݒ�ϐ��錾
	HRESULT	result = S_OK;


	//������
	CInput::Init(hInst,hWnd);

	//�L�[�̊�{���擾
	LPDIRECTINPUTDEVICE8	pKeyboard = CInput::GetKeyDevice();

	//�f�o�C�X�̍쐬
	result = pKeyboard->GetDeviceState(256,m_akey);

		//�L�[�o�b�t�@�̏�����
		ZeroMemory(m_akey, 256);

		pKeyboard->Acquire();

	return	result;
}

//***************************************************************
//	�I��
//***************************************************************
void	CInputKeyboard::Uninit(void)
{
	CInput::Uninit();

}

//***************************************************************
//	�X�V
//�߂�l
//HRESULT�F�I���R�[�h
//***************************************************************
HRESULT	CInputKeyboard::Update(void)
{
	HRESULT	result;						//�X�V�ݒ�ϐ�
	BYTE	lastKeyState[MAX_KEY];		//�O��̏�ԕۑ��p
	LPDIRECTINPUTDEVICE8	pKeyboard = CInput::GetKeyDevice();	//�L�[���擾

	// �O��̏�Ԃ�ۑ��A��r�p
	memcpy(lastKeyState,m_akey,MAX_KEY);

		// �ŐV�̏�Ԃ𓾂�
	result = pKeyboard->GetDeviceState(256,m_akey);
	if(SUCCEEDED(result))
	{
		for(int i = 0; i < MAX_KEY; i++)      // �L�[�̐������A�J��Ԃ�
		{
			m_akeyTrigger[i] = (lastKeyState[i] ^ m_akey[i]) // �ύX����
                            & m_akey[i];                      // ���@��ON�̂���
            m_akeyRelease[i] = (lastKeyState[i] ^ m_akey[i]) // �ύX����
                            & ~m_akey[i];                     // ���@��OFF�̂���

            // �������s�[�g����
            if(m_akey[i])         // ������Ă�����̂�
            {
				
                if(m_akeyRepeatCount[i] == 0)  // �J�E���^��0�Ȃ�
                {
                    m_akeyRepeatTrigger[i] = m_akey[i];  // ON����
                }
                else                        // �J�E���g�r��
                {
                    m_akeyRepeatTrigger[i] = 0;    // OFF����
                }
                
                m_akeyRepeatCount[i]++;
                if(m_akeyRepeatCount[i] > REPEAT_TIME) // ���frame�z������
                        m_akeyRepeatCount[i] = 0;      // �J�E���g0�ɂ��āA����ON
				
            }
            else                    // ������Ă��Ȃ�������OFF����
            {
                m_akeyRepeatTrigger[i] = 0;
                m_akeyRepeatCount[i] = 0;
            }
        }
    }
	//���擾�Ɏ��s�����ꍇ
		else
		{
			//�A�N�Z�X���擾
			pKeyboard->Acquire();
		}

	return	result;
}

//*****************************************************************************
//	�L�[�擾�֐�
//����
//int nkey:�����ꂽ�L�[�̃i���o�[
//�߂�l
//BOOL�F�����ꂽ���̔���
//*****************************************************************************
BOOL	CInputKeyboard::GetkeyboardPress(int nkey)
{
    return (m_akey[nkey] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������

}

//*****************************************************************************
//	�L�[�g���K�[�擾�֐�
//����
//int nkey:�����ꂽ�L�[�̃i���o�[
//�߂�l
//BOOL�F�����ꂽ���̔���
//*****************************************************************************
BOOL	CInputKeyboard::GetkeyboardTrigger(int nkey)
{
    return (m_akeyTrigger[nkey] & 0x80);

}
