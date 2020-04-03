#ifndef SqlCommands_h
#define SqlCommands_h

#include "sqlite3.h"
#include <stdio.h>


using namespace std;

class SqlCommands {

public:
	SqlCommands();
	~SqlCommands();
	static int callBack(void* NotUsed, int argc, char** argv, char** azColName);
	int openDB();
	bool sqlExec(sqlite3* db, const char* syntax, static int callback, char* zErrMsg);
private:
	const char* filename;
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
};
#endif