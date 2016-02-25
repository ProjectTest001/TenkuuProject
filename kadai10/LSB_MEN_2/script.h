//***************************************************************
//
//	script.h
//	name:Masatugu Kamada
//	create:2012/11/26
//	update:2012/11/26
//
//***************************************************************

#ifndef	SCRIPT_H_
#define	SCRIPT_H_

//*****************************************************
//	マクロ定義
//*****************************************************
#define	PLAYER_MOTION_DATA_FILE	("motionText/PlayerMotionScript.txt")		//モーションテキスト

//*****************************************************
//	構造体
//*****************************************************

//*****************************************************
//	クラス定義
//*****************************************************
//前方参照
class	CPlayer;

class	CScript
{
public:
	CScript();
	~CScript();

	static	void	LoadMotionScript(void);						//モーション情報の読み込み

	static	MOTIONDATA	*GetPlayerMotion(){return	m_pMotionPlayerData;}
private:
	static	MOTIONDATA	*m_pMotionPlayerData;

	static	void	SetData(FILE	*File,int	type,const	char	*end);
	static	int	GetParts(char	*pStr);
};

#endif