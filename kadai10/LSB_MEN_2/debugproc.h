//***************************************************************
//
//	debugproc.h
//	name:Masatugu Kamada
//
//***************************************************************

#ifndef	DEBUGPROC_H_
#define	DEBUGPROC_H_

//***************************************************************
//	�N���X��`
//***************************************************************
class	CDebugProc
{
public:
	CDebugProc();									//�R���X�g���N�^
	~CDebugProc();									//�f�X�g���N�^

	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice);		//������
	void	Uninit(void);							//�I��
	static	void	Print(char	*fmt,...);			//�������ݐݒ�
	static	void	Draw(void);						//�`��

private:
	static	LPD3DXFONT	m_pD3DXFont;				//�t�H���g�ϐ�
	static	char	m_aStr[1028];					//�����z��
	bool	Switch;									//�����\���؂�ւ��t���O

};

#endif