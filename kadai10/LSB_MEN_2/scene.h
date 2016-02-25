//***************************************************************
//
//	scene.h
//	name:Masatugu Kamada
//	更新日：2012/05/23
//
//***************************************************************

#ifndef	SCENE_H_
#define	SCENE_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define	MAX_LIST	(8)	//リスト構造の総数

//*****************************************************************************
//構造体
//*****************************************************************************
//２Ｄテクスチャ構造体
typedef	struct
{
	D3DXVECTOR3	vtx;		//座標x,y,z
	float	rhw;			//バースの補正値
	D3DCOLOR	diffuse;	//頂点色
	D3DXVECTOR2	tex;		//テクスチャＵＶ座標
	D3DXVECTOR2	Scail;		//大きさ
}VERTEX_2D;

//３Ｄテクスチャ構造体
typedef	struct
{
	D3DXVECTOR3	vtx;			//座標x,y,z
	D3DXVECTOR3	hor;			//法線
	D3DCOLOR	diffuse;		//頂点色
	D3DXVECTOR2	tex;			//テクスチャＵＶ座標
	D3DXVECTOR3	vertex;			//頂点数
	int	index;					//インデックス数
	int	primitive;				//プリミティブ数
	D3DXVECTOR3	Rot_vtx;		//回転角度
	D3DXVECTOR3	Scail_vtx;		//幅と高さ
	bool	MoveFlag;			//移動中
	D3DXVECTOR3	*DataVtx;		//予備座標情報
	D3DXVECTOR3	Speed_vtx;		//速度
	float	PosNowY;			//現在位置
}VERTEX_3D;

//その他の基本ステータス
typedef	struct
{
	D3DXVECTOR3	Speed_vtx;		//速度
	D3DXVECTOR3	Rot_vtx;		//回転角度
	D3DXVECTOR3	Scail_vtx;		//拡大・縮小
}STATAS;

//***************************************************************
//	クラス定義
//***************************************************************
class	CScene
{
public:

	//オブジェクトタイプ
	typedef	enum
	{
		TYPE_GIMMICK = 0,			//ギミック系（移動床等）
		TYPE_MAX,					//その他
	}OBJECT_TYPE;
	OBJECT_TYPE	m_nType;														//オブジェクトタイプ
	CScene(int	nPriority = 3);											//インストラクタ(引数：もらう階層番号（デフォルト引数は③番））
	virtual	~CScene();													//デストラクタ
	virtual	HRESULT	Init(LPDIRECT3DDEVICE9	pDevice){return	S_OK;};		//初期化
	virtual	void	Uninit(void) = 0;									//終了
	virtual	void	Update(void) = 0;									//更新
	virtual	void	Draw(LPDIRECT3DDEVICE9	pDevice) = 0;				//描画
	static	void	UninitAll(void);									//ステートの終了処理
	void	Release(void);												//オブジェクトの破棄
	static	void	ReleaseAll(void);									//オブジェクトの全破棄
	static	void	UpdateAll(void);									//全更新
	static	void	DrawAll(LPDIRECT3DDEVICE9	pDevice);				//全描画
	virtual void	GetVtx(VERTEX_3D	*Vtx){};						//位置取得
	static	CScene	*GetTopScene(int	Cnt){return	m_apTop[Cnt];};		//最初のsceneクラス取得関数
	CScene	*GetNext(void){return	m_pNext;};							//次のsceneクラス取得関数
	OBJECT_TYPE	GetType(void){return	m_nType;};						//オブジェクトタイプ取得関数
	void	SetObjectType(OBJECT_TYPE	Type){m_nType = Type;};			//オブジェクトタイプセット関数
private:
	static	CScene	*m_apTop[MAX_LIST];									//先頭のリスト構造配列
	static	CScene	*m_apCur[MAX_LIST];									//現在のリスト構造配列
	CScene	*m_pPrev;													//前のオブジェクトへのポインタ
	CScene	*m_pNext;													//次のオブジェクトへのポインタ
	static	CScene	*m_pTop;											//リストの先頭のオブジェクトへのポインタ
	static	CScene	*m_pCur;											//リストの現在のオブジェクトへのポインタ
	int	m_nPriority;													//自分のプライオリティ番号（階層番号）
	bool	m_bDelete;													//死亡フラグ
};

#endif