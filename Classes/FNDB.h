#ifndef __FN_DB_H__
#define __FN_DB_H__

#include "cocos2d.h"
#include "sqlite3.h"

USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS 명  : FNDB
| 설    명  : 게임 DB
|------------------------------------------------------------------------------------*/
class FNDB 
{
private:
	string dbfileName;
	
public:
//	void init();
	void createDatabase();		// DB 생성
	void insetdData();			// 데이터 입력

};

#endif // __FN_DB_H__
