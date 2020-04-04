#include "SqlCommands.h"
using namespace std;
#include <iostream>

SqlCommands::SqlCommands() {

}
SqlCommands::~SqlCommands() {

}
int SqlCommands::callBack(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	cout << "WTF!";
	return 0;
}
static int callBack(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int SqlCommands::openDB() {
    zErrMsg = 0;
    rc = sqlite3_open("testdb.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
        return rc;
    }
}

bool SqlCommands::sqlExec(sqlite3* DB, const char* syntax)
{
	rc = sqlite3_exec(db, syntax, callBack, 0, &zErrMsg);
	if (rc == SQLITE_OK)
		cout << "success bro \n";
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}
	else {
		fprintf(stdout, "Records created successfully\n");
		return 0;
	}
}

sqlite3* SqlCommands::returnDB()
{
	return db;
}