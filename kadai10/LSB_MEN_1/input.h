//***************************************************************
//
//	input.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/22
//
//***************************************************************

#ifndef	INPUT_H_
#define	INPUT_H_

#define	MAX_KEY		(256)


//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class	CInput
{
public:
	CInput();													//�R���X�g���N�^
	virtual	~CInput();											//�f�X�g���N�^
	virtual	HRESULT	Init(HINSTANCE	hInst, HWND	hWnd);			//������
	virtual	void	Uninit(void);								//�I��
	virtual	HRESULT	Update(void) = 0;							//�X�V
		LPDIRECTINPUTDEVICE8	GetKeyDevice(void){return	m_pDIDevice;};

protected:

	static	LPDIRECTINPUT8	m_pDInput;							//���͕ϐ�
	LPDIRECTINPUTDEVICE8	m_pDIDevice;						//���̓f�o�C�X

private:
};


#endif