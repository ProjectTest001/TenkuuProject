//***************************************************************
//
//	renderer.h
//	name:Masatugu Kamada
//	�X�V���F2012/05/19
//
//***************************************************************

#ifndef	RENDERER_H_
#define	RENDERER_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
//�e�N�X�`�����
#define	WHITE_TEXTURE_FILE	("TEXTURE/����.png")				//���f���摜
#define	YEROWW_TEXTURE_FILE	("TEXTURE/���F.png")				//���f���摜
#define	BLUE_TEXTURE_FILE	("TEXTURE/blue.png")				//�摜�i�v���C���[�Ɏg���j
#define	BULLET_TEXTURE_FILE	("TEXTURE/bullet.png")				//�e�摜
#define	FIELD_TEXTURE_FILE	("TEXTURE/field.png")				//�n�ʉ摜
#define	WALL_TEXTURE_FILE	("TEXTURE/��.png")					//�ǉ摜
#define	SKY_TEXTURE_FILE	("TEXTURE/��.bmp")					//��摜
#define	MOUNTION_TEXTURE_FILE	("TEXTURE/mountain000.png")		//�R�摜
#define	EXPLOSION_TEXTURE_FILE	("TEXTURE/kirakira.png")		//�����p�摜
#define	NUMBER_TEXTURE_FILE	("TEXTURE/number.png")				//�X�R�A�摜
#define	TIME_TEXTURE_FILE	("TEXTURE/time_waku.png")			//���Ԙg�摜
#define	SCORE_TEXTURE_FILE	("TEXTURE/score_waku.png")			//�X�R�A�g�摜
#define	FADE_TEXTURE_FILE	("TEXTURE/fade.png")				//�t�F�[�h�C���E�A�E�g�p�摜
#define	TEXT_TEXTURE_FILE	("TEXTURE/mozi.png")				//�����摜�iPUSH�@ENTER�j
#define	TEXT2_TEXTURE_FILE	("TEXTURE/�`���[�g���A��.png")		//�����摜�i�`���[�g���A���ē��j
#define	TITLE_TEXTURE_FILE	("TEXTURE/LSB_MEN_title.png")				//�^�C�g���摜
#define	TITLE2_TEXTURE_FILE	("TEXTURE/karie.png")				//�^�C�g���摜
#define	LINE_TEXTURE_FILE	("TEXTURE/line.png")				//���C���摜
#define	TUTORIAL_TEXTURE_FILE	("TEXTURE/setumei.png")			//�����摜
#define	GAME_OVER_TEXTURE_FILE	("TEXTURE/gameover.png")		//�Q�[���I�[�o�[�摜
#define	GAME_CLEAR_TEXTURE_FILE	("TEXTURE/clear.png")			//�Q�[���N���A�摜
#define	SHADOW_TEXTURE_FILE		("TEXTURE/effect.jpg")			//�e�摜
#define	GIMMICK_TEXTURE_FILE		("TEXTURE/gimmick000.jpg")	//�M�~�b�N�摜
#define	TREE_TEXTURE_FILE		("TEXTURE/tree000.png")	//�M�~�b�N�摜
#define	STOP_TEXTURE_FILE	("TEXTURE/stop.png")				//�|�[�Y�摜


//���f���֘A
#define	GAME_OVER_TEXTURE_FILE1	("model/�_�P.x")				//�Q�[���I�[�o�[���f��
#define	GAME_OVER_TEXTURE_FILE2	("model/�_�Q.x")				//�Q�[���I�[�o�[���f��
#define	GAME_OVER_TEXTURE_FILE3	("model/�_�R.x")				//�Q�[���I�[�o�[���f��

//***************************************************************
//	�N���X��`
//***************************************************************
class	CRenderer
{
public:
	CRenderer();	//�R���X�g���N�^
	~CRenderer();	//�f�X�g���N�^
	
	typedef	enum
	{
		NOMAL,				//�ʏ�
		ADD,				//���Z����
		SUBTRACTION,		//���Z����
		TYPE_MAX,
	}RENDER_TYPE;

	HRESULT	Init(HWND	hWindow,BOOL	bwindow);			//������
	void	Uninit(void);									//�I��
	void	Update();										//�X�V
	void	Draw();											//�`��
	static	void	SetRenderType(RENDER_TYPE	type);		//�`��^�C�v�̕ύX

	//�f�o�C�X��Ԃ��֐�
	static	LPDIRECT3DDEVICE9	GetDevice(void);

private:

	LPDIRECT3D9	m_pD3D;
	static	LPDIRECT3DDEVICE9	m_D3DDevice;						//�f�o�C�X
	static	int	m_nType;
};

#endif