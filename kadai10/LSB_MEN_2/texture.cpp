//******************************************************
//
//	texture.cpp
//	name:Masatugu Kamada
//	create:2012/09/28
//	update:2012/09/28
//
//******************************************************

//***************************************************************
//	�C���N���[�h
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<math.h>
#include	"main.h"
#include	"renderer.h"
#include	"manager.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
LPDIRECT3DTEXTURE9	CTexture::m_pD3DTexture[MAX_TEXTURE] = {NULL};

//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CTexture::CTexture()
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CTexture::~CTexture()
{

}

//***************************************************************
//	������
//	����
//	LPDIRECT3DDEVICE9	pDevice:�f�o�C�X�|�C���^
//	�߂�l
//	�Ȃ�
//***************************************************************
HRESULT	CTexture::Init(LPDIRECT3DDEVICE9	pDevice)
{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, WHITE_TEXTURE_FILE, &m_pD3DTexture[WHITE_TEXTURE]);			//���摜
		D3DXCreateTextureFromFile(pDevice, YEROWW_TEXTURE_FILE, &m_pD3DTexture[YEROWW_TEXTURE]);		//���F�摜
		D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_FILE, &m_pD3DTexture[BULLET_TEXTURE]);		//�e�ۉ摜
		D3DXCreateTextureFromFile(pDevice, FIELD_TEXTURE_FILE, &m_pD3DTexture[FIELD_TEXTURE]);			//�t�B�[���h�摜
		D3DXCreateTextureFromFile(pDevice, WALL_TEXTURE_FILE, &m_pD3DTexture[WALL_TEXTURE]);			//�ǉ摜
		D3DXCreateTextureFromFile(pDevice, SKY_TEXTURE_FILE, &m_pD3DTexture[SKY_TEXTURE]);				//��摜
		D3DXCreateTextureFromFile(pDevice, MOUNTION_TEXTURE_FILE, &m_pD3DTexture[MOUNTAIN_TEXTURE]);	//�R�摜
		D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURE_FILE, &m_pD3DTexture[EXPLOSION_TEXTURE]);	//�����摜
		D3DXCreateTextureFromFile(pDevice, NUMBER_TEXTURE_FILE, &m_pD3DTexture[NUMBER_TEXTURE]);		//�����摜
		D3DXCreateTextureFromFile(pDevice, TIME_TEXTURE_FILE, &m_pD3DTexture[TIME_TEXTURE]);			//���ԉ摜
		D3DXCreateTextureFromFile(pDevice, SCORE_TEXTURE_FILE, &m_pD3DTexture[SCORE_TEXTURE]);			//�X�R�A�摜	
		D3DXCreateTextureFromFile(pDevice, FADE_TEXTURE_FILE, &m_pD3DTexture[FADE_TEXTURE]);			//�t�F�[�h�p�摜
		D3DXCreateTextureFromFile(pDevice, TEXT_TEXTURE_FILE, &m_pD3DTexture[TEXT_TEXTURE]);			//�����摜(PUSH ENTER)
		D3DXCreateTextureFromFile(pDevice, TEXT2_TEXTURE_FILE, &m_pD3DTexture[TEXT2_TEXTURE]);			//�����摜�i�`���[�g���A���ē��j
		D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_FILE, &m_pD3DTexture[TITLE_TEXTURE]);			//�^�C�g���摜
		D3DXCreateTextureFromFile(pDevice, LINE_TEXTURE_FILE, &m_pD3DTexture[LINE_TEXTURE]);			//���C���摜
		D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_FILE, &m_pD3DTexture[TUTORIAL_TEXTURE]);	//�`���[�g���A���摜
		D3DXCreateTextureFromFile(pDevice, GAME_OVER_TEXTURE_FILE, &m_pD3DTexture[GAME_OVER_TEXTURE]);	//�Q�[���I�[�o�摜
		D3DXCreateTextureFromFile(pDevice, GAME_CLEAR_TEXTURE_FILE, &m_pD3DTexture[GAME_CLEAR_TEXTURE]);//�Q�[���N���A�摜
		D3DXCreateTextureFromFile(pDevice, SHADOW_TEXTURE_FILE, &m_pD3DTexture[SHADOW_TEXTURE]);		//�e�摜
		D3DXCreateTextureFromFile(pDevice, GIMMICK_TEXTURE_FILE, &m_pD3DTexture[GIMMICK_TEXTURE]);		//�M�~�b�N�摜
		D3DXCreateTextureFromFile(pDevice, STOP_TEXTURE_FILE, &m_pD3DTexture[STOP_TEXTURE]);			//�X�g�b�v�\���摜
		D3DXCreateTextureFromFile(pDevice, TREE_TEXTURE_FILE, &m_pD3DTexture[TREE_TEXTURE]);			//�؉摜
		D3DXCreateTextureFromFile(pDevice, BLUE_TEXTURE_FILE, &m_pD3DTexture[BLUE_TEXTURE]);			//�摜
		D3DXCreateTextureFromFile(pDevice, TITLE2_TEXTURE_FILE, &m_pD3DTexture[24]);
		D3DXCreateTextureFromFileEx(pDevice,WALL_TEXTURE_FILE,D3DX_DEFAULT,D3DX_DEFAULT,3,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,
			D3DX_DEFAULT,0,NULL,NULL,&m_pD3DTexture[WALL_TEXTURE]);
	return	S_OK;
}

//***************************************************************
//	�I��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CTexture::UnInit()
{
	for(int	i = 0; i < MAX_TEXTURE; i++)
	{
		if(m_pD3DTexture[i])
		{
			m_pD3DTexture[i]->Release();
			m_pD3DTexture[i] = NULL;
		}
	}

}

