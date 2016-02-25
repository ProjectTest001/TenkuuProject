//***************************************************************
//
//	score.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/30
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<math.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"camera.h"
#include	"renderer.h"
#include	"manager.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"scene2d.h"
#include	"scene_x.h"
#include	"player.h"
#include	"number.h"
#include	"score.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
CNumber	*CScore::m_apNumber[8];
CScene2d	*CScore::m_ap2d = NULL;
int	CScore::m_nScore = 0;

//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CScore::CScore(int	nPriority):CScene(nPriority)
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CScore::~CScore()
{

}

//***************************************************************
//	������
//***************************************************************
HRESULT	CScore::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//�g����
	m_ap2d = new	CScene2d(5);
	m_ap2d->Init(CRenderer::GetDevice(),vtx,D3DXVECTOR2(width * 8 + 20,heght + 30),CScene2d::TYPE_MAX,SCORE_TEXTURE);

	//�����̈ʒu����
	vtx.x += 10;
	vtx.y += 20;

	//�N���X����
	for(int	i = 0 ; i < 8; i++)
	{
		m_apNumber[i] = new	CNumber;
		m_apNumber[i]->Init(pDevice,vtx,width,heght,NUMBER_TEXTURE);
		vtx.x += width;
	}
	//������
	m_nScore = 0;

	return	S_OK;
}
//***************************************************************
//	�X�R�A����
//����
//LPDIRECT3DDEVICE9	pDevice�F�f�o�C�X�|�C���^
//D3DXVECTOR3	vtx�F�w����W
//�߂�l
//CScene2d�F���N���X
//***************************************************************
CScore	*CScore::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//�|�C���^�錾
	CScore	*pScore;

	//�N���X����
	pScore = new	CScore;

	//������
	pScore->Init(pDevice,vtx,width,heght);

	return	pScore;

}

//***************************************************************
//	�I��
//***************************************************************
void	CScore::Uninit()
{
	//�������
	for(int	i = 0 ; i < 8; i++)
	{
		m_apNumber[i]->Uninit();
		delete	m_apNumber[i];
		m_apNumber[i] = NULL;
	}

}

//***************************************************************
//	�X�V
//***************************************************************
void	CScore::Update()
{

}


//***************************************************************
//	�X�R�A�̃Z�b�e�B���O
//***************************************************************
void	CScore::SetScore(int	nScore)
{
	//�X�R�A�̑���
	m_nScore += nScore;
	int	nScoreCount = 10000000;

	for(int	i = 0; i < 8; i++,nScoreCount/=10)
	{
		int	nPoint = (m_nScore % (nScoreCount * 10)) / nScoreCount;
		m_apNumber[i]->SetNumber(nPoint);
	}
}

//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//***************************************************************
void	CScore::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	m_ap2d->Draw(pDevice);

	for(int	i = 0 ; i < 8; i++)
	{
		m_apNumber[i]->Draw(pDevice);
	}
}
