#include "SqlCommands.h"
using namespace std;
#include <iostream>
#include <string>

SqlCommands::SqlCommands() {

}
SqlCommands::~SqlCommands() {

}
const char* SqlCommands::manualImput()
{	//input = temp.c_str();
	bool keepGoing = 1;
	const char* input = "0";
	string SQLstring;
	string temp;
	temp = "h";
	for (int i = 0; keepGoing && i <= 1; i++) {
		switch (i)
		{
		case 0:
			SQLstring += "INSERT OR REPLACE INTO INVENTORY(NAME, PRICE) "  \
				"VALUES('";
			cout << "Enter an item's name: \n";
			cin >> temp;
			cout << endl;
			SQLstring += temp;
			break;
		case 1:
			SQLstring += "',";
			cout << "Enter an item's price: \n";
			cin >> temp;
			SQLstring += temp;
			SQLstring += ");";
			break;

		default:
			cout << "ERROR \n";
			break;
		}
		//if (i >= 1) {
			input = SQLstring.c_str();
		//}
		
	}
	return input;
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