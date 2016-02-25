//***************************************************************
//
//	scene3d.cpp
//	name:Masatugu Kamada
//	�X�V���F2012/05/23
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
CSter::CSter()
{
	//������
	m_pMesh = NULL;
	m_pD3DXMatBuff = NULL;
	m_nNumMat = 0;

}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CSter::~CSter()
{

}

//***************************************************************
//	������
//�����F
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//�߂�l�F
//HRESULT	�I���R�[�h
//***************************************************************
HRESULT	CSter::Init(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,int	TexNo)
{
	//������
	m_Vertex_3d.vtx = vtx;
	m_Vertex_3d.diffuse = D3DXCOLOR(1.0,0.0f,0.0f,1.0f);
	m_Vertex_3d.Speed_vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	get = false;
	vec = 3.0f;
	m_nTex = YEROWW_TEXTURE;

	return	S_OK;
}

//***************************************************************
//	�����֐�
//����
//LPDIRECT3DDEVICE9 pDevice:�f�o�C�X�|�C���^
//D3DXVECTOR3 vtx�F�w����W
//�߂�l
//CScene_x	���N���X
//***************************************************************
CScene_x	*CSter::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vtx,int	TexNo)
{
	//�|�C���^�錾
	CSter	*pSter;

	//�N���X����
	pSter = new	CSter;

	//������
	pSter->Init(pDevice, vtx,TexNo);

	return	pSter;

}
//***************************************************************
//	�I��
//***************************************************************
void	CSter::Uninit()
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
//***************************************************************
void	CSter::Update()
{
	//�L�[�ϐ��Ǝ擾
	CInputKeyboard	*pKeyBoard;
	pKeyBoard = CManager::GetInputKeyboard();//���͏����ւ̃|�C���^�擾

	//��]
	m_Vertex_3d.Rot_vtx.y += 0.04f + m_Vertex_3d.Speed_vtx.y * 2;

	//�����擾�����ꍇ
	if(CItem::HitItem(m_Vertex_3d.vtx,CGame::GetPlayer().vtx) && !CTime::TimeUp() && m_Vertex_3d.Speed_vtx.y == 0.0f)
	{
		m_Vertex_3d.Speed_vtx.y = 0.08f;
		get = true;
	}

	//�ړ�
	m_Vertex_3d.vtx.y += m_Vertex_3d.Speed_vtx.y;

	if(get)
	{
		vec -= m_Vertex_3d.Speed_vtx.y;
	}

	//���ȏ㐯���㏸��������ł��A�Q�[���N���A
	if(vec < 0.0f)
	{
		CManager::ChangeMode(CManager::MODE_REZULT_CLEAR);
	}
}
//***************************************************************
//	�`��
//***************************************************************
void	CSter::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	//�}�g���b�N�X�ϐ��錾
	D3DXMATRIX	mTrans,mScale,mRotate;		//��������W�A�傫���A��]

	//�e�N�X�`���擾�ϐ�
	LPDIRECT3DTEXTURE9	Texture = CTexture::GetTexture(m_nTex);

	//���f���t�@�C���̎擾
	LPD3DXMESH	pMesh = CXfile::GetMesh(STAR_ID);
	LPD3DXBUFFER	pBuffer = CXfile::GetBuffer(STAR_ID);
	DWORD	pWord = CXfile::GetWord(STAR_ID);

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
		LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)pBuffer->GetBufferPointer();


			//�`��J�n
			for(unsigned int i = 0 ; i < pWord ; i++)
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
				pMesh->DrawSubset(i);
			}
			
		//�}�e���A�������ɖ߂�
		pMaterial->MatD3D.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
		pMaterial->MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pMaterial->MatD3D.Emissive = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		pDevice->SetMaterial(&pMaterial->MatD3D);

}

