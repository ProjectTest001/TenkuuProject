//***************************************************************
//
//	scene.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
//
//***************************************************************

#ifndef	SCENE_H_
#define	SCENE_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define	MAX_LIST	(8)	//���X�g�\���̑���

//*****************************************************************************
//�\����
//*****************************************************************************
//�Q�c�e�N�X�`���\����
typedef	struct
{
	D3DXVECTOR3	vtx;		//���Wx,y,z
	float	rhw;			//�o�[�X�̕␳�l
	D3DCOLOR	diffuse;	//���_�F
	D3DXVECTOR2	tex;		//�e�N�X�`���t�u���W
	D3DXVECTOR2	Scail;		//�傫��
}VERTEX_2D;

//�R�c�e�N�X�`���\����
typedef	struct
{
	D3DXVECTOR3	vtx;			//���Wx,y,z
	D3DXVECTOR3	hor;			//�@��
	D3DCOLOR	diffuse;		//���_�F
	D3DXVECTOR2	tex;			//�e�N�X�`���t�u���W
	D3DXVECTOR3	vertex;			//���_��
	int	index;					//�C���f�b�N�X��
	int	primitive;				//�v���~�e�B�u��
	D3DXVECTOR3	Rot_vtx;		//��]�p�x
	D3DXVECTOR3	Scail_vtx;		//���ƍ���
	bool	MoveFlag;			//�ړ���
	D3DXVECTOR3	*DataVtx;		//�\�����W���
	D3DXVECTOR3	Speed_vtx;		//���x
	float	PosNowY;			//���݈ʒu
}VERTEX_3D;

//���̑��̊�{�X�e�[�^�X
typedef	struct
{
	D3DXVECTOR3	Speed_vtx;		//���x
	D3DXVECTOR3	Rot_vtx;		//��]�p�x
	D3DXVECTOR3	Scail_vtx;		//�g��E�k��
}STATAS;

//***************************************************************
//	�N���X��`
//***************************************************************
class	CScene
{
public:

	//�I�u�W�F�N�g�^�C�v
	typedef	enum
	{
		TYPE_GIMMICK = 0,			//�M�~�b�N�n�i�ړ������j
		TYPE_MAX,					//���̑�
	}OBJECT_TYPE;
	OBJECT_TYPE	m_nType;														//�I�u�W�F�N�g�^�C�v
	CScene(int	nPriority = 3);											//�C���X�g���N�^(�����F���炤�K�w�ԍ��i�f�t�H���g�����͇B�ԁj�j
	virtual	~CScene();													//�f�X�g���N�^
	virtual	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice){return	S_OK;};		//������
	virtual	void	Uninit(void) = 0;									//�I��
	virtual	void	Update(void) = 0;									//�X�V
	virtual	void	Draw(LPDIRECT3DDEVICE9	pDevice) = 0;				//�`��
	static	void	UninitAll(void);									//�X�e�[�g�̏I������
	void	Release(void);												//�I�u�W�F�N�g�̔j��
	static	void	ReleaseAll(void);									//�I�u�W�F�N�g�̑S�j��
	static	void	UpdateAll(void);									//�S�X�V
	static	void	DrawAll(LPDIRECT3DDEVICE9	pDevice);				//�S�`��
	virtual void	GetVtx(VERTEX_3D	*Vtx){};						//�ʒu�擾
	static	CScene	*GetTopScene(int	Cnt){return	m_apTop[Cnt];};		//�ŏ���scene�N���X�擾�֐�
	CScene	*GetNext(void){return	m_pNext;};							//����scene�N���X�擾�֐�
	OBJECT_TYPE	GetType(void){return	m_nType;};						//�I�u�W�F�N�g�^�C�v�擾�֐�
	void	SetObjectType(OBJECT_TYPE	Type){m_nType = Type;};			//�I�u�W�F�N�g�^�C�v�Z�b�g�֐�
private:
	static	CScene	*m_apTop[MAX_LIST];									//�擪�̃��X�g�\���z��
	static	CScene	*m_apCur[MAX_LIST];									//���݂̃��X�g�\���z��
	CScene	*m_pPrev;													//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene	*m_pNext;													//���̃I�u�W�F�N�g�ւ̃|�C���^
	static	CScene	*m_pTop;											//���X�g�̐擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static	CScene	*m_pCur;											//���X�g�̌��݂̃I�u�W�F�N�g�ւ̃|�C���^
	int	m_nPriority;													//�����̃v���C�I���e�B�ԍ��i�K�w�ԍ��j
	bool	m_bDelete;													//���S�t���O
};

#endif