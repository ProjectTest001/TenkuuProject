//******************************************************
//
//	texture.cpp
//	name:Masatugu Kamada
//	create:2012/09/28
//	update:2012/09/28
//
//******************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<math.h>
#include	"main.h"
#include	"renderer.h"
#include	"manager.h"
#include	"xfile.h"

//***************************************************************
//	静的変数
//***************************************************************
LPD3DXMESH	CXfile::m_pMesh[MAX_XFILE] = {NULL};
LPD3DXBUFFER	CXfile::m_pD3DXMatBuff[MAX_XFILE] = {NULL};
DWORD	CXfile::m_nNumMat[MAX_XFILE] = {NULL};

//***************************************************************
//	メイン関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CXfile::CXfile()
{

}

//***************************************************************
//	デストラクタ
//***************************************************************
CXfile::~CXfile()
{

}

//***************************************************************
//	初期化
//	引数
//	LPDIRECT3DDEVICE9	pDevice:デバイスポインタ
//	戻り値
//	なし
//***************************************************************
HRESULT	CXfile::Init(LPDIRECT3DDEVICE9	pDevice)
{
	int	i = 0;
	//Ｘファイル読み込み
	//人間
	D3DXLoadMeshFromX("model/MODEL/body.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/head.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/arm_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/hand_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/arm_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/hand_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/leg_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/foot_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/leg_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/MODEL/foot_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;

	//棒人間
	D3DXLoadMeshFromX("model/lsb_men/lsb_waist.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_body.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_neck.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_head.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightarm.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightelboe.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_righthand.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftarm.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftelbow.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_lefthand.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightleg.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightknee.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightfoot.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftleg.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftknee.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftfoot.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;

	//アンパンマン
	D3DXLoadMeshFromX("model/AnMODEL/an_body.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_head.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_arm_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_hand_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_arm_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_hand_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_leg_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_foot_r.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_leg_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/AnMODEL/an_foot_l.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;

	return	S_OK;
}

//***************************************************************
//	終了
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
void	CXfile::UnInit()
{
	for(int	i = 0; i < MAX_XFILE; i++)
	{
	//メッシュ解放
		if(m_pMesh[i] != NULL)
		{
			m_pMesh[i]->Release();
			m_pMesh[i] = NULL;
		}

		//バッファ解放
		if(m_pD3DXMatBuff[i] != NULL)
		{
			m_pD3DXMatBuff[i]->Release();
			m_pD3DXMatBuff[i] = NULL;
		}

	}

}

