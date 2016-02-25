//***************************************************************
//
//	scene.cpp
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
#include	"scene.h"
#include	"scene2d.h"
#include	"renderer.h"

//***************************************************************
//	�N���X�֐�
//***************************************************************

//***************************************************************
//	�ÓI�ϐ�
//***************************************************************
CScene	*CScene::m_pTop = NULL;
CScene	*CScene::m_pCur = NULL;
CScene	*CScene::m_apTop[MAX_LIST] = {NULL};
CScene	*CScene::m_apCur[MAX_LIST] = {NULL};

//***************************************************************
//	�R���X�g���N�^
//	����
//	int	nPriority�F�K�w�ԍ�
//	�߂�l
//	�Ȃ�
//***************************************************************
CScene::CScene(int	nPriority)
{
	//�v���C�I���e�B�̐ݒ�
	m_nPriority = nPriority;

	//OBJ�^�C�v�̐ݒ�
	SetObjectType(CScene::TYPE_MAX);

	//�N���X����
	//���Ɉ�ȏ㐶�����Ă���ꍇ
		if(m_apTop[m_nPriority] != NULL)
		{
			m_pPrev = m_apCur[m_nPriority];			//�O�Ɍ��݂̋L�^��ۑ�
			m_pNext = NULL;							//���̐����ׂ̈�NULL�ɂ���
			m_apCur[m_nPriority]->m_pNext = this;		//���݂̒��̎��ɐ���
			m_apCur[m_nPriority] = this;				//���݂ɐ���
		}
		//����������Ă��Ȃ��ꍇ
		else
		{
			m_apTop[m_nPriority] = this;			//�擪�ɐ���
			m_apCur[m_nPriority] = this;			//�ŏ��Ȃ̂Ō��݂ɐ���
			m_pNext = NULL;						//���̐����ׂ̈�NULL�ɂ���
			m_pPrev = NULL;						//�O��NULL�ɂ���

		}

		//���S�t���O������
		m_bDelete = false;
}

//***************************************************************
//	�f�X�g���N�^
//***************************************************************
CScene::~CScene()
{

}
//***************************************************************
//	�X�e�[�g�̏I������
//***************************************************************
void	CScene::UninitAll(void)
{
	//�|�C���^�錾
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST - 1 ; nCount++)
	{
		pScene = m_apTop[nCount];
		//�S�Ẵ��X�g���������܂ŌJ��Ԃ�
		while(pScene)
		{
			//���̃I�u�W�F�N�g�ւ̃|�C���^��ۑ�
			CScene	*pSceneNext = pScene->m_pNext;

			//�X�V
			pScene->Release();

			//���̃I�u�W�F�N�g����
			pScene = pSceneNext;
		}
	}

}

//***************************************************************
//	�I�u�W�F�N�g��j������
//***************************************************************
void	CScene::Release(void)
{
	//
	m_bDelete = true;
}

//***************************************************************
//	�S�ẴI�u�W�F�N�g��j������
//***************************************************************
void	CScene::ReleaseAll(void)
{
	//�|�C���^�錾
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		//�S�Ẵ��X�g���������܂ŌJ��Ԃ�
		while(pScene)
		{
			//���̃I�u�W�F�N�g�ւ̃|�C���^��ۑ�
			CScene	*pSceneNext = pScene->m_pNext;

			//�X�V
			pScene->Release();

			//���̃I�u�W�F�N�g����
			pScene = pSceneNext;
		}
	}

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//���̃I�u�W�F�N�g�ւ̃|�C���^��ۑ�
			CScene	*pSceneNext = pScene->m_pNext;

			//���S�t���O���������Ă���ꍇ
			if(pScene->m_bDelete)
			{
				//���X�g�̐擪�̏ꍇ
				if(pScene == m_apTop[pScene->m_nPriority])
				{
					//�擪�Ƀ����[�X�Ώۂ̎��̃A�h���X������
					m_apTop[pScene->m_nPriority] = pScene->m_pNext;

					//���X�g�̎c�肪�����̎�
					if(pScene->m_pNext != NULL)
					{
						pScene->m_pNext->m_pPrev = NULL;
					}
				}
				//���X�g�̍Ō�̏ꍇ
				else	if(pScene == m_apCur[pScene->m_nPriority])
				{
					m_apCur[pScene->m_nPriority] = pScene->m_pPrev;
					pScene->m_pPrev->m_pNext = NULL;
				}
				//����ȊO
				else
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				//�������
				pScene->Uninit();
				delete	pScene;
			}

			//���̃I�u�W�F�N�g����
			pScene = pSceneNext;
		}
	}

}

//***************************************************************
//	�S�X�V
//***************************************************************
void	CScene::UpdateAll(void)
{
	//�|�C���^�錾
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//���̃I�u�W�F�N�g�ւ̃|�C���^��ۑ�
			CScene	*pSceneNext = pScene->m_pNext;

			//�X�V
			pScene->Update();

			//���̃I�u�W�F�N�g����
			pScene = pSceneNext;
		}
	}

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//���̃I�u�W�F�N�g�ւ̃|�C���^��ۑ�
			CScene	*pSceneNext = pScene->m_pNext;

			//���S�t���O���������Ă���ꍇ
			if(pScene->m_bDelete)
			{
				//���X�g�̐擪�̏ꍇ
				if(pScene == m_apTop[pScene->m_nPriority])
				{
					//�擪�Ƀ����[�X�Ώۂ̎��̃A�h���X������
					m_apTop[pScene->m_nPriority] = pScene->m_pNext;

					//���X�g�̎c�肪�����̎�
					if(pScene->m_pNext != NULL)
					{
						pScene->m_pNext->m_pPrev = NULL;
					}
				}
				//���X�g�̍Ō�̏ꍇ
				else	if(pScene == m_apCur[pScene->m_nPriority])
				{
					m_apCur[pScene->m_nPriority] = pScene->m_pPrev;
					pScene->m_pPrev->m_pNext = NULL;
				}
				//����ȊO
				else
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				//�������
				pScene->Uninit();
				delete	pScene;
			}

			//���̃I�u�W�F�N�g����
			pScene = pSceneNext;
		}
	}
}

//***************************************************************
//	�S�`��
//***************************************************************
void	CScene::DrawAll(LPDIRECT3DDEVICE9 pDevice)
{
	//�|�C���^�錾
	CScene	*pScene;

	for(int	nCount = 0 ; nCount < MAX_LIST ; nCount++)
	{
		pScene = m_apTop[nCount];
		while(pScene)
		{
			//���̃I�u�W�F�N�g�ւ̃|�C���^��ۑ�
			CScene	*pSceneNext = pScene->m_pNext;

			//�X�V
			pScene->Draw(pDevice);

			//���̃I�u�W�F�N�g����
			pScene = pSceneNext;

		}
	}
}