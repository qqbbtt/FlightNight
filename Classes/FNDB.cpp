#include "FNDB.h"

USING_NS_CC;


/*------------------------------------------------------------------------------------
| �� �� ��  : createDatabase()
| �Ű�����  : 
| �� �� ��  :
| ��    ��  : DB ����
|------------------------------------------------------------------------------------*/
void FNDB::createDatabase()
{
	sqlite3* pDB = NULL;
	char* errMsg;
	int result;

	// DB �̸� ����
	dbfileName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	dbfileName = dbfileName + "save.db3";

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("Open Error1 : Code:%d Msg : %s", result, errMsg);
	}

	string sqlStr;
	sqlStr = "create table IF NOT EXISTS FlightNight(\Date, \Score, \BuffItem)";

	result = sqlite3_exec(pDB, sqlStr.c_str(), NULL, NULL,&errMsg);

	if (result != SQLITE_OK)
	{
		CCLOG("Open Error2 : Code:%d Msg : %s", result, errMsg);
	}

	sqlite3_close(pDB);

	insetdData();
}

/*------------------------------------------------------------------------------------
| �� �� ��  : insetdData()
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ������ �Է�
|------------------------------------------------------------------------------------*/
void FNDB::insetdData()
{
	sqlite3* pDB = NULL;
	char *errMsg;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("Open Error : Code:%d Msg : %s", result, errMsg);
	}

	string sqlStr;
	sqlStr = "insert into FlightNight(Date, Score, BuffItem) values('2016.4.5', '500', '5')";

	result = sqlite3_exec(pDB, sqlStr.c_str(), NULL, NULL, &errMsg);

	if (result != SQLITE_OK)
	{
		CCLOG("Open Error2 : Code:%d Msg : %s", result, errMsg);
	}

	sqlite3_close(pDB);

}

