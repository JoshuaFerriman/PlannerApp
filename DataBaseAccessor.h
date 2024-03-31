#pragma once
#include <sqlite3/sqlite3.h>
#include <vector>
#include <string>



struct Field
{
	std::string fieldName;
	std::string fieldType;
	std::vector<std::string> constraints = {};

};

struct Table
{
	std::string tableName;

	std::vector<Field> fields;

	std::string sqlSelectStatement;
};

static std::vector<std::vector<std::string>> resultSet;

class DatabaseAccessor
{
	//Fields
private:
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

public:
	
	std::string dbName;

	//Functions
private:
	int StartDB();
	void CloseDB();
	static int callback(void* data, int argc, char** argv, char** azColName);
	static int callbackGetData(void* data, int argc, char** argv, char** azColName);

	



public:
	DatabaseAccessor();
	DatabaseAccessor(const std::string& dbName);
	~DatabaseAccessor();
	int ReloadDB();

	void CreateTable(const Table& table);

	void TableINSERT(const Table& table, std::vector<std::string>& fieldValues);

	std::vector<std::vector<std::string>> TableSELECTWhere(char* sqlSelectStatement);
	void TableSELECTAll(const Table& table);

	void TableUPDATE(char* sqlUpdateStatement);

	void TableDELETE(char* sqlDeleteStatement);
};

