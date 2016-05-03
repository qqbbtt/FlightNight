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
	int BuffItem;						// 버프 아이템
	int DeBuffItem;						// 디버프 아이템
	float	Level;						// 게임 레벨
	
	dataTime Time;						// 시간
	

public:
	GameData();							// 생성자
	void initTime();					// 현재 시간 초기화

	void setScore(int sc);				// 점수 셋팅
	void setBuffItem(int count);		// 버프 아이템 셋팅
	void setDeBuffItem(int count);		// 디버프 아이템 셋팅


	int	getScore();						// 점수 리턴
	int getBuffItem();					// 버프 아이템 리턴
	int getDeBuffItem();				// 디버프 아이템 리턴
	dataTime getTime();					// 현재 시간 리턴


	float getLevel();
	

	void setLevel(float lev);

};

#endif // __GAME_DATA_H__
