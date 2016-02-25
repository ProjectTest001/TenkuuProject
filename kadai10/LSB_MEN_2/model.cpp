//***************************************************************
//
//	model.cpp
//	name:Masatugu Kamada
//	update：2012/11/05
//
//***************************************************************

//***************************************************************
//	インクルード
//***************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"sound.h"
#include	<dinput.h>
#include	"renderer.h"
#include	"scene.h"
#include	"scene2d.h"
//#include	"scene3d.h"
#include	"scene_x.h"
#include	"number.h"
#include	"score.h"
#include	"player.h"
#include	"manager.h"
#include	"game.h"
#include	"model.h"
#include	"texture.h"
#include	"xfile.h"

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//***************************************************************
CModel::CModel()
{
	m_pParent = NULL;
}

//***************************************************************
//	デストラクタ
//***************************************************************
CModel::~CModel()
{

}


//***************************************************************
//	初期化
//	引数
//	LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//	int	nType:親番号
//	D3DXVECTOR3	pos:座標
//	D3DXVECTOR3	rot:角度
//	int	TexNo:画像番号
//	戻り値
//	HRESULT:終了コード
//***************************************************************
HRESULT	CModel::Init(LPDIRECT3DDEVICE9	pDevice,int	nType,D3DXVECTOR3	pos,D3DXVECTOR3	rot,int	TexNo)
{
	m_nmodel = nType;


	//ステータス初期化
	m_Vertex_3d.vtx = pos;			//座標
	m_Vertex_3d.Rot_vtx = rot;		//角度
	m_nTex = TexNo;					//画像番号

	return	S_OK;
}

//***************************************************************
//	生成
//	引数
//	LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//	int	nType:親番号
//	D3DXVECTOR3	pos:座標
//	D3DXVECTOR3	rot:角度
//	int	TexNo:画像番号
//	戻り値
//	*CModel:モデルクラスポインタ
//***************************************************************
CModel	*CModel::Create(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int	TexNo)
{
	CModel	*pModel;

	pModel = new	CModel;
	pModel->Init(pDevice,nType,pos,rot,TexNo);

	return	pModel;
}

//***************************************************************
//	終了
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
void	CModel::Uninit(void)
{

}

//***************************************************************
//	更新
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
void	CModel::Update(void)
{

}


//*****************************************************************************
//	描画
//	引数：
//	LPDIRECT3DDEVICE9 pDevice：デバイスポインタ
//	戻り値：
//	なし
//*****************************************************************************
void	CModel::Draw(LPDIRECT3DDEVICE9	pDevice)
{
	//パーツの親マトリックス宣言
	D3DXMATRIX	mtxParent;

	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mRotate;		//左から座標、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//Ｘファイル情報取得変数
	LPD3DXMESH	pMesh = CXfile::GetMesh(m_nmodel);
	LPD3DXBUFFER	pBuffer = CXfile::GetBuffer(m_nmodel);
	DWORD	pWord = CXfile::GetWord(m_nmodel);

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//親モデルが存在する場合
	if(m_pParent)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	//存在しない場合
	else
	{
		pDevice->GetTransform(D3DTS_WORLD,&mtxParent);
	}

			//角度設定
			D3DXMatrixRotationYawPitchRoll(&mRotate, D3DX_PI * m_Vertex_3d.Rot_vtx.y, D3DX_PI * m_Vertex_3d.Rot_vtx.x, D3DX_PI * m_Vertex_3d.Rot_vtx.z);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//座標設定
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x, m_Vertex_3d.vtx.y, m_Vertex_3d.vtx.z);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

			//親マトリックスと自分のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxParent);

			//セッティング
			pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

			//メッシュ読み込み
			LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)pBuffer->GetBufferPointer();

			//描画開始
			for(unsigned int i = 0 ; i < pWord ; i++)
			{
				//マテリアルセット
				pDevice->SetMaterial(&pMaterial[i].MatD3D);

				if(Texture)
				{
					//テクスチャ貼り付け
					pDevice->SetTexture(0,
						Texture);
				}

				//描画
				pMesh->DrawSubset(i);
			}
			
		//マテリアルを元に戻す
		pMaterial->MatD3D.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
		pMaterial->MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pMaterial->MatD3D.Emissive = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pDevice->SetMaterial(&pMaterial->MatD3D);

}
