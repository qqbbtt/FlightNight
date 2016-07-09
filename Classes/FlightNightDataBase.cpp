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

	orderDate();

}

/*------------------------------------------------------------------------------------
| 함 수 명  : orderScore()
| 매개변수  : 
| 리 턴 값  : 
| 설    명  : 데이터 점수 정렬
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::orderScore()
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
		int i = 0;

		while (sqlite3_step(statement) == SQLITE_ROW && i < 5 )
		{
			arrFNDB[i][0] = sqlite3_column_int(statement, 0) % 2000;
			arrFNDB[i][1] = sqlite3_column_int(statement, 1);
			arrFNDB[i][2] = sqlite3_column_int(statement, 2);
			arrFNDB[i][3] = sqlite3_column_int(statement, 3);
			arrFNDB[i][4] = sqlite3_column_int(statement, 4);
			arrFNDB[i][5] = sqlite3_column_int(statement, 5);
			arrFNDB[i][6] = sqlite3_column_int(statement, 6);
			arrFNDB[i][7] = sqlite3_column_int(statement, 7);

//			CCLOG("%d | %d | %d | %d | %d | %d | %d | %d | ", arrFNDB[i][0], arrFNDB[i][1], arrFNDB[i][2], arrFNDB[i][3], arrFNDB[i][4], arrFNDB[i][5], arrFNDB[i][6], arrFNDB[i][7]);

			i++;
		}
	}

	sqlite3_finalize(statement);

	sqlite3_close(pDB);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : orderBuf()
| 매개변수  :
| 리 턴 값  :
| 설    명  : 데이터 버프 아이템 정렬
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::orderBuf()
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
	sqlStr = "select year, month, day, hour, min, score, buffItem, deBuffItem from FlightNight order by buffItem DESC";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK)
	{
		int i = 0;

		while (sqlite3_step(statement) == SQLITE_ROW && i < 5)
		{
			arrFNDB[i][0] = sqlite3_column_int(statement, 0) % 2000;
			arrFNDB[i][1] = sqlite3_column_int(statement, 1);
			arrFNDB[i][2] = sqlite3_column_int(statement, 2);
			arrFNDB[i][3] = sqlite3_column_int(statement, 3);
			arrFNDB[i][4] = sqlite3_column_int(statement, 4);
			arrFNDB[i][5] = sqlite3_column_int(statement, 5);
			arrFNDB[i][6] = sqlite3_column_int(statement, 6);
			arrFNDB[i][7] = sqlite3_column_int(statement, 7);

//			CCLOG("%d | %d | %d | %d | %d | %d | %d | %d | ", arrFNDB[i][0], arrFNDB[i][1], arrFNDB[i][2], arrFNDB[i][3], arrFNDB[i][4], arrFNDB[i][5], arrFNDB[i][6], arrFNDB[i][7]);

			i++;
		}
	}

	sqlite3_finalize(statement);

	sqlite3_close(pDB);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : orderDebuf()
| 매개변수  :
| 리 턴 값  :
| 설    명  : 데이터 디버프 아이템 정렬
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::orderDebuf()
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
	sqlStr = "select year, month, day, hour, min, score, buffItem, deBuffItem from FlightNight order by deBuffItem DESC";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK)
	{
		int i = 0;

		while (sqlite3_step(statement) == SQLITE_ROW && i < 5)
		{
			arrFNDB[i][0] = sqlite3_column_int(statement, 0) % 2000;
			arrFNDB[i][1] = sqlite3_column_int(statement, 1);
			arrFNDB[i][2] = sqlite3_column_int(statement, 2);
			arrFNDB[i][3] = sqlite3_column_int(statement, 3);
			arrFNDB[i][4] = sqlite3_column_int(statement, 4);
			arrFNDB[i][5] = sqlite3_column_int(statement, 5);
			arrFNDB[i][6] = sqlite3_column_int(statement, 6);
			arrFNDB[i][7] = sqlite3_column_int(statement, 7);

//			CCLOG("%d | %d | %d | %d | %d | %d | %d | %d | ", arrFNDB[i][0], arrFNDB[i][1], arrFNDB[i][2], arrFNDB[i][3], arrFNDB[i][4], arrFNDB[i][5], arrFNDB[i][6], arrFNDB[i][7]);

			i++;
		}
	}

	sqlite3_finalize(statement);

	sqlite3_close(pDB);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : orderDate()
| 매개변수  :
| 리 턴 값  :
| 설    명  : 데이터 날짜 정렬
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::orderDate()
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
	sqlStr = "select year, month, day, hour, min, score, buffItem, deBuffItem from FlightNight order by year DESC, month DESC, day DESC, hour DESC, min DESC";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK)
	{
		int i = 0;

		while (sqlite3_step(statement) == SQLITE_ROW && i < 5)
		{
			arrFNDB[i][0] = sqlite3_column_int(statement, 0) % 2000;
			arrFNDB[i][1] = sqlite3_column_int(statement, 1);
			arrFNDB[i][2] = sqlite3_column_int(statement, 2);
			arrFNDB[i][3] = sqlite3_column_int(statement, 3);
			arrFNDB[i][4] = sqlite3_column_int(statement, 4);
			arrFNDB[i][5] = sqlite3_column_int(statement, 5);
			arrFNDB[i][6] = sqlite3_column_int(statement, 6);
			arrFNDB[i][7] = sqlite3_column_int(statement, 7);

//			CCLOG("%d | %d | %d | %d | %d | %d | %d | %d | ", arrFNDB[i][0], arrFNDB[i][1], arrFNDB[i][2], arrFNDB[i][3], arrFNDB[i][4], arrFNDB[i][5], arrFNDB[i][6], arrFNDB[i][7]);

			i++;
		}
	}

	sqlite3_finalize(statement);

	sqlite3_close(pDB);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : deleteDatabase()
| 매개변수  :
| 리 턴 값  :
| 설    명  : 모든 데이터 삭제
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::deleteDatabase()
{
	sqlite3* pDB = NULL;
	char *errMsg;
	int result;

	result = sqlite3_open(dbfileName.c_str(), &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("deleteDatabase Open Error : Code:%d Msg : %s", result, errMsg);
	}

	string sqlStr;
	sqlStr = "delete from FlightNight where year > 2000";
	result = sqlite3_exec(pDB, sqlStr.c_str(), NULL, NULL, &errMsg);

	if (result != SQLITE_OK)
	{
		CCLOG("deleteDatabase Open Error2 : Code:%d Msg : %s", result, errMsg);
	}

	sqlite3_close(pDB);

	arrFNDB[5][8] = { 0, };

}

/*------------------------------------------------------------------------------------
| 함 수 명  : (*FlightNightDataBase::getFNDB())[8]
| 매개변수  :
| 리 턴 값  : int* = 배열 포인터
| 설    명  : 배열 리턴
|------------------------------------------------------------------------------------*/
int (*FlightNightDataBase::getFNDB())[8]
{
	return arrFNDB;
}