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
#define	HUMAN_ID (0)
#define	HUMAN_NUM (10)
#define	LSB_ID (HUMAN_ID + HUMAN_NUM)
#define	LSB_NUM	(16)
#define	AN_MODEL_ID	(LSB_NUM + LSB_ID)
#define	AN_NUM	(10)

#define	MAX_XFILE		(AN_MODEL_ID + AN_NUM)

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