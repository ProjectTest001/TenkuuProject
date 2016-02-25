//***************************************************************
//
//	model.h
//	name:Masatugu Kamada
//	update�F2012/11/05
//
//***************************************************************


#ifndef	MODEL_H_
#define	MODEL_H_

//***************************************************************
//	�}�N����`
//***************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CModel
{
public:
	CModel();																//�R���X�g���N�^
	~CModel();															//�f�X�g���N�^


	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,int	nType,D3DXVECTOR3	pos,
							D3DXVECTOR3	rot,int	TexNo);		//������
	void	Uninit(void);													//�I��
	void	Update(void);													//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);														//�`��
	static	CModel	*Create(LPDIRECT3DDEVICE9	pDevice,int	nType,D3DXVECTOR3	pos,
							D3DXVECTOR3	rot,int	TexNo);												//����
	void	SetParent(CModel	*pModel){m_pParent = pModel;};									//�e���f���̃Z�b�g
	void	SetVertex(D3DXVECTOR3	pos){m_Vertex_3d.vtx = pos;};
	void	SetRot(D3DXVECTOR3	rot){m_Vertex_3d.Rot_vtx = rot;};
	D3DXMATRIX	GetMtxWorld(void){return	m_mtxWorld;};											//���f���}�g���b�N�X�̎擾
	
private:
	CModel	*m_pParent;																			//�e���f���ւ̃|�C���^
	VERTEX_3D	m_Vertex_3d;																	//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																		//�}�g���b�N�X
	int	m_nTex;																					//�摜�ԍ�
	int	m_nmodel;																				//���f���ԍ�

};

#endif