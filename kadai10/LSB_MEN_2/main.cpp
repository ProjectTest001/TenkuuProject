//***************************************************************
//
//	main.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/19
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"renderer.h"
#include	"scene.h"
#include	"manager.h"
#include	"sound.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"number.h"
#include	"score.h"

#pragma	comment(lib,"d3d9.lib")
#pragma	comment(lib,"d3dx9.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")
#pragma	comment(lib,"winmm.lib")		//マルチメディアタイマー

//*****************************************************************************
//
//	ＤＸ演習
//	name:Masatugu Kamada
//
//*****************************************************************************

//*****************************************************************************
//	プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK myWindowProc(
							  HWND HWindow,
							  UINT uMsg,
							  WPARAM wParam,
							  LPARAM lParam);

//*****************************************************************************
//	メイン関数
//引数:
//HINSTANCE hInstance		ウィンドウのインスタンスハンドル
//HINSTANCE hPrevInstance	win１６の産物
//LPSTR lpCmdLine			コマンドライン
//int	nShowCmd			
//戻り値：
//	int		ＷｉｎＭａｉｎの終了コード
//*****************************************************************************
int	WINAPI	WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int	nShowCmd)
{
	//クラス変数
	CManager	*pManager;

	//ウィンドウ生成
	WNDCLASSEX	myWindowC=
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,	//	window	style
		myWindowProc,	//	call back
		0,
		0,
		hInstance,			//WinMain Instance
		NULL,	//	ICON
		LoadCursor(NULL,IDC_ARROW),	//cursor
		(HBRUSH)	(COLOR_WINDOW+1),	//window back
		NULL,	//MENU
		"俺window",	//window class name
		NULL		//	small ICON
	};
	RegisterClassEx(&myWindowC);
	//--
	HWND myWindow;

	RECT	rRect
		= {0,0,SCREEN_WIDTH,
		SCREEN_HEIGHT};

	AdjustWindowRect(&rRect,
		WS_OVERLAPPEDWINDOW,
		false);

	myWindow=CreateWindowEx(
				0,	//extension window style
				//WS_EX_RIGHTSCROLLBAR,
				"俺window",
				"ＬＳＢ＿ＭＥＮ",
				WS_OVERLAPPEDWINDOW,		//window style
				CW_USEDEFAULT,				// x
				CW_USEDEFAULT,				// y
				(rRect.right - rRect.left),						// width
				(rRect.bottom - rRect.top),						// height
				NULL,						//parent
				NULL,						//child or menu
				hInstance,
				NULL	//window data
				);

	//キー入力初期化

	//クラス生成
	pManager = new	CManager;

	InitializeSound(myWindow);
	//初期化
	pManager->Init(hInstance,myWindow,true);		//第３引数を真で通常、偽でフルスクリーン

			ShowWindow(myWindow,nShowCmd);
			UpdateWindow(myWindow);
			//----message loop
			DWORD	lastTime;	//最後に計測した時間
			DWORD	FPSCount = 0;	//FPS
			DWORD	FPSLastCount = timeGetTime();	//
			DWORD	now;		//現在時間

			timeBeginPeriod(1);	//分解能１ミリ秒
			lastTime = timeGetTime();
			now = 0;

			MSG message;

		//メインループ
		while(1)
		{
			if(PeekMessage(&message,
				NULL,0,0,PM_REMOVE))
			{
				//メッセージ
				if(message.message == WM_QUIT)
				{
					break;
				}
				else
				{
					TranslateMessage(&message);
					DispatchMessage(&message);

				}

			}
			else
			{
				//メッセージキュー空
				now = timeGetTime();	//現在時刻
				if(now - FPSLastCount > 1000)
				{
					CScore::SetScore(FPSCount);
					FPSLastCount = now;
					FPSCount = 0;
				}
				if( (now - lastTime) >= 
					(1000 / 60) )		//1/60秒以上
				{
					lastTime = now;
					FPSCount++;
						if(pManager)
						{
							//更新処理
							pManager->Update();
						}

						if(pManager)
						{
							//描画処理
							pManager->Draw();
						}
				}
			}

		}
/*
			while(GetMessage(&message,NULL,0,0)	!=0)
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
*/
			//---


			//クラス解放
			if(pManager)
			{
				pManager->Uninit();
				delete	pManager;
				pManager = NULL;
			}

			//全てのオブジェクトの破棄
			CScene::ReleaseAll();
			FinalizeSound();

			UnregisterClass("俺window",
				myWindowC.hInstance);
			return(int)message.wParam;
}

//---------------------
LRESULT CALLBACK myWindowProc(
							  HWND HWindow,
							  UINT uMsg,
							  WPARAM wParam,
							  LPARAM lParam)
{
	switch(uMsg)
	{
		case
		WM_CREATE:			//初期化
			break;
			case
		WM_DESTROY:

			PostQuitMessage(0);
			break;
			case
		WM_LBUTTONDOWN:

		break;

			case
		WM_KEYDOWN:
			switch(wParam)
			{
				case	VK_ESCAPE:

					//ウィンドウ終了
					DestroyWindow(HWindow);
				break;
			}

		break;
	case	WM_KEYUP:

		break;
	}
	return	DefWindowProc(HWindow,uMsg,wParam,lParam);
}

