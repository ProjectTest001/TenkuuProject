//***************************************************************
//
//	explosion.h
//	name:Masatugu Kamada
//	�X�V���F2012/06/02
//
//***************************************************************

#ifndef	EXPLOSION_H_
#define	EXPLOSION_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************


//***************************************************************
//	�N���X��`
//***************************************************************
class	CExplosion:public	CSceneBillboard
{
public:
	CExplosion(int	nPriority = 5);																								//�R���X�g���N�^
	~CExplosion();																								//�f�X�g���N�^
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo);									//������
	void	Uninit(void);																						//�I��
	void	Update(void);																						//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);																	//�`��
	static	CExplosion	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,int	TexNo);									//�Z�b�e�B���O

private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;																		//�o�b�t�@
	VERTEX_3D	m_Vertex_3d;																					//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																						//�}�g���b�N�X
	float	m_Time;																								//�����G�t�F�N�g�̎���
	int	m_nTex;																					//�摜�ԍ�
};



#endif

