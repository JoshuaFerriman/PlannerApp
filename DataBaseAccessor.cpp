#include "DataBaseAccessor.h"

DatabaseAccessor::DatabaseAccessor()
{
    StartDB("test");
}

DatabaseAccessor::DatabaseAccessor(std::string dbName)
{
    StartDB(dbName);
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

int DatabaseAccessor::StartDB(std::string dbName)
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
    return StartDB("test");

}

void DatabaseAccessor::CreateTable(Table table)
{
    /* Execute SQL statement */
    rc = sqlite3_exec(db, table.sqlCreateStatement.c_str(), callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Table created successfully\n");
   }
}

void DatabaseAccessor::TableINSERT(Table table, std::vector<std::string> sqlInsertStatements)
{
    /* Create SQL statement */
    std::string sqlStatement = "";
    for (std::string sqlInsertStatement : sqlInsertStatements)
    { 
        sqlStatement += table.sqlInsertStatement + sqlInsertStatement;
    }

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlStatement.c_str(), callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
}




void DatabaseAccessor::TableSELECT(char* sqlSelectStatement)
{
    const char* data = "Callback function called";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sqlSelectStatement, callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }
}

void DatabaseAccessor::TableSELECT(Table table)
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