//***************************************************************
//
//	coin.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	COIN_H_
#define	COIN_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//***************************************************************
//	�N���X��`
//***************************************************************
class	CCoin:public	CItem
{
public:
	CCoin();																					//�C���X�g���N�^
	~CCoin();																				//�f�X�g���N�^
	virtual	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice, D3DXVECTOR3 vtx,int	TexNo);								//������
	virtual	void	Uninit(void);																		//�I��
	virtual	void	Update(void);																		//�X�V
	virtual	void	Draw(LPDIRECT3DDEVICE9	pDevice);													//�`��
	static	CScene_x	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo);					//�Z�b�e�B���O

private:
	bool	get;
	float	vec;
};


#endif