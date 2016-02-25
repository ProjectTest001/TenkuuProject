//***************************************************************
//
//	light.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/26
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<math.h>
#include	"main.h"
#include	<dinput.h>
#include	"light.h"
#include	"renderer.h"
#include	"manager.h"
#include	"input.h"
#include	"inputkeyboard.h"

//***************************************************************
//	静的変数
//***************************************************************

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CLight::CLight()
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CLight::~CLight()
{

}

//***************************************************************
//	初期化
//***************************************************************
HRESULT	CLight::Init(LPDIRECT3DDEVICE9	pDevice)
{

	//ライトの設定
		//太陽光
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		m_aLight[0].Diffuse.r = 1.0f;
		m_aLight[0].Diffuse.g = 1.0f;
		m_aLight[0].Diffuse.b = 1.0f;
		m_aLight[0].Diffuse.a = 1.0f;
		m_aLight[0].Ambient.r = 1.0f;
		m_aLight[0].Ambient.g = 1.0f;
		m_aLight[0].Ambient.b = 1.0f;
		m_aLight[0].Ambient.a = 1.0f;

		//反射光
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		m_aLight[1].Diffuse.r = 0.15f;
		m_aLight[1].Diffuse.g = 0.15f;
		m_aLight[1].Diffuse.b = 0.15f;
		m_aLight[1].Diffuse.a = 0.15f;
		m_aLight[1].Ambient.r = 0.15f;
		m_aLight[1].Ambient.g = 0.15f;
		m_aLight[1].Ambient.b = 0.15f;
		m_aLight[1].Ambient.a = 0.15f;

		//環境光
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		m_aLight[2].Diffuse.r = 0.1f;
		m_aLight[2].Diffuse.g = 0.1f;
		m_aLight[2].Diffuse.b = 0.1f;
		m_aLight[2].Diffuse.a = 0.1f;
		m_aLight[2].Ambient.r = 0.1f;
		m_aLight[2].Ambient.g = 0.1f;
		m_aLight[2].Ambient.b = 0.1f;
		m_aLight[2].Ambient.a = 0.1f;

	//変数宣言
	D3DXVECTOR3	vecDir;

	//太陽光
	vecDir = D3DXVECTOR3(1.0f,-1.0f,0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction,&vecDir);

	//反射光
	vecDir = D3DXVECTOR3(-1.0f,1.0f,0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction,&vecDir);

	//環境光
	vecDir = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction,&vecDir);

	//ライトをセット
	pDevice->SetLight(0,&m_aLight[0]);
	pDevice->SetLight(1,&m_aLight[1]);
	pDevice->SetLight(2,&m_aLight[2]);

	//ライトを有効化
	pDevice->LightEnable(0,TRUE);
	pDevice->LightEnable(1,TRUE);
	pDevice->LightEnable(2,TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	return	S_OK;
}

//***************************************************************
//	終了
//***************************************************************
void	CLight::Uninit()
{
	//ZeroMemory(&m_aLight[0],sizeof(D3DLIGHT9));

}
