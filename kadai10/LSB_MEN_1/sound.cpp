//-------------------------- sound.cpp
#include <d3dx9.h>
#include "sound.h"

//----------------------------------------- メモリ開放用マクロ
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
//------------------------------------------
typedef struct
{
    WCHAR *filename;	// ファイル名
    BOOL loop;			// 曲の繰り返しをするかフラグ
} SOUND_INFO;
//----------------------------------------- 音源情報
static SOUND_INFO sound[SOUND_LABEL_MAX] = 
{
	// ファイル名,  ループ再生
    {L"sound/sute-zi4.mid",true},
    {L"sound/sute-zi2.mid",true},
    {L"sound/game_over.mid",false},
    {L"sound/win.wav",false},
    {L"sound/撃破.wav",false},
    {L"sound/defend0.wav",false},
    {L"sound/defend1.wav",false},
    {L"sound/bomb0.wav",false},
    {L"sound/lockon0.wav",false},
    {L"sound/shot0.wav",false},
    {L"sound/shot1.wav",false},
    {L"sound/laser0.wav",false},
};


//-------------------------------------------
static IDirectMusicPerformance8* pPerformance = NULL;	// 演奏情報データ
static IDirectMusicLoader8* pLoader = NULL;				// ローダー(音ファイル読み込み用)

static IDirectMusicSegment8* pSegment[SOUND_LABEL_MAX];	// 個々の音データ
static IDirectMusicAudioPath8* pAudioPath = NULL;		// ファイル読み込み用ディレクトリ

static LONG volume;										// 音量

//---------------------------------------------
HRESULT InitializeSound(HWND hWindow)
{
    HRESULT result;
    // COM(共用オブジェクトモジュール)初期化
    result = CoInitialize(NULL);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Initialize COM Error.","Warning",MB_OK);
        return result;
    }
    
    // 演奏情報データ(performance)作成
    result = CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,
                                IID_IDirectMusicPerformance8,
                                (void **)&pPerformance);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Create Performance Error","Warning",MB_OK);
        return result;
    }
    
    // performance 初期化
    result = pPerformance->InitAudio(NULL,NULL,NULL,
                            DMUS_APATH_DYNAMIC_STEREO,64,
                            DMUS_AUDIOF_ALL,NULL);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Initialize Audio Error","Warning",MB_OK);
        return result;
    }
    
    // ローダー(音ファイル読み込み用)作成
    result = CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,
                                IID_IDirectMusicLoader8,
                                (void **)&pLoader);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Initialize Loader Error","Warning",MB_OK);
        return result;
        
    }
    // 現在のディレクトリ　current directory
    WCHAR wstrSearchPath[MAX_PATH];
    CHAR strPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,strPath);  // Unicodeの場合は、これだけでok
											// シフトJISコード(マルチバイトコード)の場合、下記の変換必要
    MultiByteToWideChar(CP_ACP,0,strPath,-1,wstrSearchPath,MAX_PATH); // Shift-JIS -> Unicode変換
    
    // 検索用ディレクトリにセット　set search directory
    result = pLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,wstrSearchPath,false);
    if(FAILED(result))
    {
        MessageBox(hWindow,"Set directory Error","Warning",MB_OK);
        return result;
    }
    // 音データの読み込み
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
        // 音色データ(band)の読み込み
        pSegment[i]->Download(pPerformance);
    }
    
    //　曲の繰り返し 設定
    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
        if(sound[i].loop)
        {
            result = pSegment[i]->SetLoopPoints(0,0);	// ループで戻すポイントを頭に設定
            if(FAILED(result))
            {
                MessageBox(hWindow,"Set Loop Error","Warning",MB_OK);
                return result;
            }
            
            result = pSegment[i]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);	// 無限繰り返しを指定
            if(FAILED(result))
            {
                MessageBox(hWindow,"Set Loop count Error","Warning",MB_OK);
                return result;
            }
            
        }
    }

    // 音の出力回路を、標準的なものに指定
    result = pPerformance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_STEREO,64,true,&pAudioPath);
        if(FAILED(result))
        {
            MessageBox(hWindow,"Create Audio path Error","Warning",MB_OK);
            return result;
        }

	// ボリューム指定
    volume = 0;
    pAudioPath->SetVolume(volume,0);
        
    return result;

}
//----------------------------------------------------------
void FinalizeSound()
{

    // 演奏情報データ(performance)停止指定
    if(pPerformance)
    {
        pPerformance->Stop(NULL,NULL,0,0);
        pPerformance->CloseDown();
    }
    
    // 出力回路指定　解放
    SAFE_RELEASE(pAudioPath);
	// ファイル読み込み用ローダー　解放
    SAFE_RELEASE(pLoader);

    // 演奏情報データ(performance)解放
    SAFE_RELEASE(pPerformance);
    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
		// 音色、曲データ　解放
        SAFE_RELEASE(pSegment[i]);
    }

    // COM(共用オブジェクトモジュール)終了処理
    CoUninitialize();
}

//-------------------------------------------------------------
//	曲、効果音　再生
HRESULT PlaySound(SOUND_LABEL label,DWORD flags)
{
    HRESULT result;
    if(label < 0 || label >= SOUND_LABEL_MAX)
    {
        return S_FALSE;
    }

    if(flags != DMUS_SEGF_SECONDARY						// アプリで用意しているバッファで
                && pPerformance->IsPlaying(pSegment[label],NULL) == S_OK)	//演奏中なら
     {
       // 音を止める
       result = pPerformance->StopEx(pSegment[label],0,0);
       if(FAILED(result))
       {
            return result;
       }
     }
  
	// 音を鳴らす   
     result = pPerformance->PlaySegmentEx(pSegment[label],NULL,NULL,flags,0,NULL,NULL,pAudioPath);
        if(FAILED(result))
        {
            return result;
        }
     
    return S_OK;
}
//-------------------------------------------------------------
//  演奏をすべて止める
HRESULT StopSound()
{
    HRESULT result;

    for(int i=0;i<SOUND_LABEL_MAX;i++)
    {
		// 音を止める
       result = pPerformance->StopEx(pSegment[i],0,0);
       if(FAILED(result))
       {
            return result;
       }
    }
    return result;
}

