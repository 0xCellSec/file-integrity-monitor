#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#ifndef LOG_HPP
#define LOG_HPP
namespace DatabaseLogging
{
    struct Files;
    using file_map = std::unordered_map<int, std::vector<Files>>;

    file_map fetchFileDataMap(sqlite3* database, const char* database_path);
    void initDatabase(sqlite3* database, const char* database_path);
    void logCheckSum(sqlite3* database, const char* database_path, std::string origin_file_path, std::string file_checksum);
    bool monitorFiles(sqlite3* database, const char* database_path);
}

#endif