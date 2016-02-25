//***************************************************************
//
//	time.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/30
//
//***************************************************************

//***************************************************************
//	インクルード
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
//	静的変数
//***************************************************************
CNumber	*CTime::m_apNumber[3];
CScene2d	*CTime::m_ap2d = NULL;
int	CTime::m_nTime = 0;

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CTime::CTime(int	nPriority):CScene(nPriority)
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CTime::~CTime()
{

}

//***************************************************************
//	初期化
//***************************************************************
HRESULT	CTime::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//枠生成
	m_ap2d = new	CScene2d(5);
	m_ap2d->Init(CRenderer::GetDevice(),vtx,D3DXVECTOR2(width * 3 + 20,heght + 30),CScene2d::TYPE_MAX,TIME_TEXTURE);

	//数字の位置調整
	vtx.x += 10;
	vtx.y += 13;

	//クラス生成
	for(int	i = 0 ; i < TIME_DIGIT; i++)
	{
		m_apNumber[i] = new	CNumber;
		m_apNumber[i]->Init(pDevice,vtx,width,heght,NUMBER_TEXTURE);
		vtx.x += width;
	}
	//初期化
	m_nTime = TIME_COUNT;
	m_nSpan = 60;


		SetTime(0);

	return	S_OK;
}
//***************************************************************
//	スコア生成
//引数
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：指定座標
//戻り値
//CScene2d：元クラス
//***************************************************************
CTime	*CTime::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//ポインタ宣言
	CTime	*pTime;

	//クラス生成
	pTime = new	CTime;

	//初期化
	pTime->Init(pDevice,vtx,width,heght);

	return	pTime;

}

//***************************************************************
//	終了
//***************************************************************
void	CTime::Uninit()
{
	//解放処理
	for(int	i = 0; i < TIME_DIGIT; i++)
	{
		m_apNumber[i]->Uninit();
		delete	m_apNumber[i];
		m_apNumber[i] = NULL;
	}
}

//***************************************************************
//	更新
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
//	時間のセッティング
//***************************************************************
void	CTime::SetTime(int	nTime)
{
	if(m_nTime <= 0)
	{
		m_nTime -= nTime;
		return;
	}

	//時間の減少
	m_nTime -= nTime;
	int	nTimeCount = 100;

	for(int	i = 0; i < TIME_DIGIT; i++,nTimeCount/=10)
	{
		int	nPoint = (m_nTime % (nTimeCount * 10)) / nTimeCount;
		m_apNumber[i]->SetNumber(nPoint);
	}

}

//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
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
//	時間切れの判定
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
