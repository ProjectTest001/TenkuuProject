//***************************************************************
//
//	mountion.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/29
//
//***************************************************************

#ifndef	MOUNTION_H_
#define	MOUNTION_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//*****************************************************************************
//�\����
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CMountion:public	CScene3d
{
public:
	CMountion();																									//�C���X�g���N�^
	~CMountion();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
											int	cut,float	heght,int	cutY,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CMountion	*Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3	vtx,float	vec,D3DXCOLOR	color,
															int	cut,float	heght,int	cutY,int	TexNo);					//�Z�b�e�B���O

private:


};



#endif