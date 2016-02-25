//****************************************************************
//
//	pose.h
//	name�FMasatugu Kamada
//	�X�V���F2012/08/19
//
//****************************************************************

#ifndef	POSE_H_
#define	POSE_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class	CPose
{
public:
	CPose();																	//�C���X�g���N�^
	~CPose();																				//�f�X�g���N�^

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	void	SetPose(bool	pose){m_bPose = pose;};												//�|�[�Y�ݒ�
	static	bool	GetPose(void){return	m_bPose;};											//�|�[�Y����擾
private:
	int	m_nTime;																				//����
	CScene2d	*m_pPose2d;
	static	bool	m_bPose;
};

#endif