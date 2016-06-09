#include "FlightNightDataBase.h"

USING_NS_CC;

FlightNightDataBase FNDB; // 전역 변수로 등록

/*------------------------------------------------------------------------------------
| 함 수 명  : createDatabase()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : DB 생성
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::createDatabase()
{
	sqlite3* pDB = NULL;
	char* errMsg;
	int result;

	// DB 이름 지정
	dbfileName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	dbfileName = dbfileName + "save.db3";

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("createDatabase Open Error1 : Code:%d Msg : %s", result, errMsg);
	}

	string sqlStr;
	sqlStr = "create table IF NOT EXISTS FlightNight(year, month, day, hour, min, score, buffItem, deBuffItem)";

	result = sqlite3_exec(pDB, sqlStr.c_str(), NULL, NULL,&errMsg);

	if (result != SQLITE_OK)
	{
		CCLOG("createDatabase Open Error2 : Code:%d Msg : %s", result, errMsg);
	}

	CCLOG("here");

	sqlite3_close(pDB);


}

/*------------------------------------------------------------------------------------
| 함 수 명  : insertdData(int year, int month, int day, int hour, int min, int score, int buf, int debuf)
| 매개변수  : year = 년, month = 월, day = 일, hour = 시, min = 분, score = 점수, buf = 버프, debuf = 디버프 
| 리 턴 값  :
| 설    명  : 데이터 입력
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::insertdData(int year, int month, int day, int hour, int min, int score, int buf, int debuf)
{
	sqlite3* pDB = NULL;
	char *errMsg;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("insertdData Open Error1 : Code:%d Msg : %s", result, errMsg);
	}

	char sqlStr[256];
//	sqlStr = "insert into FlightNight values(" + year + "," + month + "," + day + "," + hour + "," + min + "," + score + "," + buf + "," + debuf + ")";
	sprintf(sqlStr, "insert into FlightNight values(%d,%d,%d,%d,%d,%d,%d,%d)", year, month, day, hour, min, score, buf, debuf);
	result = sqlite3_exec(pDB, sqlStr, NULL, NULL, &errMsg);

	if (result != SQLITE_OK)
	{
		CCLOG("insertdData Open Error2 : Code:%d Msg : %s", result, errMsg);
	}


	sqlite3_close(pDB);

	selectData();

}

/*------------------------------------------------------------------------------------
| 함 수 명  : selectData()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : 입력된 데이터 확인 출력
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::selectData()
{
	sqlite3* pDB = NULL;
	char *errMsg;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("selectData Open Error : Code:%d Msg : %s", result, errMsg);
	}

	string sqlStr;
	sqlStr = "select year, month, day, hour, min, score, buffItem, deBuffItem from FlightNight order by score DESC";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK)
	{
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int row1 = sqlite3_column_int(statement, 0);
			int row2 = sqlite3_column_int(statement, 1);
			int row3 = sqlite3_column_int(statement, 2);
			int row4 = sqlite3_column_int(statement, 3);
			int row5 = sqlite3_column_int(statement, 4);
			int row6 = sqlite3_column_int(statement, 5);
			int row7 = sqlite3_column_int(statement, 6);
			int row8 = sqlite3_column_int(statement, 7);

			CCLOG("%d | %d | %d | %d | %d | %d | %d | %d | ", row1, row2, row3, row4, row5, row6, row7, row8);		
		}
	}

	sqlite3_finalize(statement);

	sqlite3_close(pDB);
}

