//***************************************************************
//
//	building.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	BUILDING_H_
#define	BUILDING_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CBuilding:public	CSceneBillboard
{
public:
	CBuilding();																									//�C���X�g���N�^
	~CBuilding();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CBuilding	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,D3DXVECTOR3	Scail,int	TexNo);					//�Z�b�e�B���O

private:

protected:
};

#endif