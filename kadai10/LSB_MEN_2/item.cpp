//******************************************
//
//	item.cpp
//	name:MasatuguKamada
//	create:2012/10/06
//	update:2012/10/06
//
//******************************************


//******************************************
//	�C���N���[�h
//******************************************
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

//********************************************
//	�N���X�֐�
//********************************************

//********************************************
//	�R���X�g���N�^
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//********************************************
CItem::CItem()
{

}

//********************************************
//	�f�X�g���N�^
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//********************************************
CItem::~CItem()
{

}

//********************************************
//	������
//	����
//	�Ȃ�
//	�߂�l
//	HRESULT�F�I���R�[�h
//********************************************
HRESULT	CItem::Init()
{

	return	S_OK;
}

//********************************************
//	�I��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//********************************************
void	CItem::UnInit()
{

}

//********************************************
//	�X�V
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//********************************************
void	CItem::Update()
{

}


//********************************************
//	�`��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//********************************************
void	CItem::Draw()
{

}

//********************************************
//	�����蔻��
//	����
//	D3DXVECTOR3	ItemPos:�A�C�e���̍��W
//	D3DXVECTOR3	Pos:�Ώۂ̍��W
//	�߂�l
//	�Ȃ�
//********************************************
bool	CItem::HitItem(D3DXVECTOR3 ItemPos, D3DXVECTOR3 Pos)
{
	bool	Hit = false;

	if( ItemPos.x - 0.5f < Pos.x && ItemPos.x + 0.5f > Pos.x &&
		CScene3d::GetHeight(ItemPos)  + ItemPos.y - 1.5f < Pos.y &&
		CScene3d::GetHeight(ItemPos)  + ItemPos.y + 1.5f > Pos.y &&
		ItemPos.z - 0.5f < Pos.z && ItemPos.z + 0.5f > Pos.z )
	{
		Hit = true;
		return	Hit;
	}

	return	Hit;

}


