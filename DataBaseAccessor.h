#pragma once
#include <sqlite3/sqlite3.h>
#include <vector>
#include <string>

struct Field 
{
	std::string fieldName;
	std::string fieldType;

};

struct Table
{
	std::string tableName;

	std::vector<Field> fields;

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
	std::string dbName;

	//Functions
private:
	int StartDB();
	void CloseDB();
	static int callback(void* data, int argc, char** argv, char** azColName);

	



public:
	DatabaseAccessor();
	DatabaseAccessor(const std::string& dbName);
	~DatabaseAccessor();
	int ReloadDB();

	void CreateTable(const Table& table);
	void TableINSERT(const Table& table, std::vector<std::string>& fieldValues);
	void TableSELECT(char* sqlSelectStatement);
	void TableSELECT(const Table& table);
	void TableUPDATE(char* sqlUpdateStatement);
	void TableDELETE(char* sqlDeleteStatement);
};

