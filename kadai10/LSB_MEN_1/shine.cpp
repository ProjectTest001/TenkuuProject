//*****************************************************
//
//	shine.cpp
//	name:MasatuguKamada
//	create:2012/11/08
//	update:2012/11/08
//
//*****************************************************

//*****************************************************
//	インクルード
//*****************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	"main.h"
#include	"renderer.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"scenebillboard.h"
#include	"shine.h"
#include	"camera.h"
#include	"manager.h"
#include	"texture.h"


//******************************************************
//	メイン関数
//******************************************************

//******************************************************
//	コンストラクタ
//	引数
//	なし
//	戻り値
//	なし
//******************************************************
CShine::CShine()
{

}

//******************************************************
//	デストラクタ
//	引数
//	なし
//	戻り値
//	なし
//******************************************************
CShine::~CShine()
{

}

//******************************************************
//	初期化
//	引数
//	LPDIRECT3DDEVICE9	pDevice:デバイスポインタ
//	D3DXVECTOR3 pos:座標
//	D3DXCOLOR color:配色
//	int life:寿命
//	D3DXVECTOR3 Scail:拡縮
//	float Speed:減少速度
//	int TexNo:画像番号
//	戻り値
//	HRESULT：終了コード
//******************************************************
HRESULT	CShine::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3 pos, D3DXCOLOR color, int life, D3DXVECTOR3 Scail, float Speed, int TexNo)
{
			//バッファ設定
			if(FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D)) * 4,
											D3DUSAGE_WRITEONLY,
											0,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
			{
				return	E_FAIL;
			}

				//アンロック変数
				VERTEX_3D	*pv;

					//ロック解除
					m_pD3DVtxBuff->Lock(0,0,(void**)&pv,0);

				//画像の初期化の流れ
						//座標x,y,z
						pv[0].vtx = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
						pv[1].vtx = D3DXVECTOR3(0.5f, 0.5f,0.0f);
						pv[2].vtx = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
						pv[3].vtx = D3DXVECTOR3(0.5f,-0.5f , 0.0f);

						//法線
						pv[0].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[1].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[2].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);
						pv[3].hor = D3DXVECTOR3(0.0f,1.0f,0.0f);


						//頂点色(赤、緑、青）
						pv[0].diffuse = color;
						pv[1].diffuse = color;
						pv[2].diffuse = color;
						pv[3].diffuse = color;

						// テクスチャＵＶ
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0fで左上指定
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0fで右上指定
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0fで左下指定
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0fで右下指定

					//ロック
					m_pD3DVtxBuff->Unlock();

					//数値初期化
					m_Vertex_3d.vtx = pos;						//座標
					m_Vertex_3d.vtx.y += 1.0f;
					m_Vertex_3d.diffuse = color;				//配色
					m_Vertex_3d.Scail_vtx = Scail;				//拡縮
					m_nLife = life;								//寿命
					m_fSpeed = Speed;							//減少速度
					m_nTex = TexNo;								//画像番号

	return	S_OK;
}

//******************************************************
//	初期化
//	引数
//	LPDIRECT3DDEVICE9	pDevice:デバイスポインタ
//	D3DXVECTOR3 pos:座標
//	D3DXCOLOR color:配色
//	int life:寿命
//	D3DXVECTOR3 Scail:拡縮
//	float Speed:減少速度
//	int TexNo:画像番号
//	戻り値
//	HRESULT：終了コード
//******************************************************
CShine	*CShine::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3 pos, D3DXCOLOR color, int life, D3DXVECTOR3 Scail,
					   float Speed, int TexNo)
{
	CShine	*pShine;

	pShine = new	CShine;

	pShine->Init(pDevice,pos,color,life,Scail,Speed,TexNo);

	return	pShine;
}

//******************************************************
//	終了
//	引数
//	なし
//	戻り値
//	なし
//******************************************************
void	CShine::UnInit()
{
	//解放処理
	//バッファ解放
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

}

//******************************************************
//	更新
//	引数
//	なし
//	戻り値
//	なし
//******************************************************
void	CShine::Update()
{
	//ライフ減少
	m_nLife--;

	//縮小
	m_Vertex_3d.Scail_vtx.x -= m_fSpeed;
	m_Vertex_3d.Scail_vtx.y -= m_fSpeed;
	m_Vertex_3d.Scail_vtx.z -= m_fSpeed;

	//小さくなるか寿命が切れたら終了
	if(m_Vertex_3d.Scail_vtx.x < 0.0f || m_Vertex_3d.Scail_vtx.y < 0.0f ||m_Vertex_3d.Scail_vtx.z < 0.0f || m_nLife < 0)
	{
		CScene::Release();
	}
}

//******************************************************
//	描画
//	引数
//	LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//	戻り値
//	なし
//******************************************************
void	CShine::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//マトリックス変数宣言
	D3DXMATRIX	mTrans,mScale,mRotate;		//左から座標、大きさ、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//カメラ関係変数宣言
	D3DXMATRIX	mtxView;
	CCamera	*pCamera;

	//カメラ情報取得
	pCamera = CManager::GetCamera();

	mtxView = pCamera->GetViewMatrix();

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::KASAN);

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//大きさ設定
	D3DXMatrixScaling(&mScale,m_Vertex_3d.Scail_vtx.x, m_Vertex_3d.Scail_vtx.y, m_Vertex_3d.Scail_vtx.z);

	//合成
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		D3DXMatrixInverse(&matViewInv,NULL,&matViewInv);

		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&matViewInv);

	//座標設定
	D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x, m_Vertex_3d.vtx.y, m_Vertex_3d.vtx.z);

	//合成
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

	//セッティング
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//バッファ指定
	pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));

		//フォーマットの指定
		pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ設定
			pDevice->SetTexture(0,
				Texture);

			//画像表示
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}





