//***************************************************************
//
//	scenebillboard.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	CAMERA_H_
#define	CAMERA_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define	CAMERA_MOVE	(0.5f)		//�ړ���
#define	CAMERA_VETCTOR		(12.0f)		//���_�ƒ����_�̋���
#define	CAMERA_TIMER		(1)		//�J������~����

//***************************************************************
//	�N���X��`
//***************************************************************
class	CCamera
{
public:
	CCamera();														//�C���X�g���N�^
	~CCamera();														//�f�X�g���N�^

	//�J�����̏�������
	typedef	enum
	{
		NOMAL_CAMERA = 0,		//�ʏ펞
		TITLE_CAMERA,			//�^�C�g�����̃J����
		PLAYER_CAMERA,			//�v���C���[�ǔ��J����
		MAUSE_CAMERA,			//�}�E�X�ɂ��ړ����@
		ROT_CAMERA,				//��]���[�h
		IVENT_CAMERA,			//�C�x���g������
		CAMERA_MAX,
	}CAMERA_MODE;

	static	HRESULT	Init(int	mode);											//������
	void	Uninit(void);												//�I��
	void	Update(void);												//�X�V
	static	void	SetCamera(LPDIRECT3DDEVICE9	pDevice);				//�J�����̃Z�b�e�B���O
	static	D3DXMATRIX	GetViewMatrix(void);							//�r���[���擾
	static	D3DXVECTOR3	GetCameraRot(void){return	m_Rot;};			//�J������]�̏��擾
	static	int	GetCameraMode(void){return	m_CameraMode;};				//�J�������[�h�̏��擾
	static	void	SetCameraMode(int	mode){m_CameraMode = mode;};	//�J�������[�h�̐؂�ւ�
	void	PlayerCamera(void);											//�v���C���[�ǔ��֐�
private:
	//�J�����|�W�V�����ϐ�
	static	D3DXVECTOR3	m_posCameraP;								//�J�������W
	static	D3DXVECTOR3	m_posCameraR;								//�J���������_
	static	D3DXVECTOR3	m_posCameraU;								//�J�����������x�N�g��

	static	D3DXMATRIX	m_mtxView;									//�r���[�}�g���b�N�X
	static	D3DXMATRIX	m_mtxProjection;							//�v���W�F�N�V�����}�g���b�N�X

	static	D3DXVECTOR3	m_Rot;										//�J������]�ϐ�
	static	int	m_CameraTimer;										//�J������~����
	static	float	Time;										//�J�������`�⊮�p�ϐ�
	static	int	m_CameraMode;										//�J�������[�h�ϐ�

};



#endif