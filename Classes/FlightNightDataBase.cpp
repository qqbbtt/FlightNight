#include "FlightNightDataBase.h"

USING_NS_CC;

FlightNightDataBase FNDB; // ���� ������ ���

/*------------------------------------------------------------------------------------
| �� �� ��  : createDatabase()
| �Ű�����  : 
| �� �� ��  :
| ��    ��  : DB ����
|------------------------------------------------------------------------------------*/
void FlightNightDataBase::createDatabase()
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
| �� �� ��  : insertdData(int year, int month, int day, int hour, int min, int score, int buf, int debuf)
| �Ű�����  : year = ��, month = ��, day = ��, hour = ��, min = ��, score = ����, buf = ����, debuf = ����� 
| �� �� ��  :
| ��    ��  : ������ �Է�
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
| �� �� ��  : orderScore()
| �Ű�����  : 
| �� �� ��  : 
| ��    ��  : ������ ���� ����
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
| �� �� ��  : orderBuf()
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ������ ���� ������ ����
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
| �� �� ��  : orderDebuf()
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ������ ����� ������ ����
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
| �� �� ��  : orderDate()
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ������ ��¥ ����
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
| �� �� ��  : deleteDatabase()
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ��� ������ ����
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
| �� �� ��  : (*FlightNightDataBase::getFNDB())[8]
| �Ű�����  :
| �� �� ��  : int* = �迭 ������
| ��    ��  : �迭 ����
|------------------------------------------------------------------------------------*/
int (*FlightNightDataBase::getFNDB())[8]
{
	return arrFNDB;
}