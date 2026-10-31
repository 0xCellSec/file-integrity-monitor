#include <sqlite3.h>
#include <iostream>

#ifndef LOG_HPP
#define LOG_HPP
namespace DatabaseLogging
{
    void initDatabase(sqlite3* database, const char* database_path);
    void logCheckSum(sqlite3* database, const char* database_path, std::string origin_file_path, std::string file_checksum);
}

#endif