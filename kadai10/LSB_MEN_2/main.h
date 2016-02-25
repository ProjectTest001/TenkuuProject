//*****************************************************************************
//
//
//
//
//*****************************************************************************
#ifndef	MAIN_H_
#define	MAIN_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define	SCREEN_WIDTH	(800)		//�E�B���h�E����
#define	SCREEN_HEIGHT	(600)		//�E�B���h�E�c��
#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#define	RAZIAN				(3.14f / 180.0f)	//���W�A���␳

//���f���p�[�c�\����
typedef	enum
{
	MODELPARTS_WAIST = 0,		//��
	MODELPARTS_BODY,			//�g��
	MODELPARTS_NECK,			//��
	MODELPARTS_HEAD,			//��
	MODELPARTS_RIGHTARM,		//�E�r
	MODELPARTS_RIGHTELBOW,		//�E�I
	MODELPARTS_RIGHTHAND,		//�E��
	MODELPARTS_LEFTARM,			//���r
	MODELPARTS_LEFTELBOW,		//���I
	MODELPARTS_LEFTHAND,		//����
	MODELPARTS_RIGHTLEG,		//�E������
	MODELPARTS_RIGHTKNEE,		//�E�G
	MODELPARTS_RIGHTFOOT,		//�E��
	MODELPARTS_LEFTLEG,			//��������
	MODELPARTS_LEFTKNEE,		//���G
	MODELPARTS_LEFTFOOT,		//����
	MODELPARTS_MAX,				//�p�[�c����
}MODELPARTS;

//���[�V�����p�\����
//���[�V�����f�[�^
typedef	struct
{
	float	posx;
	float	posy;
	float	posz;

	float	rotx;
	float	roty;
	float	rotz;

}KEY;

//�L�[���\����
typedef	struct
{
	int	nFrame;	//�Đ��t���[����
	KEY	aKEY[MODELPARTS_MAX];	//�p�[�c���
}KEY_INFO;

//�L�[���̏W���\����
typedef	struct
{
	KEY_INFO	*pKey;
	int	NumFrame;
}MOTIONDATA;

#endif