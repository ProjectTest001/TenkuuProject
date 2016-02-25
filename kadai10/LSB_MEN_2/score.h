//***************************************************************
//
//	number.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SCORE_H_
#define	SCORE_H_

//***************************************************************
//	�}�N����`
//***************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
class	CScore:public	CScene
{
public:
	CScore(int	nPriority = 6);																					//�C���X�g���N�^
	~CScore();																				//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CScore	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght);					//�Z�b�e�B���O
	static	void	SetScore(int	nScore);
	static	int	GetScore(void){return	m_nScore;};

private:
	static	CNumber	*m_apNumber[8];
	static	CScene2d	*m_ap2d;
	static	int	m_nScore;

};

#endif