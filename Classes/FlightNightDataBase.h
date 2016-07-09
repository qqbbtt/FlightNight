#ifndef __FLIGHTNIGHT_DATABASE_H__
#define __FLIGHTNIGHT_DATABASE_H__

#include "cocos2d.h"
#include "sqlite3.h"

USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS 명  : FlightNightDataBase
| 설    명  : 게임 DB
|------------------------------------------------------------------------------------*/
class FlightNightDataBase 
{
private:
	string dbfileName;
	int arrFNDB[5][8];												// 정렬 된 데이터 저장
	
public:
//	void init();
	void createDatabase();											// DB 생성
	void insertdData(int year, int month, int day,
		int hour, int min, int score, int buf, int debuf);			// 데이터 입력

	void deleteDatabase();											// 모든 데이터 삭제

	void orderDate();												// 데이터 날짜 정렬
	void orderScore();												// 데이터 점수 정렬
	void orderBuf();												// 데이터 버프 아이템 정렬
	void orderDebuf();												// 데이터 디버프 아이템 정렬

	int (*getFNDB())[8];											// 배열 리턴


};

extern FlightNightDataBase FNDB;

#endif // __FLIGHTNIGHT_DATABASE_H__
