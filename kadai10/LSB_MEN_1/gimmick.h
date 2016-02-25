//***************************************************************
//
//	gimmick.h
//	name:Masatugu Kamada
//	�X�V���F2012/09/11
//
//***************************************************************

#ifndef	GIMMICK_H_
#define	GIMMICK_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
class	CGimmick:public	CScene_x
{
public:
	CGimmick();																					//�C���X�g���N�^
	~CGimmick();																				//�f�X�g���N�^
	virtual	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice, D3DXVECTOR3 vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo);								//������
	virtual	void	Uninit(void);																		//�I��
	virtual	void	Update(void);																		//�X�V
	virtual	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CGimmick	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Scail,D3DXVECTOR3	rot,D3DXVECTOR3	Speed,int	TexNo);					//�Z�b�e�B���O
	void	GetVtx(VERTEX_3D	*Vtx){*Vtx = m_Vertex_3d;};

private:
	LPD3DXMESH	m_pMesh;																		//���b�V��
	LPD3DXBUFFER	m_pD3DXMatBuff;																//�o�b�t�@
	DWORD		m_nNumMat;																		//�`��ϐ�
	VERTEX_3D	m_Vertex_3d;																	//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																		//�}�g���b�N�X
	int	m_nTex;																					//�摜�ԍ�
};


#endif