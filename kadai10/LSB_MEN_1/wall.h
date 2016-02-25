//***************************************************************
//
//	wall.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	WALL_H_
#define	WALL_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************

//*****************************************************************************
//�\����
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CWall:public	CScene3d
{
public:
	CWall();																									//�C���X�g���N�^
	~CWall();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
				D3DXVECTOR3	Rot,float	width,float	heght,int	cutX,int	cutY,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CWall	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,
							D3DXVECTOR3	Rot,float	width,float	heght,int	cutX,int	cutY,int	TexNo);					//�Z�b�e�B���O
	static	bool	HitWall(void){return	m_bHit;};

private:
	static	bool	m_bHit;
};



#endif