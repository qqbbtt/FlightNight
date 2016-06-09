#ifndef __FLIGHTNIGHT_DATABASE_H__
#define __FLIGHTNIGHT_DATABASE_H__

#include "cocos2d.h"
#include "sqlite3.h"

USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS ��  : FlightNightDataBase
| ��    ��  : ���� DB
|------------------------------------------------------------------------------------*/
class FlightNightDataBase 
{
private:
	string dbfileName;
	
public:
//	void init();
	void createDatabase();											// DB ����
	void insertdData(int year, int month, int day,
		int hour, int min, int score, int buf, int debuf);			// ������ �Է�
	void selectData();												// �Էµ� ������ Ȯ�� ���


};

extern FlightNightDataBase FNDB;

#endif // __FLIGHTNIGHT_DATABASE_H__
