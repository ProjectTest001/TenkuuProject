//***************************************************************
//
//	scene_x.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SCENE_X_H_
#define	SCENE_X_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
class	CScene_x:public	CScene
{
public:
	CScene_x(int	nPriority = 4);																					//�C���X�g���N�^
	~CScene_x();																				//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo);								//������
	void	Uninit(void);																		//�I��
	void	Update(void);																		//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CScene_x	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,const	char	*Name,int	TexNo);					//�Z�b�e�B���O

private:

protected:

	LPD3DXMESH	m_pMesh;																		//���b�V��
	LPD3DXBUFFER	m_pD3DXMatBuff;																//�o�b�t�@
	DWORD		m_nNumMat;																		//�`��ϐ�
	VERTEX_3D	m_Vertex_3d;																	//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																		//�}�g���b�N�X
	int	m_nTex;																					//�摜�ԍ�

};



#endif