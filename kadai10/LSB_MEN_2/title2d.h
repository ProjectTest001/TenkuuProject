//***************************************************************
//
//	title2d.h
//	name:Masatugu Kamada
//	create:2012/10/20
//	update�F2012/10/20
//
//***************************************************************

#ifndef	TITLE2D_H_
#define	TITLE2D_H_

//***************************************************************
//	�}�N����`
//***************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CTitle2d:public	CScene2d
{
public:

	typedef	enum
	{
		NONE = 0,
		MOVE_TYPE,
		MOVE_KEY,
		MOVE_TUTORIAL,
		TYPE_MAX,
	}TYPE;

	CTitle2d();																					//�C���X�g���N�^
	~CTitle2d();																				//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CTitle2d	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);					//�Z�b�e�B���O

private:
	//LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//�o�b�t�@
	//VERTEX_2D	m_Vertex_2d;																	//�Q�c�f�[�^�\����
	int	m_nType;
	bool	bmove;
	//int	m_nTex;																					//�摜�ԍ�
};






#endif