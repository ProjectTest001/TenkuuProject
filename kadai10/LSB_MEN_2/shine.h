//*****************************************************
//
//	shine.h
//	name:MasatuguKamada
//	create:2012/11/08
//	update:2012/11/08
//
//*****************************************************

#ifndef	SHINE_H_
#define	SHINE_H_

//*****************************************************
//	�}�N����`
//*****************************************************

//*****************************************************
//	�N���X�֐�
//*****************************************************
class	CShine:public	CSceneBillboard
{
public:
	CShine();								//�R���X�g���N�^
	~CShine();								//�f�X�g���N�^

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	pos,D3DXCOLOR	color,int	life,D3DXVECTOR3	Scail,
					float	Speed,int	TexNo);							//������
	void	UnInit();						//�I��
	void	Update();						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);							//�`��
	static	CShine	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	pos,D3DXCOLOR	color,int	life,D3DXVECTOR3	Scail,
					float	Speed,int	TexNo);		//����

private:
	int	m_nLife;					//���C�t
	float	m_fSpeed;				//�������x

};

#endif