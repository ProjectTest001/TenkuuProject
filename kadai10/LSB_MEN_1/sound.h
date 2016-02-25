//------------------------- sound.h
#ifndef _SOUND_
#define _SOUND_
#include <dmusici.h>		// DirectMusic �֘A�̃w�b�_�[

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
HRESULT InitializeSound(HWND hWindow);      // ������
void FinalizeSound();                       // �I������
HRESULT PlaySound(SOUND_LABEL label,DWORD flags);   // ����炷
HRESULT StopSound();                        // �S������


#endif

