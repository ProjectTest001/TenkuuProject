//***************************************************************
//
//	field.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/29
//
//***************************************************************

#ifndef	FIELD_H_
#define	FIELD_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//*****************************************************************************
//�\����
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CField:public	CScene3d
{
public:
	CField();																									//�C���X�g���N�^
	~CField();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
					D3DXVECTOR3	Rot,float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CField	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
								D3DXVECTOR3	Rot,float	Xwidth,float	Zwidth,int	cutX,int	cutZ,int	TexNo);					//�Z�b�e�B���O
	static	VERTEX_3D	GetVertex(void){return	m_Vertex_3d;};												//���_���̎擾

private:
	static	VERTEX_3D	m_Vertex_3d;																			//�R�c�f�[�^�\����
	D3DXVECTOR3	*m_pNormalBuff;																					//�@���̃��[�N�p�|�C���^
};



#endif