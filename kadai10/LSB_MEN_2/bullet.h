//***************************************************************
//
//	bullet.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	BULLET_H_
#define	BULLET_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CBullet:public	CSceneBillboard
{
public:
	CBullet();																									//�C���X�g���N�^
	~CBullet();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CBullet	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo);					//�Z�b�e�B���O
	static	VERTEX_3D	GetVertex(void){return	m_Vertex_3d;};												//���_���̎擾

private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//�o�b�t�@
	static	VERTEX_3D	m_Vertex_3d;																			//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																						//�}�g���b�N�X
	int	m_nTex;																									//�摜�ԍ�
};



#endif

