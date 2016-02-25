//***************************************************************
//
//	scene3d.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SCENE3D_H_
#define	SCENE3D_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//3D�w��

//*****************************************************************************
//�\����
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CScene3d:public	CScene
{
public:
	CScene3d();																									//�C���X�g���N�^
	~CScene3d();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CScene3d	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);					//�Z�b�e�B���O
	static	float	GetHeight(D3DXVECTOR3	pos);												//�n�ʂ̍����̎擾
	static	float	GetHeightPolygon(D3DXVECTOR3	pos,D3DXVECTOR3	vtx0,D3DXVECTOR3	vtx1,D3DXVECTOR3	vtx2);

private:
	D3DXVECTOR3	*m_pNormalBuff;																					//�@���̃��[�N�p�|�C���^

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//�o�b�t�@
	VERTEX_3D	m_Vertex_3d;																					//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																						//�}�g���b�N�X
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff;																	//�C���f�b�N�X�o�b�t�@

	int	m_nTex;																					//�摜�ԍ�

};



#endif