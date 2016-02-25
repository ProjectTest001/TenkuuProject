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
//	�}�N����`
//*****************************************************
#define	PLAYER_MOTION_DATA_FILE	("motionText/PlayerMotionScript.txt")		//���[�V�����e�L�X�g

//*****************************************************
//	�\����
//*****************************************************

//*****************************************************
//	�N���X��`
//*****************************************************
//�O���Q��
class	CPlayer;

class	CScript
{
public:
	CScript();
	~CScript();

	static	void	LoadMotionScript(void);						//���[�V�������̓ǂݍ���

	static	MOTIONDATA	*GetPlayerMotion(){return	m_pMotionPlayerData;}
private:
	static	MOTIONDATA	*m_pMotionPlayerData;

	static	void	SetData(FILE	*File,int	type,const	char	*end);
	static	int	GetParts(char	*pStr);
};

#endif