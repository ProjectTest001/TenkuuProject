//***************************************************************
//
//	manager.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/19
//
//***************************************************************

#ifndef	MANAGER_H_
#define	MANAGER_H_

//***************************************************************
//	�}�N����`
//***************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
//�O���Q��
class	CInputKeyboard;
class	CCamera;
class	CLight;
class	CScene3d;
class	CScore;
class	CTime;
class	CTitle;
class	CGame;
class	CRezult;
class	CFade;
class	CDebugProc;
class	CTexture;
class	CXfile;

class	CManager
{
public:
	CManager();																//�R���X�g���N�^
	~CManager();															//�f�X�g���N�^

	typedef	enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_REZULT_CLEAR,
		MODE_REZULT_GAMEOVER,
		MODE_MAX,
	}MODE;

	HRESULT	Init(HINSTANCE	hInstance, HWND	hWnd, BOOL	bWindow);		//������
	void	Uninit(void);													//�I��
	void	Update(void);													//�X�V
	void	Draw(void);														//�`��

	static	CRenderer	*GetRenderer(void){return	m_pRenderer;};									//�����_�\�擾
	static	CInputKeyboard	*GetInputKeyboard(void){return	m_pInputkeyboard;};						//�L�[���͂̎擾�֐�
	static	CCamera	*GetCamera(void){return	m_pCamera;};											//�J�������擾
	static	CScene3d	*GetScene3D(void){return	m_pScene3d;};
	static	void	SetMode(MODE	mode);															//�X�e�[�g�؂�ւ�
	static	void	ChangeMode(MODE	mode);															//�X�e�[�g�؂�ւ�

private:
	static	CRenderer	*m_pRenderer;										//�����_�\�ϐ�
	static	CTexture	*m_pTexture;										//�e�N�X�`���ϐ�
	static	CInputKeyboard	*m_pInputkeyboard;								//�L�[�{�[�h�ϐ�
	static	CCamera	*m_pCamera;												//�J�����ϐ�
	static	CLight	*m_pLight;												//���C�g�ϐ�
	static	CScene3d	*m_pScene3d;										//�R�c�ϐ�
	static	CScore	*m_pScore;												//�X�R�A�ϐ�
	static	CTime	*m_pTime;												//���ԕϐ�
	static	int	m_mode;													//�Q�[�����[�h�ϐ�
	static	int	m_amode;
	static	CTitle	*m_pTitle;												//�^�C�g���ϐ�
	static	CGame	*m_pGame;												//�Q�[���ϐ�
	static	CRezult	*m_pRezult;												//���U���g�ϐ�
	static	CFade	*m_pFade;												//�t�F�[�h�ϐ�
	static	CDebugProc	*m_pDebug;											//�f�o�b�N�ϐ�
	static	CXfile	*m_pXfile;												//�w�t�@�C���ϐ�
};

#endif