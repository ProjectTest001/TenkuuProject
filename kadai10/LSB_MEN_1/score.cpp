//***************************************************************
//
//	score.cpp
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
#include	"scene3d.h"
#include	"scene2d.h"
#include	"scene_x.h"
#include	"player.h"
#include	"number.h"
#include	"score.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
CNumber	*CScore::m_apNumber[8];
CScene2d	*CScore::m_ap2d = NULL;
int	CScore::m_nScore = 0;

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CScore::CScore(int	nPriority):CScene(nPriority)
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CScore::~CScore()
{

}

//***************************************************************
//	初期化
//***************************************************************
HRESULT	CScore::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//枠生成
	m_ap2d = new	CScene2d(5);
	m_ap2d->Init(CRenderer::GetDevice(),vtx,D3DXVECTOR2(width * 8 + 20,heght + 30),CScene2d::TYPE_MAX,SCORE_TEXTURE);

	//数字の位置調整
	vtx.x += 10;
	vtx.y += 20;

	//クラス生成
	for(int	i = 0 ; i < 8; i++)
	{
		m_apNumber[i] = new	CNumber;
		m_apNumber[i]->Init(pDevice,vtx,width,heght,NUMBER_TEXTURE);
		vtx.x += width;
	}
	//初期化
	m_nScore = 0;

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
CScore	*CScore::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,float	width,float	heght)
{
	//ポインタ宣言
	CScore	*pScore;

	//クラス生成
	pScore = new	CScore;

	//初期化
	pScore->Init(pDevice,vtx,width,heght);

	return	pScore;

}

//***************************************************************
//	終了
//***************************************************************
void	CScore::Uninit()
{
	//解放処理
	for(int	i = 0 ; i < 8; i++)
	{
		m_apNumber[i]->Uninit();
		delete	m_apNumber[i];
		m_apNumber[i] = NULL;
	}

}

//***************************************************************
//	更新
//***************************************************************
void	CScore::Update()
{

}


//***************************************************************
//	スコアのセッティング
//***************************************************************
void	CScore::SetScore(int	nScore)
{
	//スコアの増加
	m_nScore += nScore;
	int	nScoreCount = 10000000;

	for(int	i = 0; i < 8; i++,nScoreCount/=10)
	{
		int	nPoint = (m_nScore % (nScoreCount * 10)) / nScoreCount;
		m_apNumber[i]->SetNumber(nPoint);
	}
}

//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//***************************************************************
void	CScore::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	m_ap2d->Draw(pDevice);

	for(int	i = 0 ; i < 8; i++)
	{
		m_apNumber[i]->Draw(pDevice);
	}
}
