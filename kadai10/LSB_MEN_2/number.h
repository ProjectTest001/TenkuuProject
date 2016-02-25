//***************************************************************
//
//	number.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	NUMBER_H_
#define	NUMBER_H_

//***************************************************************
//	�}�N����`
//***************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
class	CNumber
{
public:
	CNumber(int	nPriority = 6);																					//�C���X�g���N�^
	~CNumber();																				//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CNumber	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght,int	TexNo);					//�Z�b�e�B���O
	void	SetNumber(int	nNumber);

private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//�o�b�t�@
	VERTEX_2D	m_Vertex_2d;																	//�Q�c�f�[�^�\����
	int	m_nTex;																					//�摜�ԍ�
};

#endif