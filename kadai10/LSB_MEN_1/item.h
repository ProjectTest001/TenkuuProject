//******************************************
//
//	item.h
//	name:MasatuguKamada
//	create:2012/10/06
//	update:2012/10/06
//
//******************************************

#ifndef	ITEM_H_
#define	ITEM_H_

//******************************************
//	クラス
//******************************************


class	CItem:public	CScene_x
{
public:
	CItem();					//コンストラクタ
	~CItem();					//デストラクタ

	HRESULT	Init();						//初期化
	void	UnInit();					//終了
	void	Update();					//更新
	void	Draw();						//描画
	//void	Create();					//生成

	bool	HitItem(D3DXVECTOR3	ItemPos,D3DXVECTOR3	Pos);					//当たり判定

private:

};

#endif
