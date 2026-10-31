#include <sqlite3.h>
#include <iostream>

#ifndef LOG_HPP
#define LOG_HPP
namespace DatabaseLogging
{
    void initDatabase();
    void logCheckSum(std::string origin_file_path, std::string file_checksum);
}

#endif