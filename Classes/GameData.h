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
| CLASS 명  : GameData
| 설    명  : 게임 데이터
|------------------------------------------------------------------------------------*/
class GameData 
{
private:
	int Score;							// 점수
	int BufItem;						// 버프 아이템
	int DebufItem;						// 디버프 아이템
	
	dataTime Time;						// 시간
	

public:
	GameData();							// 생성자
	void initTime();					// 현재 시간 초기화

	void setScore(int sc);				// 점수 셋팅
	void setBufItem(int count);			// 버프 아이템 셋팅
	void setDebufItem(int count);		// 디버프 아이템 셋팅
	

	int	getScore();						// 점수 리턴
	int getBufItem();					// 버프 아이템 리턴
	int getDebufItem();					// 디버프 아이템 리턴
	dataTime getTime();					// 현재 시간 리턴

};

#endif // __GAME_DATA_H__
