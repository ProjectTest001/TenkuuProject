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
//	�N���X
//******************************************


class	CItem:public	CScene_x
{
public:
	CItem();					//�R���X�g���N�^
	~CItem();					//�f�X�g���N�^

	HRESULT	Init();						//������
	void	UnInit();					//�I��
	void	Update();					//�X�V
	void	Draw();						//�`��
	//void	Create();					//����

	bool	HitItem(D3DXVECTOR3	ItemPos,D3DXVECTOR3	Pos);					//�����蔻��

private:

};

#endif
