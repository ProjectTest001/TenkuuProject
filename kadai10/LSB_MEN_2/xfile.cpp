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
	//棒人間
	D3DXLoadMeshFromX("model/lsb_men/lsb_waist.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_body.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_neck.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_head.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftarm.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftelbow.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_lefthand.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightarm.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightelbow.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_righthand.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftleg.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftknee.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_leftfoot.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightleg.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightknee.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;
	D3DXLoadMeshFromX("model/lsb_men/lsb_rightfoot.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;

	//***************************************************
	//	敵
	//***************************************************

	//ロボ
	D3DXLoadMeshFromX("model/敵.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;


	//***************************************************
	//	アイテム
	//***************************************************
	//コイン
	D3DXLoadMeshFromX("model/コイン.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;

	//星
	D3DXLoadMeshFromX("model/星.x",D3DXMESH_SYSTEMMEM, pDevice, NULL,&m_pD3DXMatBuff[i], NULL, &m_nNumMat[i], &m_pMesh[i]);	i++;

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

