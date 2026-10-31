#include "log.hpp"

#include <sqlite3.h>
#include <iostream> 


void DatabaseLogging::initDatabase(sqlite3* database, const char* database_path)
{

    const std::string SCHEMA = R"schema(
    CREATE TABLE IF NOT EXISTS monitored_files (
        id              INTEGER PRIMARY KEY AUTOINCREMENT,
        file_path       TEXT NOT NULL UNIQUE,
        file_hash       TEXT NOT NULL,
        last_modified   DATETIME, 
        last_checked    DATETIME DEFAULT CURRENT_TIMESTAMP 
    );

    CREATE INDEX IF NOT EXISTS idx_file_path ON monitored_files(file_path);
    )schema";

    int exit = sqlite3_open(database_path, &database);
    char * messsageError;

    exit = sqlite3_exec(database, SCHEMA.c_str(), NULL, 0, &messsageError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Creating Table" << std::endl;
        sqlite3_free(messsageError);
    }
    else
    {
        std::cout << "Table Created Successfully" << std::endl;
        sqlite3_close(database);
        return;
    }
    return;
}

void DatabaseLogging::logCheckSum(sqlite3* database, const char* database_path, std::string origin_file_path, std::string file_checksum)
{
    const std::string LOG = R"log(
    INSERT INTO monitored_files (file_path, file_hash) VALUES (? , ?)
    )log";

    int exit = sqlite3_open(database_path, &database);
    char * messsageError;
    sqlite3_stmt* statement;

    int prepare = sqlite3_prepare_v2(database, LOG.c_str(), -1, &statement, NULL);

    if (prepare != SQLITE_OK) 
    {
        std::cerr << "ERROR: " << sqlite3_errmsg(database) << std::endl;
        sqlite3_close(database);
        return; 
    }


    sqlite3_bind_text(statement, 1, origin_file_path.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, file_checksum.c_str(), -1, SQLITE_TRANSIENT); 
     
    prepare = sqlite3_step(statement);

    if (prepare != SQLITE_DONE)
    {
        std::cerr << "EXECUTION ERROR: " << sqlite3_errmsg(database) << std::endl;
    }
    
    sqlite3_finalize(statement);
    sqlite3_close(database);
    return;
}