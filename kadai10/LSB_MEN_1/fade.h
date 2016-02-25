//***************************************************************
//
//	fade.h
//	name:Masatugu Kamada
//	�X�V���F2012/07/11
//
//***************************************************************

#ifndef	FADE_H_
#define	FADE_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
class	CFade:public	CScene
{
public:
	CFade(int	nPriority = 7);																	//�C���X�g���N�^
	~CFade();																				//�f�X�g���N�^

	//�t�F�[�h���[�h�ݒ�
	typedef	enum
	{
		NONE = 0,			//�ʏ���
		FADEIN,				//�t�F�[�h�C��
		FADEIN_END,			//�t�F�[�h�C���I��
		FADEOUT,			//�t�F�[�h�A�E�g
		FADEOUT_END,		//�t�F�[�h�A�E�g�I��
		FADE_MAX
	}STATUS;

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,int	TexNo);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	void	Start(STATUS	status,int	Time);													//�t�F�[�h�̐؂�ւ�
	static	int	GetStatus(void){return	m_status;};																	//�t�F�[�h��Ԃ̎擾

private:
	static	int	m_status;																		//�t�F�[�h���[�h�p�ϐ�
	int	m_nTime;																				//����
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//�o�b�t�@
	VERTEX_2D	m_Vertex_2d;																	//�Q�c�f�[�^�\����
	int	m_nTex;																					//�摜�ԍ�
};





#endif