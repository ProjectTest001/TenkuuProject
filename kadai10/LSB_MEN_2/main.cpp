//***************************************************************
//
//	main.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/19
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
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
#pragma	comment(lib,"winmm.lib")		//�}���`���f�B�A�^�C�}�[

//*****************************************************************************
//
//	�c�w���K
//	name:Masatugu Kamada
//
//*****************************************************************************

//*****************************************************************************
//	�v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK myWindowProc(
							  HWND HWindow,
							  UINT uMsg,
							  WPARAM wParam,
							  LPARAM lParam);

//*****************************************************************************
//	���C���֐�
//����:
//HINSTANCE hInstance		�E�B���h�E�̃C���X�^���X�n���h��
//HINSTANCE hPrevInstance	win�P�U�̎Y��
//LPSTR lpCmdLine			�R�}���h���C��
//int	nShowCmd			
//�߂�l�F
//	int		�v�����l�������̏I���R�[�h
//*****************************************************************************
int	WINAPI	WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int	nShowCmd)
{
	//�N���X�ϐ�
	CManager	*pManager;

	//�E�B���h�E����
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
		"��window",	//window class name
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
				"��window",
				"�k�r�a�Q�l�d�m",
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

	//�L�[���͏�����

	//�N���X����
	pManager = new	CManager;

	InitializeSound(myWindow);
	//������
	pManager->Init(hInstance,myWindow,true);		//��R������^�Œʏ�A�U�Ńt���X�N���[��

			ShowWindow(myWindow,nShowCmd);
			UpdateWindow(myWindow);
			//----message loop
			DWORD	lastTime;	//�Ō�Ɍv����������
			DWORD	FPSCount = 0;	//FPS
			DWORD	FPSLastCount = timeGetTime();	//
			DWORD	now;		//���ݎ���

			timeBeginPeriod(1);	//����\�P�~���b
			lastTime = timeGetTime();
			now = 0;

			MSG message;

		//���C�����[�v
		while(1)
		{
			if(PeekMessage(&message,
				NULL,0,0,PM_REMOVE))
			{
				//���b�Z�[�W
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
				//���b�Z�[�W�L���[��
				now = timeGetTime();	//���ݎ���
				if(now - FPSLastCount > 1000)
				{
					CScore::SetScore(FPSCount);
					FPSLastCount = now;
					FPSCount = 0;
				}
				if( (now - lastTime) >= 
					(1000 / 60) )		//1/60�b�ȏ�
				{
					lastTime = now;
					FPSCount++;
						if(pManager)
						{
							//�X�V����
							pManager->Update();
						}

						if(pManager)
						{
							//�`�揈��
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


			//�N���X���
			if(pManager)
			{
				pManager->Uninit();
				delete	pManager;
				pManager = NULL;
			}

			//�S�ẴI�u�W�F�N�g�̔j��
			CScene::ReleaseAll();
			FinalizeSound();

			UnregisterClass("��window",
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
		WM_CREATE:			//������
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

					//�E�B���h�E�I��
					DestroyWindow(HWindow);
				break;
			}

		break;
	case	WM_KEYUP:

		break;
	}
	return	DefWindowProc(HWindow,uMsg,wParam,lParam);
}

