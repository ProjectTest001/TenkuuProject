//-------------------------- sound.cpp
#include <d3dx9.h>
#include "sound.h"

//----------------------------------------- �������J���p�}�N��
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
//------------------------------------------
typedef struct
{
    WCHAR *filename;	// �t�@�C����
    BOOL loop;			// �Ȃ̌J��Ԃ������邩�t���O
} SOUND_INFO;
//----------------------------------------- �������
static SOUND_INFO sound[SOUND_LABEL_MAX] = 
{
	// �t�@�C����,  ���[�v�Đ�
    {L"sound/sute-zi4.mid",true},
    {L"sound/sute-zi2.mid",true},
    {L"sound/game_over.mid",false},
    {L"sound/win.wav",false},
    {L"sound/���j.wav",false},
    {L"sound/defend0.wav",false},
    {L"sound/defend1.wav",false},
    {L"sound/bomb0.wav",false},
    {L"sound/lockon0.wav",false},
    {L"sound/shot0.wav",false},
    {L"sound/shot1.wav",false},
    {L"sound/laser0.wav",false},
};


//-------------------------------------------
static IDirectMusicPerformance8* pPerformance = NULL;	// ���t���f�[�^
static IDirectMusicLoader8* pLoader = NULL;				// ���[�_�[(���t�@�C���ǂݍ��ݗp)

static IDirectMusicSegment8* pSegment[SOUND_LABEL_MAX];	// �X�̉��f�[�^
static IDirectMusicAudioPath8* pAudioPath = NULL;		// �t�@�C���ǂݍ��ݗp�f�B���N�g��

static LONG volume;										// ����

//---------------------------------------------
HRESULT InitializeSound(HWND hWindow)
{
    HRESULT result;
    // COM(���p�I�u�W�F�N�g���W���[��)������
    result = CoInitialize(NULL);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Initialize COM Error.","Warning",MB_OK);
        return result;
    }
    
    // ���t���f�[�^(performance)�쐬
    result = CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,
                                IID_IDirectMusicPerformance8,
                                (void **)&pPerformance);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Create Performance Error","Warning",MB_OK);
        return result;
    }
    
    // performance ������
    result = pPerformance->InitAudio(NULL,NULL,NULL,
                            DMUS_APATH_DYNAMIC_STEREO,64,
                            DMUS_AUDIOF_ALL,NULL);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Initialize Audio Error","Warning",MB_OK);
        return result;
    }
    
    // ���[�_�[(���t�@�C���ǂݍ��ݗp)�쐬
    result = CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,
                                IID_IDirectMusicLoader8,
                                (void **)&pLoader);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Initialize Loader Error","Warning",MB_OK);
        return result;
        
    }
    // ���݂̃f�B���N�g���@current directory
    WCHAR wstrSearchPath[MAX_PATH];
    CHAR strPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,strPath);  // Unicode�̏ꍇ�́A���ꂾ����ok
											// �V�t�gJIS�R�[�h(�}���`�o�C�g�R�[�h)�̏ꍇ�A���L�̕ϊ��K�v
    MultiByteToWideChar(CP_ACP,0,strPath,-1,wstrSearchPath,MAX_PATH); // Shift-JIS -> Unicode�ϊ�
    
    // �����p�f�B���N�g���ɃZ�b�g�@set search directory
    result = pLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,wstrSearchPath,false);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Set directory Error","Warning",MB_OK);
        return result;
    }
    // ���f�[�^�̓ǂݍ���
    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
        result = pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,
                                            IID_IDirectMusicSegment8,
                                            sound[i].filename,
                                            (LPVOID *)&pSegment[i]);
        if(FAILED(result))
        {
            MessageBox(hWindow,"Load Sound Segment Error","Warning",MB_OK);
            return result;
        }
        // ���F�f�[�^(band)�̓ǂݍ���
        pSegment[i]->Download(pPerformance);
    }
    
    //�@�Ȃ̌J��Ԃ� �ݒ�
    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
        if(sound[i].loop)
        {
            result = pSegment[i]->SetLoopPoints(0,0);	// ���[�v�Ŗ߂��|�C���g�𓪂ɐݒ�
            if(FAILED(result))
            {
                MessageBox(hWindow,"Set Loop Error","Warning",MB_OK);
                return result;
            }
            
            result = pSegment[i]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);	// �����J��Ԃ����w��
            if(FAILED(result))
            {
                MessageBox(hWindow,"Set Loop count Error","Warning",MB_OK);
                return result;
            }
            
        }
    }

    // ���̏o�͉�H���A�W���I�Ȃ��̂Ɏw��
    result = pPerformance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_STEREO,64,true,&pAudioPath);
        if(FAILED(result))
        {
            MessageBox(hWindow,"Create Audio path Error","Warning",MB_OK);
            return result;
        }

	// �{�����[���w��
    volume = 0;
    pAudioPath->SetVolume(volume,0);
        
    return result;

}
//----------------------------------------------------------
void FinalizeSound()
{

    // ���t���f�[�^(performance)��~�w��
    if(pPerformance)
    {
        pPerformance->Stop(NULL,NULL,0,0);
        pPerformance->CloseDown();
    }
    
    // �o�͉�H�w��@���
    SAFE_RELEASE(pAudioPath);
	// �t�@�C���ǂݍ��ݗp���[�_�[�@���
    SAFE_RELEASE(pLoader);

    // ���t���f�[�^(performance)���
    SAFE_RELEASE(pPerformance);
    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
		// ���F�A�ȃf�[�^�@���
        SAFE_RELEASE(pSegment[i]);
    }

    // COM(���p�I�u�W�F�N�g���W���[��)�I������
    CoUninitialize();
}

//-------------------------------------------------------------
//	�ȁA���ʉ��@�Đ�
HRESULT PlaySound(SOUND_LABEL label,DWORD flags)
{
    HRESULT result;
    if(label < 0 || label >= SOUND_LABEL_MAX)
    {
        return S_FALSE;
    }

    if(flags != DMUS_SEGF_SECONDARY						// �A�v���ŗp�ӂ��Ă���o�b�t�@��
                && pPerformance->IsPlaying(pSegment[label],NULL) == S_OK)	//���t���Ȃ�
     {
       // �����~�߂�
       result = pPerformance->StopEx(pSegment[label],0,0);
       if(FAILED(result))
       {
            return result;
       }
     }
  
	// ����炷   
     result = pPerformance->PlaySegmentEx(pSegment[label],NULL,NULL,flags,0,NULL,NULL,pAudioPath);
        if(FAILED(result))
        {
            return result;
        }
     
    return S_OK;
}
//-------------------------------------------------------------
//  ���t�����ׂĎ~�߂�
HRESULT StopSound()
{
    HRESULT result;

    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
		// �����~�߂�
       result = pPerformance->StopEx(pSegment[i],0,0);
       if(FAILED(result))
       {
            return result;
       }
    }
    return result;
}

