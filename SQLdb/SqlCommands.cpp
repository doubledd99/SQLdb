#include "SqlCommands.h"


SqlCommands::SqlCommands() {

}
SqlCommands::~SqlCommands() {

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
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
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

bool SqlCommands::sqlExec(sqlite3* db, const char* syntax, int callback, char* zErrMsg)
{
    static int i = callBack();
    rc = sqlite3_exec(db, syntax, int i = callBack() , 0, &zErrMsg);
}
