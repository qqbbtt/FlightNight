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
	
public:
//	void init();
	void createDatabase();											// DB 생성
	void insertdData(int year, int month, int day,
		int hour, int min, int score, int buf, int debuf);			// 데이터 입력
	void selectData();												// 입력된 데이터 확인 출력


};

extern FlightNightDataBase FNDB;

#endif // __FLIGHTNIGHT_DATABASE_H__
