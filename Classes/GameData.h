#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "cocos2d.h"

USING_NS_CC;

struct dataTime
{
	int Year;
	int Month;
	int Day;
	int Hour;
	int Min;
};

/*------------------------------------------------------------------------------------
| CLASS ��  : GameData
| ��    ��  : ���� ������
|------------------------------------------------------------------------------------*/
class GameData 
{
private:
	int Score;							// ����
	int BuffItem;						// ���� ������
	int DeBuffItem;						// ����� ������
	float	Level;						// ���� ����
	
	dataTime Time;						// �ð�
	

public:
	GameData();							// ������
	void initTime();					// ���� �ð� �ʱ�ȭ

	void setScore(int sc);				// ���� ����
	void setBuffItem(int count);		// ���� ������ ����
	void setDeBuffItem(int count);		// ����� ������ ����


	int	getScore();						// ���� ����
	int getBuffItem();					// ���� ������ ����
	int getDeBuffItem();				// ����� ������ ����
	dataTime getTime();					// ���� �ð� ����


	float getLevel();
	

	void setLevel(float lev);

};

#endif // __GAME_DATA_H__
