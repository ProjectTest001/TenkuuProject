//***************************************************************
//
//	script.cpp
//	name:Masatugu Kamada
//	create:2012/11/26
//	update:2012/11/26
//
//***************************************************************

//**************************************************************
//	インクルード
//**************************************************************
#include	<windows.h>
#include	<d3dx9.h>
#include	<stdio.h>
#include	<math.h>
#include	"main.h"
#include	"sound.h"
#include	"scene.h"
#include	"scene2d.h"
#include	"scene_x.h"
#include	"player.h"
#include	"script.h"

//**************************************************************
//	クラス関数
//**************************************************************

//**************************************************************
//	静的変数
//**************************************************************
MOTIONDATA	*CScript::m_pMotionPlayerData = NULL;

//**************************************************************
//	コンストラクタ
//**************************************************************
CScript::CScript()
{

}

//**************************************************************
//	デストラクタ
//**************************************************************
CScript::~CScript()
{

}

//**************************************************************
//	モーション情報の読み込み
//	引数
//	なし
//	戻り値
//	なし
//**************************************************************
void	CScript::LoadMotionScript(void)
{
	//変数宣言
	FILE	*pFile;				//ファイル変数
	char	aStr[128];
	pFile = fopen(PLAYER_MOTION_DATA_FILE,"rt");
	m_pMotionPlayerData = new	MOTIONDATA[CPlayer::MOTION_MAX];

	//ファイルチェック
	if(!pFile)
	{
		return;
	}

	//文字数をはかる変数
	int	len;
	while(fgets(aStr,256,pFile))
	{
		len= strlen(aStr);
		aStr[len-1] = NULL;
		
		//ニュートラル
		if(strcmp(aStr,"NEUTRAL") == 0)
		{
			SetData(pFile,CPlayer::MOTIONTYPE_NEUTRAL,"NEUTRAL_END");
		}
		//歩く
		else	if(strcmp(aStr,"WALK") == 0)
		{
			SetData(pFile,CPlayer::MOTIONTYPE_WALK, "WALK_END");
		}
		//ジャンプ
		else	if(strcmp(aStr,"JUMP") == 0)
		{
			SetData(pFile,CPlayer::MOTIONTYPE_JUMP, "JUMP_END");
		}
		//腕を伸ばす
		else	if(strcmp(aStr,"STICK") == 0)
		{
			SetData(pFile,CPlayer::MOTIONTYPE_PUNCH, "STICK_END");
		}

		else	if(strcmp(aStr,"MOTION_END") == 0)
		{
			break;
		}
	}
}


void	CScript::SetData(FILE	*File,int type,const	char	*end)
{
	//ファイルチェック
	if(!File)
	{
		return;
	}

	char	*aStr = new	char;
	int	Key = -1;
	int	nParts = -1;
	while(1)
	{
		fscanf(File,"%s",aStr);
		nParts = GetParts(aStr);

		if(strcmp(aStr,"ALLKEY") == 0)
		{
			int	num;
			fscanf(File," %d",&num);
			m_pMotionPlayerData[type].pKey = new	KEY_INFO[num];
			m_pMotionPlayerData[type].NumFrame = num;
		}
		else	if(strcmp(aStr,"KEY") == 0)
		{
			Key++;
		}
		else	if(strcmp(aStr,"FRAME") == 0)
		{
			if(m_pMotionPlayerData)
			{
				fscanf(File," = %d",&m_pMotionPlayerData[type].pKey[Key].nFrame);
			}
		}
		else	if(nParts != -1)
		{
			if(m_pMotionPlayerData)
			{
				fscanf(File," = ");
				fscanf(File,"%ff %ff %ff %ff %ff %ff\n",&m_pMotionPlayerData[type].pKey[Key].aKEY[nParts].posx,&m_pMotionPlayerData[type].pKey[Key].aKEY[nParts].posy,&m_pMotionPlayerData[type].pKey[Key].aKEY[nParts].posz,
													&m_pMotionPlayerData[type].pKey[Key].aKEY[nParts].rotx,&m_pMotionPlayerData[type].pKey[Key].aKEY[nParts].roty,&m_pMotionPlayerData[type].pKey[Key].aKEY[nParts].rotz);
			}
		}
		else	if(strcmp(aStr,end) == 0)
		{
			break;
		}
		
	}

}

int	CScript::GetParts(char *pStr)
{
	if(strcmp(pStr,"MODELPARTS_WAIST") == 0)
	{
		return	MODELPARTS_WAIST;
	}
	else	if(strcmp(pStr,"MODELPARTS_BODY") == 0)
	{
		return	MODELPARTS_BODY;
	}
	else	if(strcmp(pStr,"MODELPARTS_NECK") == 0)
	{
		return	MODELPARTS_NECK;
	}
	else	if(strcmp(pStr,"MODELPARTS_HEAD") == 0)
	{
		return	MODELPARTS_HEAD;
	}
	else	if(strcmp(pStr,"MODELPARTS_RIGHTARM") == 0)
	{
		return	MODELPARTS_RIGHTARM;
	}
	else	if(strcmp(pStr,"MODELPARTS_RIGHTELBOW") == 0)
	{
		return	MODELPARTS_RIGHTELBOW;
	}
	else	if(strcmp(pStr,"MODELPARTS_RIGHTHAND") == 0)
	{
		return	MODELPARTS_RIGHTHAND;
	}
	else	if(strcmp(pStr,"MODELPARTS_LEFTARM") == 0)
	{
		return	MODELPARTS_LEFTARM;
	}
	else	if(strcmp(pStr,"MODELPARTS_LEFTELBOW") == 0)
	{
		return	MODELPARTS_LEFTELBOW;
	}
	else	if(strcmp(pStr,"MODELPARTS_LEFTHAND") == 0)
	{
		return	MODELPARTS_LEFTHAND;
	}
	else	if(strcmp(pStr,"MODELPARTS_RIGHTLEG") == 0)
	{
		return	MODELPARTS_RIGHTLEG;
	}
	else	if(strcmp(pStr,"MODELPARTS_RIGHTKNEE") == 0)
	{
		return	MODELPARTS_RIGHTKNEE;
	}
	else	if(strcmp(pStr,"MODELPARTS_RIGHTFOOT") == 0)
	{
		return	MODELPARTS_RIGHTFOOT;
	}
	else	if(strcmp(pStr,"MODELPARTS_LEFTLEG") == 0)
	{
		return	MODELPARTS_LEFTLEG;
	}
	else	if(strcmp(pStr,"MODELPARTS_LEFTKNEE") == 0)
	{
		return	MODELPARTS_LEFTKNEE;
	}
	else	if(strcmp(pStr,"MODELPARTS_LEFTFOOT") == 0)
	{
		return	MODELPARTS_LEFTFOOT;
	}

	return	-1;
}