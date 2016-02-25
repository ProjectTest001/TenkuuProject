//***************************************************************
//
//	time.cpp
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
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"player.h"
#include	"number.h"
#include	"time.h"
#include	"texture.h"

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
CNumber	*CTime::m_apNumber[3];
CScene2d	*CTime::m_ap2d = NULL;
int	CTime::m_nTime = 0;

//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CTime::CTime(int	nPriority):CScene(nPriority)
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CTime::~CTime()
{

}

//***************************************************************
//	������
//***************************************************************
HRESULT	CTime::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//�g����
	m_ap2d = new	CScene2d(5);
	m_ap2d->Init(CRenderer::GetDevice(),vtx,D3DXVECTOR2(width * 3 + 20,heght + 30),CScene2d::TYPE_MAX,TIME_TEXTURE);

	//�����̈ʒu����
	vtx.x += 10;
	vtx.y += 13;

	//�N���X����
	for(int	i = 0 ; i < TIME_DIGIT; i++)
	{
		m_apNumber[i] = new	CNumber;
		m_apNumber[i]->Init(pDevice,vtx,width,heght,NUMBER_TEXTURE);
		vtx.x += width;
	}
	//������
	m_nTime = TIME_COUNT;
	m_nSpan = 60;


		SetTime(0);

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
CTime	*CTime::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//�|�C���^�錾
	CTime	*pTime;

	//�N���X����
	pTime = new	CTime;

	//������
	pTime->Init(pDevice,vtx,width,heght);

	return	pTime;

}

//***************************************************************
//	�I��
//***************************************************************
void	CTime::Uninit()
{
	//�������
	for(int	i = 0; i < TIME_DIGIT; i++)
	{
		m_apNumber[i]->Uninit();
		delete	m_apNumber[i];
		m_apNumber[i] = NULL;
	}
}

//***************************************************************
//	�X�V
//***************************************************************
void	CTime::Update()
{
	if(m_nSpan < 0)
	{
		SetTime(1);
		m_nSpan = 60;
	}
	else
	{
		m_nSpan--;
	}
}


//***************************************************************
//	���Ԃ̃Z�b�e�B���O
//***************************************************************
void	CTime::SetTime(int	nTime)
{
	if(m_nTime <= 0)
	{
		m_nTime -= nTime;
		return;
	}

	//���Ԃ̌���
	m_nTime -= nTime;
	int	nTimeCount = 100;

	for(int	i = 0; i < TIME_DIGIT; i++,nTimeCount/=10)
	{
		int	nPoint = (m_nTime % (nTimeCount * 10)) / nTimeCount;
		m_apNumber[i]->SetNumber(nPoint);
	}

}

//***************************************************************
//	�`��
//����
//LPDIRECT3DDEVICE9 pDevice�F�f�o�C�X�|�C���^
//***************************************************************
void	CTime::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	m_ap2d->Draw(pDevice);

	for(int	i = 0 ; i < TIME_DIGIT; i++)
	{
		m_apNumber[i]->Draw(pDevice);
	}

}

//***************************************************************
//	���Ԑ؂�̔���
//***************************************************************
bool	CTime::TimeUp(void)
{
	bool	TimeUp = false;

	if(m_nTime < 0)
	{
		TimeUp = true;
		return	TimeUp;
	}
	else
	{
		return	TimeUp;
	}
}
