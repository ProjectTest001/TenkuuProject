//***************************************************************
//
//	debugproc.cpp
//	name:Masatugu Kamada
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<stdio.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene3d.h"
#include	"scene_x.h"
#include	"debugproc.h"

//***************************************************************
//	静的変数
//***************************************************************
char	CDebugProc::m_aStr[1028];
LPD3DXFONT	CDebugProc::m_pD3DXFont = NULL;

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CDebugProc::CDebugProc()
{
	//m_pD3DXFont = NULL;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CDebugProc::~CDebugProc()
{

}

//***************************************************************
//	初期化
//***************************************************************
HRESULT	CDebugProc::Init(LPDIRECT3DDEVICE9	pDevice)
{

if(FAILED(D3DXCreateFont(pDevice,
        14,                     //文字高さ
        7,                      //文字幅
        FW_BOLD,                //フォントスタイル
        NULL,                   //ミップマップモデルの数
        FALSE,                  //斜体にするかどうか
        SHIFTJIS_CHARSET,       //文字セット
        OUT_DEFAULT_PRECIS,
        PROOF_QUALITY,
        FIXED_PITCH | FF_MODERN,
        "tahoma",               //フォントの種類
        &m_pD3DXFont)))
    {
        return E_FAIL;
    }

	return	S_OK;

}


//***************************************************************
//	終了
//***************************************************************
void	CDebugProc::Uninit()
{

}


//***************************************************************
//	描画
//***************************************************************
void	CDebugProc::Draw()
{

 RECT rect = {10, 10, 0, 0}; //表示領域

    //文字列サイズを計算
    m_pD3DXFont->DrawText(
        NULL,
        m_aStr,
        -1,             //表示サイズ(-1で全部)
        &rect,          //表示範囲
        DT_CALCRECT,    //表示範囲に調整
        NULL);

    //そのサイズでレンダリング
    m_pD3DXFont->DrawText(
        NULL,
        m_aStr,
        -1,                     //表示サイズ(-1で全部)
        &rect,                  //表示範囲
        DT_LEFT | DT_BOTTOM,    //左詰めで両端揃え
        0xff00ff00);            //色

}

//***************************************************************
//	デバック情報書き込み
//***************************************************************
void	CDebugProc::Print(char *fmt, ...)
{

}


