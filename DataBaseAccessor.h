#pragma once
#include <sqlite3/sqlite3.h>
#include <vector>
#include <string>

struct Table
{
	std::string tableName;
	std::string sqlCreateStatement;
	std::string sqlInsertStatement;
	std::string sqlSelectStatement;
};


class DatabaseAccessor
{
	//Fields
private:
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

public:

	//Functions
private:
	int StartDB();
	void CloseDB();
	static int callback(void* data, int argc, char** argv, char** azColName);

	



public:
	DatabaseAccessor();
	~DatabaseAccessor();
	int ReloadDB();

	void CreateTable(Table table);
	void TableINSERT(Table table, std::vector<std::string> sqlInsertStatements);
	void TableSELECT(char* sqlSelectStatement);
	void TableSELECT(Table table);
	void TableUPDATE(char* sqlUpdateStatement);
	void TableDELETE(char* sqlDeleteStatement);
};

