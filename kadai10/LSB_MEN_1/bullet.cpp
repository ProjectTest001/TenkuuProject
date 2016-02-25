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
#include	"renderer.h"
#include	"scene.h"
#include	"scene3d.h"
#include	"scenebillboard.h"
#include	"camera.h"
#include	"manager.h"
#include	"bullet.h"
#include	"field.h"
#include	"explosion.h"
#include	"texture.h"

//***************************************************************
//	静的変数
//***************************************************************
VERTEX_3D	CBullet::m_Vertex_3d;

//***************************************************************
//	クラス関数
//***************************************************************

//***************************************************************
//	コンストラクタ
//	戻り値
//	なし
//***************************************************************
CBullet::CBullet()
{
	//初期化
	m_pD3DVtxBuff = NULL;

}

//***************************************************************
//	デストラクタ
//***************************************************************
CBullet::~CBullet()
{

}

//***************************************************************
//	初期化
//引数：
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：呼び出した対象の座標
//D3DXVECTOR3	Rot:呼び出した対象の向いてる角度
//int	TexNo:テクスチャ番号
//戻り値
//HRESULT:終了コード
//***************************************************************
HRESULT	CBullet::Init(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo)
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
						pv[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
						pv[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

						// テクスチャＵＶ
						pv[0].tex = D3DXVECTOR2(0.0f,0.0f);		//0.0f,0.0fで左上指定
						pv[1].tex = D3DXVECTOR2(1.0f,0.0f);		//1.0f,0.0fで右上指定
						pv[2].tex = D3DXVECTOR2(0.0f,1.0f);		//0.0f,1.0fで左下指定
						pv[3].tex = D3DXVECTOR2(1.0f,1.0f);		//1.0f,1.0fで右下指定

					//ロック
					m_pD3DVtxBuff->Unlock();

					//数値初期化
					m_Vertex_3d.vtx = vtx;										//座標
					m_Vertex_3d.Rot_vtx = Rot;										//角度
					m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);			//速度
					m_nTex = TexNo;												//画像番号

	return	S_OK;
}

//***************************************************************
//	ポリゴン生成
//引数：
//LPDIRECT3DDEVICE9	pDevice：デバイスポインタ
//D3DXVECTOR3	vtx：呼び出した対象の座標
//D3DXVECTOR3	Rot:呼び出した対象の向いてる角度
//int	TexNo:テクスチャ番号
//戻り値
//CBullet	元クラス
//***************************************************************
CBullet	*CBullet::Create(LPDIRECT3DDEVICE9	pDevice,D3DXVECTOR3	vtx,D3DXVECTOR3	Rot,int	TexNo)
{
	//ポインタ宣言
	CBullet	*pBullet;

	//クラス生成
	pBullet = new	CBullet;

	//初期化
	pBullet->Init(pDevice,vtx,Rot,TexNo);

	return	pBullet;
}

//***************************************************************
//	終了
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
void	CBullet::Uninit()
{

	//解放処理
	//バッファ解放
	if(m_pD3DVtxBuff != NULL )
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}

}

//***************************************************************
//	更新
//	引数
//	なし
//	戻り値
//	なし
//***************************************************************
void	CBullet::Update()
{

	//地面情報取得
	VERTEX_3D	pField = CField::GetVertex();
	
	//ベクトル変数宣言
	const	D3DXVECTOR3	aVtx[4] = 
	{
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2) ),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//左上
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / 2 )),		//右上
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / 2),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//右下
		D3DXVECTOR3(pField.vtx.x + (pField.Scail_vtx.x / (-2)),0.0f,pField.vtx.z + (pField.Scail_vtx.z / (-2) )),		//左下
	};
	
	//角度が加わった時の修正変数
	D3DXVECTOR3	aVtxNew[4];
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
		aVtxNew[nCount].x = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x + cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z;
		aVtxNew[nCount].z = sinf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].z - cosf(pField.Rot_vtx.y * D3DX_PI) * aVtx[nCount].x;
	}

	//速度
	m_Vertex_3d.Speed_vtx.x -= sin(D3DX_PI * m_Vertex_3d.Rot_vtx.x) * 0.08f;
	m_Vertex_3d.Speed_vtx.z -= cos(D3DX_PI * m_Vertex_3d.Rot_vtx.x) * 0.08f;

	//抵抗摩擦
	m_Vertex_3d.Speed_vtx.x -= m_Vertex_3d.Speed_vtx.x * 0.3f;
	//m_Vertex_3d.Speed_vtx.y -= m_Vertex_3d.Speed_vtx.y * 0.3f;		//Ｙ座標の計算は今は使わない
	m_Vertex_3d.Speed_vtx.z -= m_Vertex_3d.Speed_vtx.z * 0.3f;

		//移動
		m_Vertex_3d.vtx.x += m_Vertex_3d.Speed_vtx.x;
		m_Vertex_3d.vtx.z += m_Vertex_3d.Speed_vtx.z;

	//当たり判定測定
	for(int	nCount = 0 ; nCount < 4 ; nCount++)
	{
				//弾と壁のベクトル関係の計算
				D3DXVECTOR3	nVtx = aVtxNew[(int)(nCount + 1) % 4] - aVtxNew[nCount];
				D3DXVECTOR3	BulletVtx = m_Vertex_3d.vtx - aVtxNew[nCount];

			//外積計算で負の数字になった場合、当たった事にする
			if( (nVtx.z * BulletVtx.x- nVtx.x * BulletVtx.z) < 0 )
			{
				//爆発エフェクト生成後、消滅
				CExplosion::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,EXPLOSION_TEXTURE);
				//CBullet::Uninit();
				CScene::Release();
				break;
			}
	}
}
//***************************************************************
//	描画
//引数
//LPDIRECT3DDEVICE9 pDevice:デバイスポインタ
//戻り値
//なし
//***************************************************************
void	CBullet::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	
	//マトリックス変数宣言
	D3DXMATRIX	mTrans;		//左から座標、大きさ、回転

	//テクスチャ取得変数
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//カメラ関係変数宣言
	D3DXMATRIX	mtxView;
	CCamera	*pCamera;

	//カメラ情報取得
	pCamera = CManager::GetCamera();		//カメラポインタ
	mtxView = pCamera->GetViewMatrix();		//ビューマトリックス

	//描画タイプの変更
	CRenderer::SetRenderType(CRenderer::NOMAL);

	//マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビルボード処理
	D3DXMATRIX	matViewInv(mtxView);
			matViewInv._41 = 

			matViewInv._42 = 

			matViewInv._43 = 0.0f;

		D3DXMatrixInverse(&matViewInv,NULL,&matViewInv);

		//合成
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
