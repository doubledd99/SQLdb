#include <iostream>
#include <string>
#include "sqlite3.h"
#include <stdio.h>

#include "SqlCommands.h"
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    cout << "WTF!";
    return 0;
}

int main(int argc, char* argv[]) {
  // sqlite3* db;
  // char* zErrMsg = 0;
  // int rc;
  const char *sql;
  //  rc = sqlite3_open("testdb.db", &db);

  //  if (rc) {
  //      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  //      return(0);
  //  }
  //  else {
  //      fprintf(stderr, "Opened database successfully\n");
  //  }
  //  //SqlCommands one;
  //// rc = one.openDB();
  // 
   sql = "INSERT OR REPLACE INTO INVENTORY (NAME,PRICE) "  \
        "VALUES ('Hawkeye', 14.56); " \
        "INSERT OR REPLACE INTO INVENTORY (NAME,PRICE) "  \
        "VALUES ('Black Velvet', 10); "     \
        "INSERT OR REPLACE INTO INVENTORY (NAME,PRICE)" \
        "VALUES ('Fireball', 22);" \
        "INSERT OR REPLACE INTO INVENTORY (NAME,PRICE)" \
        "VALUES ('Cherry MG', 12);";
  // rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  // if (rc != SQLITE_OK) {
  //     fprintf(stderr, "SQL error: %s\n", zErrMsg);
  //     sqlite3_free(zErrMsg);
  // }
  // else {
  //     fprintf(stdout, "Records created successfully\n");
  // }
	SqlCommands one;
	one.manualImput();
	one.openDB();
	one.sqlExec(one.returnDB(), sql);
    sqlite3_close(one.returnDB());
}