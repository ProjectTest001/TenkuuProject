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
//class	CBullet;

//�v���C���[�N���X
class	CPlayer:public	CScene_x
{
public:
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
private:

	float	PurposeRot;																			//�ړI�̊p�x
	float	ResultRot;																			//�v���C���[�̍���̊p�x
	bool	jump;
	static	bool	m_bDeath;
	bool	clear;
	CScene	*m_pSceneLink;																		//�M�~�b�N�ۑ��p�ϐ�
};



#endif