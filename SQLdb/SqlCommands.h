#ifndef SqlCommands_h
#define SqlCommands_h

#include "sqlite3.h"
#include <stdio.h>
#include <string>

using namespace std;

class SqlCommands {

public:
	SqlCommands();
	~SqlCommands();
	string manualImput(); //walks the user through inputting all info necessary to insert new entry into database
	int openDB(); //"opens" the database so it can be communicated with
	bool sqlExec(sqlite3* DB, const char* syntax); //used once DB is open to send a query to the database
	sqlite3* returnDB(); //returns pointer of type sqlite3 object
	void displayMenu(); //prints a menu letting user pick what to do
	void deleteitem();//deletes an item from the sqlite DB
	void insertWrapper();//wrapper for insert function
	void Display();//prints out contents of DB to screen
	bool keepGoing();//asks user if they would like to keep going
private:
	int returnInt(); //was going to print contents of DB to screen
	static int callBack(void* NotUsed, int argc, char** argv, char** azColName);//handles errors
	const char* filename; //keeps track of the location of the file
	sqlite3* db; //object that 'is' the database
	char* zErrMsg = 0; //saves info on errors
	int rc; //integer used by sqlite3.h to do stuff
	const char* sql; //used for inputting info into correct format for sqlite
};
#endif