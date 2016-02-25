//******************************************************
//
//	texture.h
//	name:Masatugu Kamada
//	create:2012/09/28
//	update:2012/09/28
//
//******************************************************

#ifndef	XFILE_H_
#define	XFILE_H_

//*****************************************************************************
//	�}�N����`
//*****************************************************************************

//�摜�ԍ�

//�v���C���[
#define	LSB_ID (0)
#define	LSB_NUM	(16)

//�G
#define	ROBO_ENEMY_ID	(LSB_ID + LSB_NUM)
#define	ROBO_ENEMY_NUM	(1)

//�A�C�e��
//�R�C��
#define	COIN_ID	(ROBO_ENEMY_ID + ROBO_ENEMY_NUM)
#define	COIN_NUM	(1)

//��
#define	STAR_ID	(COIN_ID + COIN_NUM)
#define	STAR_NUM	(1)

#define	MAX_XFILE		(STAR_ID + STAR_NUM)

//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class	CXfile
{
public:
	CXfile();
	~CXfile();
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);													//������
	void	UnInit(void);																		//�I��

	//�w�t�@�C�����擾
	static	LPD3DXMESH	GetMesh(int	No){return	m_pMesh[No];};	
	static	LPD3DXBUFFER	GetBuffer(int	No){return	m_pD3DXMatBuff[No];};	
	static	DWORD	GetWord(int	No){return	m_nNumMat[No];};		

private:

	static	LPD3DXMESH	m_pMesh[MAX_XFILE];																		//���b�V��
	static	LPD3DXBUFFER	m_pD3DXMatBuff[MAX_XFILE];																//�o�b�t�@
	static	DWORD		m_nNumMat[MAX_XFILE];																		//�`��ϐ�

};

#endif