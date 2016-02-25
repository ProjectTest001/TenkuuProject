//***************************************************************
//
//	scenebillboard.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SCENEBILLBOARD_H_
#define	SCENEBILLBOARD_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CSceneBillboard:public	CScene
{
public:
	CSceneBillboard(int	nPriority = 5);																									//�C���X�g���N�^
	~CSceneBillboard();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CSceneBillboard	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXCOLOR	color,int	TexNo);					//�Z�b�e�B���O

private:

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//�o�b�t�@
	VERTEX_3D	m_Vertex_3d;																					//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																						//�}�g���b�N�X
	int	m_nTex;																					//�摜�ԍ�
};



#endif