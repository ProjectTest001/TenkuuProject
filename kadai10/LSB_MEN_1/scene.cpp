//***************************************************************
//
//	scene.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"renderer.h"

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	静的変数
//***************************************************************
CScene	*CScene::m_pTop = NULL;
CScene	*CScene::m_pCur = NULL;
CScene	*CScene::m_apTop[MAX_LIST] = {NULL};
CScene	*CScene::m_apCur[MAX_LIST] = {NULL};

//***************************************************************
//	コンストラクタ
//	引数
//	int	nPriority：階層番号
//	戻り値
//	なし
//***************************************************************
CScene::CScene(int	nPriority)
{
	//プライオリティの設定
	m_nPriority = nPriority;

	//OBJタイプの設定
	SetObjectType(CScene::TYPE_MAX);

	//クラス生成
	//既に一つ以上生成している場合
		if(m_apTop[m_nPriority] != NULL)
		{
			m_pPrev = m_apCur[m_nPriority];			//前に現在の記録を保存
			m_pNext = NULL;							//次の生成の為にNULLにする
			m_apCur[m_nPriority]->m_pNext = this;		//現在の中の次に生成
			m_apCur[m_nPriority] = this;				//現在に生成
		}
		//一つも生成していない場合
		else
		{
			m_apTop[m_nPriority] = this;			//先頭に生成
			m_apCur[m_nPriority] = this;			//最初なので現在に生成
			m_pNext = NULL;						//次の生成の為にNULLにする
			m_pPrev = NULL;						//前をNULLにする

		}

		//死亡フラグ初期化
		m_bDelete = false;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CScene::~CScene()
{

}
//***************************************************************
//	ステートの終了処理
//***************************************************************
void	CScene::UninitAll(void)
{
	//ポインタ宣言
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST - 1 ; nCount++)
	{
		pScene = m_apTop[nCount];
		//全てのリストを解放するまで繰り返す
		while(pScene)
		{
			//次のオブジェクトへのポインタを保存
			CScene	*pSceneNext = pScene->m_pNext;

			//更新
			pScene->Release();

			//次のオブジェクトを代入
			pScene = pSceneNext;
		}
	}

}

//***************************************************************
//	オブジェクトを破棄する
//***************************************************************
void	CScene::Release(void)
{
	//
	m_bDelete = true;
}

//***************************************************************
//	全てのオブジェクトを破棄する
//***************************************************************
void	CScene::ReleaseAll(void)
{
	//ポインタ宣言
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		//全てのリストを解放するまで繰り返す
		while(pScene)
		{
			//次のオブジェクトへのポインタを保存
			CScene	*pSceneNext = pScene->m_pNext;

			//更新
			pScene->Release();

			//次のオブジェクトを代入
			pScene = pSceneNext;
		}
	}

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//次のオブジェクトへのポインタを保存
			CScene	*pSceneNext = pScene->m_pNext;

			//死亡フラグが成立している場合
			if(pScene->m_bDelete)
			{
				//リストの先頭の場合
				if(pScene == m_apTop[pScene->m_nPriority])
				{
					//先頭にリリース対象の次のアドレスを入れる
					m_apTop[pScene->m_nPriority] = pScene->m_pNext;

					//リストの残りが複数の時
					if(pScene->m_pNext != NULL)
					{
						pScene->m_pNext->m_pPrev = NULL;
					}
				}
				//リストの最後の場合
				else	if(pScene == m_apCur[pScene->m_nPriority])
				{
					m_apCur[pScene->m_nPriority] = pScene->m_pPrev;
					pScene->m_pPrev->m_pNext = NULL;
				}
				//それ以外
				else
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				//解放処理
				pScene->Uninit();
				delete	pScene;
			}

			//次のオブジェクトを代入
			pScene = pSceneNext;
		}
	}

}

//***************************************************************
//	全更新
//***************************************************************
void	CScene::UpdateAll(void)
{
	//ポインタ宣言
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//次のオブジェクトへのポインタを保存
			CScene	*pSceneNext = pScene->m_pNext;

			//更新
			pScene->Update();

			//次のオブジェクトを代入
			pScene = pSceneNext;
		}
	}

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//次のオブジェクトへのポインタを保存
			CScene	*pSceneNext = pScene->m_pNext;

			//死亡フラグが成立している場合
			if(pScene->m_bDelete)
			{
				//リストの先頭の場合
				if(pScene == m_apTop[pScene->m_nPriority])
				{
					//先頭にリリース対象の次のアドレスを入れる
					m_apTop[pScene->m_nPriority] = pScene->m_pNext;

					//リストの残りが複数の時
					if(pScene->m_pNext != NULL)
					{
						pScene->m_pNext->m_pPrev = NULL;
					}
				}
				//リストの最後の場合
				else	if(pScene == m_apCur[pScene->m_nPriority])
				{
					m_apCur[pScene->m_nPriority] = pScene->m_pPrev;
					pScene->m_pPrev->m_pNext = NULL;
				}
				//それ以外
				else
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				//解放処理
				pScene->Uninit();
				delete	pScene;
			}

			//次のオブジェクトを代入
			pScene = pSceneNext;
		}
	}
}

//***************************************************************
//	全描画
//***************************************************************
void	CScene::DrawAll(LPDIRECT3DDEVICE9 pDevice)
{
	//ポインタ宣言
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//次のオブジェクトへのポインタを保存
			CScene	*pSceneNext = pScene->m_pNext;

			//更新
			pScene->Draw(pDevice);

			//次のオブジェクトを代入
			pScene = pSceneNext;

		}
	}
}