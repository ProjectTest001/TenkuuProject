//***************************************************************
//
//	inputkeyborad.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/22
//
//***************************************************************

#ifndef	INPUTKEYBOARD_H_
#define	INPUTKEYBOARD_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define REPEAT_TIME (6)                 // �������s�[�g�Ԋu(frame)

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class	CInputKeyboard:public	CInput
{
public:
	CInputKeyboard();										//�R���X�g���N�^
	~CInputKeyboard();										//�f�X�g���N�^
	HRESULT	Init(HINSTANCE	hInst,HWND	hwnd);				//������
	void	Uninit(void);									//�I��
	HRESULT	Update(void);									//�X�V

	//�L�[�{�[�h�̏����擾����֐�
	static	BOOL	GetkeyboardPress(int	nkey);	//�L�[�擾
	static	BOOL	GetkeyboardTrigger(int	nkey);	//�L�[�g���K�[�̎擾


private:
	//�L�[�{�[�h�̏��
	static	BYTE	m_akey[MAX_KEY];
	static	BYTE	m_akeyTrigger[MAX_KEY];
	static	BYTE	m_akeyRelease[MAX_KEY];
	static	BYTE	m_akeyRepeatTrigger[MAX_KEY];    // �������ς̂Ƃ��A���Ԋu��ON(�����A��)
	static	int	m_akeyRepeatCount[MAX_KEY]; // �L�[���s�[�g�p�J�E���g

};

#endif