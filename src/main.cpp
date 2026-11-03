#include "hash.hpp"
#include "log.hpp"
#include "file_changer.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

int main() 
{
    sqlite3* database;
    const char* database_path = "database.db";

    const std::string folder_iterable = "test";
    DatabaseLogging::initDatabase(database, database_path);
    std::this_thread::sleep_for(2000ms);

    for (const auto& entry : std::filesystem::directory_iterator(folder_iterable))
    {   
        auto absolute_file_path = std::filesystem::canonical(entry.path());
        std::cout << absolute_file_path << std::endl;

        std::fstream infile(absolute_file_path, std::ios_base::in | std::ios_base::binary);

        if (!infile.is_open())
        {
            std::cerr << "CAN'T OPEN FILE" << errno << std::endl;
            return 0;
        }
        std::string file_hash = Hashing::createCheckSum(infile);
        DatabaseLogging::logCheckSum(database, database_path,absolute_file_path, file_hash);

    }
    std::this_thread::sleep_for(1000ms);

    for (const auto& entry : std::filesystem::directory_iterator(folder_iterable))
    {
        ThreatSimulator::modifyFile(entry.path());
    }
    DatabaseLogging::monitorFiles(database, database_path);

    return 1;
   
}