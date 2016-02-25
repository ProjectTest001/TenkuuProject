//***************************************************************
//
//	sky.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/29
//
//***************************************************************

#ifndef	SKY_H_
#define	SKY_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//*****************************************************************************
//�\����
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CSky:public	CScene3d
{
public:
	CSky();																									//�C���X�g���N�^
	~CSky();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
											int	cut,float	heght,int	cutY,float	rot,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CSky	*Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
															int	cut,float	heght,int	cutY,float	rot,int	TexNo);					//�Z�b�e�B���O

private:

	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff2;																		//�t�^�p�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff2;																	//�t�^�p�C���f�b�N�X�o�b�t�@
};



#endif