//***************************************************************
//
//	scene2d.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SCENE2D_H_
#define	SCENE2D_H_

//***************************************************************
//	�}�N����`
//***************************************************************
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//	�t�H�[�}�b�g�w��

//�|���S���摜���
#define	POLYGON_X	(50.0f)	//�w���W
#define	POLYGON_Y	(30.0f)		//�x���W
#define	POLYGON_W	(156.0f)	//��
#define	POLYGON_H	(356.0f)		//����

//***************************************************************
//	�N���X��`
//***************************************************************
class	CScene2d:public	CScene
{
public:


	CScene2d(int	nPriority = 6);																					//�C���X�g���N�^
	~CScene2d();																				//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);													//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CScene2d	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR2	Scail,int	Type,int	TexNo);					//�Z�b�e�B���O

private:
	//LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//�o�b�t�@
	//VERTEX_2D	m_Vertex_2d;																	//�Q�c�f�[�^�\����
	int	m_nType;
	bool	bmove;
	//int	m_nTex;																					//�摜�ԍ�

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;														//�o�b�t�@
	VERTEX_2D	m_Vertex_2d;																	//�Q�c�f�[�^�\����

	int	m_nTex;																					//�摜�ԍ�

};


#endif