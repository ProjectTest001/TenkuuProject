//***************************************************************
//
//	title.h
//	name:Masatugu Kamada
//	�X�V���F2012/07/10
//
//***************************************************************

#ifndef	TITLE_H_
#define	TITLE_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class	CTitle
{
public:
	CTitle();	//�C���X�g���N�^
	~CTitle();	//�f�X�g���N�^

	HRESULT	Init(void);		//����������
	void	Uninit(void);	//�I������
	void	Update(void);	//�X�V����
	void	Draw(void);

private:
	static	CRenderer	*m_pRenderer;								//�����_�\�ϐ�
};

#endif