//***************************************************************
//
//	game.h
//	name:Masatugu Kamada
//	�X�V���F2012/07/10
//
//***************************************************************

#ifndef	GAME_H_
#define	GAME_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define	MAX_PLAYER		(1)				//�v���C���[�ő吔�i��l�p���l���Ă邩�瑽������Ȃ��j

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
//�O���Q��
class	CPose;

class	CGame
{
public:
	CGame();	//�C���X�g���N�^
	~CGame();	//�f�X�g���N�^

	HRESULT	Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);
	static	VERTEX_3D	GetPlayer(void){return	m_pPlayer[0]->GetVtx();};

private:
	static	CScene3d	*m_pScene3d;										//�R�c�ϐ�
	static	CScore	*m_pScore;												//�X�R�A�ϐ�
	static	CTime	*m_pTime;												//���ԕϐ�
	static	CRenderer	*m_pRenderer;										//�����_�\�ϐ�

	bool	m_bSwitch;														//�|�[�Y����
	static	CPose	*m_pPose;												//�|�[�Y�ϐ�
	static	CPlayer	*m_pPlayer[MAX_PLAYER];									//�v���C���[�ϐ�

};

#endif