#ifndef SqlCommands_h
#define SqlCommands_h

#include "sqlite3.h"
#include <stdio.h>


using namespace std;

class SqlCommands {

public:
	SqlCommands();
	~SqlCommands();
	
	int openDB();
	bool sqlExec(sqlite3* DB, const char* syntax);
	sqlite3* returnDB();
private:
	static int callBack(void* NotUsed, int argc, char** argv, char** azColName);
	const char* filename;
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
};
#endif