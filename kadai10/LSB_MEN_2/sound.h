//------------------------- sound.h
#ifndef _SOUND_
#define _SOUND_
#include <dmusici.h>		// DirectMusic 関連のヘッダー

typedef enum
{
    BGM_00 = 0,
    BGM_01,
	BGM_02,
	BGM_03,
    SE_00,
    SE_01,
    SE_02,
    SE_03,
    SE_04,
    SE_05,
    SE_06,
    SE_07,
    SOUND_LABEL_MAX
} SOUND_LABEL;

//--------------------------
HRESULT InitializeSound(HWND hWindow);      // 初期化
void FinalizeSound();                       // 終了処理
HRESULT PlaySound(SOUND_LABEL label,DWORD flags);   // 音を鳴らす
HRESULT StopSound();                        // 全音消す


#endif

