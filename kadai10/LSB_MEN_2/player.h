//*****************************************************************************
//
//	player.h
//	name�FMasatugu Kamada
//	�X�V���F2012/05/25
//
//*****************************************************************************

#ifndef	PLAYER_H_
#define	PLAYER_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define	MOVE	(0.048f)		//�ړ���
#define	JUMP	(1.5f)		//�W�����v��
#define	SPAN_SHOT	(5)	//�e�̔��ˊԊu
#define	PLAYER_ROT	(0.1f)	//��]���x
//*****************************************************************************
//	�\����
//*****************************************************************************

//*****************************************************************************
//	�N���X��`
//*****************************************************************************

//�O���Q��
class	CShadow;
class	CModel;

//�v���C���[�N���X
class	CPlayer:public	CScene_x
{
public:

	//���[�V�����̎��
	typedef	enum
	{
		MOTIONTYPE_NEUTRAL = 0,				//�������Ă��Ȃ�
		MOTIONTYPE_WALK,					//����
		MOTIONTYPE_PUNCH,					//�p���`
		MOTIONTYPE_KICK,					//�L�b�N
		MOTIONTYPE_KICK2,					//�L�b�N
		MOTIONTYPE_JUMP,					//�W�����v
		MOTIONTYPE_JUMPEND,					//�W�����v��̒��n
		MOTIONTYPE_HIT,						//�̂�����
		MOTION_MAX,							//����
	}MOTIONTYPE;

	CPlayer();											//�R���X�g���N�^
	~CPlayer();											//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo);				//������
	void	Uninit(void);								//�I��
	void	Update(void);								//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);									//�`��
	static	CPlayer	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,int	TexNo);	//����
	VERTEX_3D	GetVtx(void){return	m_Vertex_3d;};
	bool	HitWall(void);
	static	void	PlayerDeath(void){m_bDeath = true;	PlaySound(SE_00,DMUS_SEGF_SECONDARY);};
	void	HitGimmick(void);

	MOTIONTYPE	GetMotion(void){return	m_motionType;}			//���[�V�����󋵎擾�֐�
private:

	float	PurposeRot;																			//�ړI�̊p�x
	float	ResultRot;																			//�v���C���[�̍���̊p�x
	bool	jump;
	static	bool	m_bDeath;
	bool	clear;
	CScene	*m_pSceneLink;																		//�M�~�b�N�ۑ��p�ϐ�
	CShadow	*m_pShadow;																			//�l�p�e

	CModel	*m_apModel[MODELPARTS_MAX];																		//�e�p�[�c�̃��f���|�C���^

	int	m_nPartsNumber;			//�p�[�c�ԍ�

	//���[�V�����֘A
	void	LoadMotionData(void);						//���[�V�����f�[�^�ǂݍ���
	//void	SetMotionData(FILE	*File,KEY_INFO	*KeyData);						//���[�V�����f�[�^�̃Z�b�g
	void	SetMotion(MOTIONTYPE	type,int	nFrameBlend,bool	bBlend);		//���[�V�����̐ݒ�
	void	UpdateMotion(void);					//���[�V�����̍X�V
	MOTIONTYPE	m_motionType;					//���݂̃��[�V�����̎��
	KEY_INFO	*m_pKeyInfo;						//�Ώۃ��[�V�����̃L�[�ւ̃|�C���^
	int	m_nKey;									//�Ώۃ��[�V�����̃L�[Number
	int	m_nNumber;								//�Ώۃ��[�V�����̃L�[�̑���
	int	m_nCountMotion;							//���[�V�����J�E���^
	bool	m_bLoopMotion;						//���[�v���[�V�������ǂ���
	bool	m_bMotion;							//���[�V�������Ă��邩�ǂ���
	bool	m_bFinishMotion;					//���[�V�������I�����Ă��邩�ǂ���
	bool	m_bBlendNow;						//�u�����h�����ǂ���

	//�u�����h�֘A
	KEY_INFO	*m_pKeyInfoBlend;
	int	m_nNumBlend;
	int	m_nKeyBlend;
	int	m_nCountMotionBlend;
	bool	m_bLoopMotionBlend;

	int	m_nFrameBlend;					//�u�����h����ۂɂ�����t���[����
	int	m_nCountBlend;					//�u�����h���̃J�E���^
	bool	m_bBlendMotion;				//�u�����h���邩�ǂ���

	//���[�V�����ϐ�
	static	MOTIONDATA	*m_apKey;

};



#endif