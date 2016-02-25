//***************************************************************
//
//	light.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/26
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
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
//	�ÓI�ϐ�
//***************************************************************

//***************************************************************
//	���C���֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//***************************************************************
CLight::CLight()
{

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CLight::~CLight()
{

}

//***************************************************************
//	������
//***************************************************************
HRESULT	CLight::Init(LPDIRECT3DDEVICE9	pDevice)
{

	//���C�g�̐ݒ�
		//���z��
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		m_aLight[0].Diffuse.r = 1.0f;
		m_aLight[0].Diffuse.g = 1.0f;
		m_aLight[0].Diffuse.b = 1.0f;
		m_aLight[0].Diffuse.a = 1.0f;
		m_aLight[0].Ambient.r = 1.0f;
		m_aLight[0].Ambient.g = 1.0f;
		m_aLight[0].Ambient.b = 1.0f;
		m_aLight[0].Ambient.a = 1.0f;

		//���ˌ�
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		m_aLight[1].Diffuse.r = 0.15f;
		m_aLight[1].Diffuse.g = 0.15f;
		m_aLight[1].Diffuse.b = 0.15f;
		m_aLight[1].Diffuse.a = 0.15f;
		m_aLight[1].Ambient.r = 0.15f;
		m_aLight[1].Ambient.g = 0.15f;
		m_aLight[1].Ambient.b = 0.15f;
		m_aLight[1].Ambient.a = 0.15f;

		//����
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		m_aLight[2].Diffuse.r = 0.1f;
		m_aLight[2].Diffuse.g = 0.1f;
		m_aLight[2].Diffuse.b = 0.1f;
		m_aLight[2].Diffuse.a = 0.1f;
		m_aLight[2].Ambient.r = 0.1f;
		m_aLight[2].Ambient.g = 0.1f;
		m_aLight[2].Ambient.b = 0.1f;
		m_aLight[2].Ambient.a = 0.1f;

	//�ϐ��錾
	D3DXVECTOR3	vecDir;

	//���z��
	vecDir = D3DXVECTOR3(1.0f,-1.0f,0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction,&vecDir);

	//���ˌ�
	vecDir = D3DXVECTOR3(-1.0f,1.0f,0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction,&vecDir);

	//����
	vecDir = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction,&vecDir);

	//���C�g���Z�b�g
	pDevice->SetLight(0,&m_aLight[0]);
	pDevice->SetLight(1,&m_aLight[1]);
	pDevice->SetLight(2,&m_aLight[2]);

	//���C�g��L����
	pDevice->LightEnable(0,TRUE);
	pDevice->LightEnable(1,TRUE);
	pDevice->LightEnable(2,TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	return	S_OK;
}

//***************************************************************
//	�I��
//***************************************************************
void	CLight::Uninit()
{
	//ZeroMemory(&m_aLight[0],sizeof(D3DLIGHT9));

}
