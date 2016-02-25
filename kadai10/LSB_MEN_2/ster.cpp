//***************************************************************
//
//	scene3d.cpp
//	name:Masatugu Kamada
//	更新日：2012/05/23
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
#include	"scene3d.h"
#include	"scene_x.h"
#include	"item.h"
#include	"input.h"
#include	"inputkeyboard.h"
#include	"manager.h"
#include	"player.h"
#include	"ster.h"
#include	"number.h"
#include	"score.h"
#include	"time.h"
#include	"texture.h"
#include	"game.h"
#include	"xfile.h"

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//	引数
//	int	nPriority：階層番号
//	イニシャライザ
//	CScene(nPriority)：階層番号受け渡し
//	戻り値
//	なし
//***************************************************************
CSter::CSter()
{
	//初期化
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CSter::~CSter()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//戻り値：
//HRESULT	終了コード
//***************************************************************
HRESULT	CSter::Init(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,int	TexNo)
{
	//初期化
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.diffuse = D3DXCOLOR(1.0,0.0f,0.0f,1.0f);
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	get = false;
	vec = 3.0f;
	m_nTex = YEROWW_TEXTURE;

	return	S_OK;
}

//***************************************************************
//	生成関数
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//D3DXVECTOR3 vtx：指定座標
//戻り値
//CScene_x	元クラス
//***************************************************************
CScene_x	*CSter::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,int	TexNo)
{
	//ポインタ宣言
	CSter	*pSter;

	//クラス生成
	pSter = new	CSter;

	//初期化
	pSter->Init(pDevice, vtx,TexNo);

	return	pSter;

}
//***************************************************************
//	終了
//***************************************************************
void	CSter::Uninit()
{
	//解放処理
	//メッシュ解放
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//バッファ解放
	if(m_pD3DXMatBuff != NULL)
	{
		m_pD3DXMatBuff->Release();
		m_pD3DXMatBuff = NULL;
	}

	CScene::Release();
}

//***************************************************************
//	更新
//***************************************************************
void	CSter::Update()
{
	//キー変数と取得
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//入力処理へのポインタ取得

	//回転
	m_Vertex_3d.Rot_vtx.y += 0.04f + m_Vertex_3d.Speed_vtx.y * 2;

	//星を取得した場合
	if(CItem::HitItem(m_Vertex_3d.vtx,CGame::GetPlayer().vtx) && !CTime::TimeUp() && m_Vertex_3d.Speed_vtx.y == 0.0f)
	{
		m_Vertex_3d.Speed_vtx.y = 0.08f;
		get = true;
	}

	//移動
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;

	if(get)
	{
		vec -= m_Vertex_3d.Speed_vtx.y;
	}

	//一定以上星が上昇したら消滅し、ゲームクリア
	if(vec < 0.0f)
	{
		CManager::ChangeMode(CManager::MODE_REZULT_CLEAR);
	}
}
//***************************************************************
//	描画
//***************************************************************
void	CSter::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mScale,mRotate;		//左から座標、大きさ、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//モデルファイルの取得
	LPD3DXMESH	pMesh = CXfile::GetMesh(STAR_ID);
	LPD3DXBUFFER	pBuffer = CXfile::GetBuffer(STAR_ID);
	DWORD	pWord = CXfile::GetWord(STAR_ID);

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

			//マトリックス初期化
			D3DXMatrixIdentity(&m_mtxWorld);

			//大きさ設定
			D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//角度設定
			D3DXMatrixRotationYawPitchRoll(&mRotate, m_Vertex_3d.Rot_vtx.y,0.0f,0.0f);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//座標設定
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x,CScene3d::GetHeight(m_Vertex_3d.vtx) + 1.0f + m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z);

			//合成
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

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

