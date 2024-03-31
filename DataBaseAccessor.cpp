#include "DataBaseAccessor.h"
#include <iostream>

DatabaseAccessor::DatabaseAccessor()
{
    DatabaseAccessor::dbName = "test";
    StartDB();
}

DatabaseAccessor::DatabaseAccessor(const std::string& dbName)
{
    DatabaseAccessor::dbName = dbName;
    StartDB();
}

DatabaseAccessor::~DatabaseAccessor()
{
    CloseDB();
}



int DatabaseAccessor::callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int DatabaseAccessor::callbackGetData(void* data, int argc, char** argv, char** azColName) {
    
    std::vector<std::string> rowValues;

    for (int i = 0; i < argc; ++i)
    {
        std::string columnValue = argv[i] ? argv[i] : "";
        rowValues.push_back(columnValue);
    }

    resultSet.push_back(rowValues);
    return 0;
}


int DatabaseAccessor::StartDB()
{
   /* Open database */
   rc = sqlite3_open((dbName + ".db").data(), &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
      return(0);
   }

}

void DatabaseAccessor::CloseDB()
{
    sqlite3_close(db);
}


int DatabaseAccessor::ReloadDB()
{
    CloseDB();
    return StartDB();

}

void DatabaseAccessor::CreateTable(const Table& table)
{
    /* Execute SQL statement */

    std::string sqlCreateStatement = "CREATE TABLE " + table.tableName + " (\n";
    for (size_t i = 0; i < table.fields.size(); ++i)
    {
        sqlCreateStatement += "\t" + table.fields[i].fieldName + " " + table.fields[i].fieldType;
        if (table.fields[i].constraints.size() != 0) // Add constraints to the statement if the constraints vector is not empty
        {
            for (std::string constraint : table.fields[i].constraints)
            {
                sqlCreateStatement += constraint;
            }
        }
        if (i != table.fields.size() - 1)  // Check if it is not the last field
            sqlCreateStatement += ",\n";
    }
    sqlCreateStatement += "\n);";

    rc = sqlite3_exec(db, sqlCreateStatement.c_str(), callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else 
    {
        fprintf(stdout, "Table created successfully\n");
    }
}

void DatabaseAccessor::TableINSERT(const Table& table, std::vector<std::string>& fieldValues)
{
    std::string insertStatement = "INSERT INTO " + table.tableName + " (";
    std::string valuesStatement = "VALUES (";

    // Build the INSERT and VALUES statements
    for (size_t i = 0; i < table.fields.size(); ++i)
    {
        insertStatement += table.fields[i].fieldName;
        valuesStatement += "?";

        if (i != table.fields.size() - 1)
        {
            insertStatement += ", ";
            valuesStatement += ", ";
        }
    }

    insertStatement += ") " + valuesStatement + ");";

    // Prepare the INSERT statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, insertStatement.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind the field values to the prepared statement
    for (size_t i = 0; i < table.fields.size(); ++i)
    {
        rc = sqlite3_bind_text(stmt, i + 1, fieldValues[i].c_str(), -1, SQLITE_STATIC);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to bind value: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
    }

    // Execute the INSERT statement
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }
    else
    {
        std::cout << "Record inserted successfully!" << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);

}

std::vector<std::vector<std::string>> DatabaseAccessor::TableSELECTWhere(char* sqlSelectStatement)
{
    std::vector<std::vector<std::string>> tempResultSet;
    const char* data = "Callback function called ";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sqlSelectStatement, callbackGetData, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        resultSet.clear();
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
        tempResultSet = resultSet;
        resultSet.clear();
    }
    return tempResultSet;
}


void DatabaseAccessor::TableSELECTAll(const Table& table)
{
    const char* data = "Callback function called";
    std::string sqlSelectStatement = "SELECT * from " + table.tableName;


    /* Execute SQL statement */
    rc = sqlite3_exec(db, sqlSelectStatement.c_str(), callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }
}

void DatabaseAccessor::TableUPDATE(char* sqlUpdateStatement)
{
    const char* data = "Callback function called";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlUpdateStatement, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
}

void DatabaseAccessor::TableDELETE(char* sqlDeleteStatement)
{
    const char* data = "Callback function called";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sqlDeleteStatement, callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }

}