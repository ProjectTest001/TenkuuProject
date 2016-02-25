//*****************************************************************************
//
//	light.h
//	name�FMasatugu Kamada
//	�X�V���F2012/05/26
//
//*****************************************************************************

#ifndef	LIGHT_H_
#define	LIGHT_H_


//*****************************************************************************
//	�N���X��`
//*****************************************************************************

class	CLight
{
public:
	CLight();															//�R���X�g���N�^
	~CLight();															//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);												//������
	void	Uninit(void);											//�I��
	void	Update(void);											//�X�V
	static	void	SetOffLight(LPDIRECT3DDEVICE9	pDevice){	pDevice->LightEnable(0,FALSE);};
	static	void	SetOnLight(LPDIRECT3DDEVICE9	pDevice){	pDevice->LightEnable(0,TRUE);};

private:

	D3DLIGHT9	m_aLight[3];								//���C�g�ϐ�

};

#endif
