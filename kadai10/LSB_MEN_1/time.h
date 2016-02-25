//***************************************************************
//
//	time.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	TIME_H_
#define	TIME_H_

//***************************************************************
//	�}�N����`
//***************************************************************
#define	TIME_COUNT	(120)					//���Ԑ���
#define	TIME_DIGIT	(3)						//����
//***************************************************************
//	�N���X��`
//***************************************************************
class	CTime:public	CScene
{
public:
	CTime(int	nPriority = 6);																					//�C���X�g���N�^
	~CTime();																				//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CTime	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);					//�Z�b�e�B���O
	static	void	SetTime(int	nScore);
	static	bool	TimeUp(void);
private:

	static	CNumber	*m_apNumber[3];
	static	CScene2d	*m_ap2d;
	static	int	m_nTime;
	int	m_nSpan;

};

#endif