//*****************************************************************************
//
//	enemy.h
//	name�FMasatugu Kamada
//	�X�V���F2012/06/5
//
//*****************************************************************************

#ifndef	ENEMY_H_
#define	ENEMY_H_


//*****************************************************************************
//	�}�N����`
//*****************************************************************************

//*****************************************************************************
//	�\����
//*****************************************************************************
typedef	struct
{
	float	Speed;		//�ړ���
	float	RotSpeed;	//��]���x
	float	JumpUp;		//�W�����v��
	float	Vec;		//�w�苗��
}ENEMY;
//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class	CEnemy:public	CScene_x
{
public:
	CEnemy();											//�C���X�g���N�^
	~CEnemy();											//�f�X�g���N�^

	typedef	enum
	{
		NOMAL_MOVE = 0,
		ROLING,
		JUMPING,
		ROLL_JUMPING,
		PLAYER_JUMPING,
		TRACKING,
		MOVE_MAX,
	};
	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,float	rotspeed,float	jumpup,int	nType,int	TexNo);				//������
	void	Uninit(void);								//�I��
	void	Update(void);								//�X�V
	void	Draw(LPDIRECT3DDEVICE9	pDevice);									//�`��
	static	CEnemy	*Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	rot,float	speed,float	rotspeed,float	jumpup,int	Type,int	TexNo);	//����
	bool	HitEnemy(D3DXVECTOR3	Pos);

private:
	LPD3DXMESH	m_pMesh;																		//���b�V��
	LPD3DXBUFFER	m_pD3DXMatBuff;																//�o�b�t�@
	DWORD		m_nNumMat;																		//�`��ϐ�
	VERTEX_3D	m_Vertex_3d;															//�R�c�f�[�^�\����
	D3DXMATRIX	m_mtxWorld;																		//�}�g���b�N�X
	int	type;																					//�ړ��̎��
	ENEMY	m_aEnamy;																			//�G�X�e�[�^�X
	int	m_nTex;																					//�摜�ԍ�
};



#endif