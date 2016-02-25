//***************************************************************
//
//	coin.cpp
//	name:Masatugu Kamada
//	create:2012/05/23
//	update:2012/10/26
//
//***************************************************************

//***************************************************************
//	�C���N���[�h
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
#include	"scenebillboard.h"
#include	"manager.h"
#include	"player.h"
#include	"item.h"
#include	"coin.h"
#include	"number.h"
#include	"score.h"
#include	"time.h"
#include	"shadow.h"
#include	"texture.h"
#include	"game.h"
#include	"light.h"
#include	"shine.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�R���X�g���N�^
//	����
//	int	nPriority�F�K�w�ԍ�
//	�C�j�V�����C�U
//	CScene(nPriority)�F�K�w�ԍ��󂯓n��
//	�߂�l
//	�Ȃ�
//***************************************************************
CCoin::CCoin()
{
	//������
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CCoin::~CCoin()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//D3DXVECTOR3 vtx:���W
//int	TexNo:�摜�ԍ�
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CCoin::Init(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,int	TexNo)
{
		//���f���ǂݍ���
	if( FAILED(D3DXLoadMeshFromX("model/�R�C��.x",
		D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_pD3DXMatBuff, NULL, &m_nNumMat, &m_pMesh)))
		{
			MessageBox(NULL,"�ǂݍ���","�G���[",MB_OK);

		}

	//������
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.diffuse = D3DXCOLOR(1.0,0.0f,0.0f,1.0f);
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	get = false;
	vec = 3.0f;
	m_nTex = TexNo;

	return	S_OK;
}

//***************************************************************
//	�����֐�
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//D3DXVECTOR3 vtx�F�w����W
//int	TexNo:�摜�ԍ�
//�߂�l
//CScene_x	���N���X
//***************************************************************
CScene_x	*CCoin::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,int	TexNo)
{
	//�|�C���^�錾
	CCoin	*pCoin;

	//�N���X����
	pCoin = new	CCoin;

	//������
	pCoin->Init(pDevice, vtx,TexNo);

	return	pCoin;

}
//***************************************************************
//	�I��
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CCoin::Uninit()
{
	//�������

	//���b�V�����
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�o�b�t�@���
	if(m_pD3DXMatBuff != NULL)
	{
		m_pD3DXMatBuff->Release();
		m_pD3DXMatBuff = NULL;
	}

	CScene::Release();
}

//***************************************************************
//	�X�V
//	����
//	�Ȃ�
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CCoin::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

	//��]
	m_Vertex_3d.Rot_vtx.y += 0.04f + m_Vertex_3d.Speed_vtx.y * 2;

	//�R�C�����擾�����ꍇ
	if(CItem::HitItem(m_Vertex_3d.vtx,CGame::GetPlayer().vtx) && !CTime::TimeUp() && m_Vertex_3d.Speed_vtx.y == 0.0f)
	{
		m_Vertex_3d.Speed_vtx.y = 0.08f;			//�㏸�����ݒ�
		get = true;									//�擾�t���O
		CScore::SetScore(100);						//�X�R�A�㏸
		PlaySound(SE_01,DMUS_SEGF_SECONDARY);		//�r�d�Đ�
	}

	//�ړ�
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;

	//�擾������㏸
	if(get)
	{
		vec -= m_Vertex_3d.Speed_vtx.y;
		CShine::Create(CRenderer::GetDevice(),D3DXVECTOR3( m_Vertex_3d.vtx.x,CScene3d::GetHeight(m_Vertex_3d.vtx) + 1.0f + m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z),D3DXCOLOR(1,1,0,1),30,D3DXVECTOR3(3.0f,3.0f,3.0f),0.4f,SHADOW_TEXTURE);
	}

	//���ȏ�R�C�����㏸���������
	if(vec < 0.0f)
	{
		Uninit();
	}

	//�e����
	//CShadow::Create(CRenderer::GetDevice(),m_Vertex_3d.vtx,D3DXCOLOR(1,1,1,1),m_Vertex_3d.Scail_vtx,3);

}
//***************************************************************
//	�`��
//	����
//	LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//	�߂�l
//	�Ȃ�
//***************************************************************
void	CCoin::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//���C�g������
	CLight::SetOffLight(pDevice);

	//�`��^�C�v�̕ύX
	CRenderer::SetRenderType(CRenderer::NOMAL);

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&m_mtxWorld);

			//�傫���ݒ�
			D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mScale);

			//�p�x�ݒ�
			D3DXMatrixRotationYawPitchRoll(&mRotate, m_Vertex_3d.Rot_vtx.y,0.0f,0.0f);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mRotate);

			//���W�ݒ�
			D3DXMatrixTranslation(&mTrans, m_Vertex_3d.vtx.x,CScene3d::GetHeight(m_Vertex_3d.vtx) + 1.0f + m_Vertex_3d.vtx.y,m_Vertex_3d.vtx.z);

			//����
			D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mTrans);

			//�Z�b�e�B���O
			pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

		//���b�V���ǂݍ���
		LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)m_pD3DXMatBuff->GetBufferPointer();


			//�`��J�n
			for(unsigned int i = 0 ; i < m_nNumMat ; i++)
			{
				//�}�e���A���Z�b�g
				pDevice->SetMaterial(&pMaterial[i].MatD3D);

				if(Texture)
				{
					//�e�N�X�`���\��t��
					pDevice->SetTexture(0,
						Texture);
				}

				//�`��
				m_pMesh->DrawSubset(i);
			}
			
		//�}�e���A�������ɖ߂�
		pMaterial->MatD3D.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
		pMaterial->MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pMaterial->MatD3D.Emissive = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pDevice->SetMaterial(&pMaterial->MatD3D);

		//���C�g�����ɖ߂�
		CLight::SetOnLight(pDevice);
}

