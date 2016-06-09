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
	int BufItem;						// ���� ������
	int DebufItem;						// ����� ������
	
	dataTime Time;						// �ð�
	

public:
	GameData();							// ������
	void initTime();					// ���� �ð� �ʱ�ȭ

	void setScore(int sc);				// ���� ����
	void setBufItem(int count);			// ���� ������ ����
	void setDebufItem(int count);		// ����� ������ ����
	

	int	getScore();						// ���� ����
	int getBufItem();					// ���� ������ ����
	int getDebufItem();					// ����� ������ ����
	dataTime getTime();					// ���� �ð� ����

};

#endif // __GAME_DATA_H__
