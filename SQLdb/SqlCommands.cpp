#include "SqlCommands.h"
using namespace std;
#include <iostream>
#include <string>
#include <vector>

SqlCommands::SqlCommands() {

}
SqlCommands::~SqlCommands() {

}
string SqlCommands::manualImput()
								//Pre condition: insertWrapper() has run
								//Post condition: string of correct sqlite format is passed along
{	//input = temp.c_str();
	bool keepGoing = 1;
	string SQLstring;
	string temp;
	temp = "h";
	for (int i = 0; keepGoing && i <= 4; i++) {
		switch (i)
		{
		case 0:
			SQLstring += "INSERT OR REPLACE INTO INVENTORY (NAME,PRICE,SIZE,TYPE,QUANTITY) VALUES ('";
			cout << "Enter an item's name: \n";
			cin.ignore(40, '\n');
			getline(cin, temp);
			cout << temp << endl;
			SQLstring += temp;
			break;
		case 1:
			SQLstring += "', ";
			cout << "Enter an item's price: \n";
			cin >> temp;
			SQLstring += temp;
			SQLstring += ", ";
			break;
		case 2: 
			cout << "Enter the Size of the bottle: \n";
			cin >> temp;
			SQLstring += temp;
			SQLstring += ", '";
			break;
		case 3: 
			cout << "Enter the type of the item (WHISKEY, FOOD, etc): \n";
			cin >> temp;
			SQLstring += temp;
			SQLstring += "', ";
			break;
		case 4:
			cout << "Enter a starting quantity for the item: \n";
			cin >> temp;
			SQLstring += temp;
			SQLstring += "); ";
		default:
			cout << "done \n";
			break;
		}
		//if (i >= 1) {
		//}
		
	}			
	
	cout << endl << SQLstring;
	return SQLstring;
}
int SqlCommands::returnInt() //Pre: openDB() has run
							//Post: contents of the DB is printed to screen
	//						Not working btw
{
	sqlite3_stmt* stmt;
	/*vector<string> name;
	vector<float> price;
	vector<int> quantity;
	vector<string> location;*/

	std::vector< std::vector < std::string > > result;
	for (int i = 0; i < 4; i++)
		result.push_back(std::vector< std::string >());


	sqlite3_prepare(db, "SELECT * from INVENTORY;", -1, &stmt, NULL);//preparing the statement
	while (sqlite3_column_text(stmt, 0))
	{
		for (int i = 0; i < 4; i++)
			result[i].push_back(std::string((char*)sqlite3_column_text(stmt, i)));
		sqlite3_step(stmt);
	}
	//sqlite3_step(stmt);//executing the statement
	char* str = (char*)sqlite3_column_text(stmt, 0);///reading the 1st column of the result


	sqlite3_finalize(stmt);
	sqlite3_close(db);

	//cout << str << endl;
	return 0;
}
int SqlCommands::callBack(void* NotUsed, int argc, char** argv, char** azColName) //Pre: none
																				//  Post: error message is handled
{
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	cout << "WTF!";
	return 0;
}
//static int calBack(void* NotUsed, int argc, char** argv, char** azColName) {
//    int i;
//    for (i = 0; i < argc; i++) {
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    printf("\n");
//    return 0;
//}

int SqlCommands::openDB() {//Pre: none
							//Post: 'connection'string is opened and DB is available to be manipulated/read
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

bool SqlCommands::sqlExec(sqlite3* DB, const char* syntax) //Pre: openDB() has run
															//Post: the sqlite command has been sent to the DB to be executed
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
		fprintf(stdout, "Record(s) modified successfully\n");
		return 0;
	}
}

sqlite3* SqlCommands::returnDB() //Pre: openDB has run
									//Post: returns DB object
{
	return db;
}

void SqlCommands::displayMenu()	//Pre: none
								//post: the correct method is called based on user input
{
	cout <<"\n===================================\nPress a corresponding number below: " \
		"\n/////////////////////////"<<endl << \
		"/1.Insert	2.Delete/" << endl <<
		"/3.Display	4.Modify/ \n" \
		"/5.Search	6.Exit  /"<<endl<< \
		"/////////////////////////\n";
	int num = 0;
	cin >> num;
	switch (num)
	{
	case 1: insertWrapper();
		break;
	case 2: deleteitem();
		break;
	case 3: cout << "\nThis function/method does not work\n";
		Display();
		break;
	case 4: insertWrapper();
		break;
	case 5: cout << "\nthis function/method relies on display function, which isn't working\n";
		break;
	default:
		return;
		break;
	}
}

void SqlCommands::deleteitem()	//pre: openDB() has run
								//post: an item has been deleted from the DB 
{
	string item;
	cout << "\nEnter the name of an item to be deleted: \n";
	cin >> item;
	string tempInput = "DELETE FROM INVENTORY WHERE NAME = '";
	tempInput += item;
	tempInput += "' COLLATE NOCASE; ";
	cout << tempInput << endl;
	const char* input = tempInput.c_str();
	sqlExec(returnDB(), input);
}
void SqlCommands::insertWrapper() {
	string inputString = manualImput();
	const char* input = inputString.c_str();
	sqlExec(db, input);
}

void SqlCommands::Display() //wrapper for returnInt()
{
	returnInt();
}

bool SqlCommands::keepGoing()//pre: none
							//post: program exits or loops through similar to a game loop
{
	cout << "\nWould you like to exit?\nPress 1 to continue\n";
	int num;
	cin >> num;
	if (num == 1)
		return true;
	else
		return false;
}
