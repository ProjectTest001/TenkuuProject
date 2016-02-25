//***************************************************************
//
//	shadow.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SHADOW_H_
#define	SHADOW_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//*****************************************************************************
//�\����
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CShadow:public	CScene3d
{
public:
	CShadow();																									//�C���X�g���N�^
	~CShadow();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CShadow	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	life,int	TexNo);					//�Z�b�e�B���O

private:
	float	m_ShadowPoint;
};

#endif