#ifndef __FN_DB_H__
#define __FN_DB_H__

#include "cocos2d.h"
#include "sqlite3.h"

USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS ��  : FNDB
| ��    ��  : ���� DB
|------------------------------------------------------------------------------------*/
class FNDB 
{
private:
	string dbfileName;
	
public:
//	void init();
	void createDatabase();		// DB ����
	void insetdData();			// ������ �Է�

};

#endif // __FN_DB_H__
