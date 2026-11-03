cmake_minimum_required(VERSION 3.14)

project(FIM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(main src/main.cpp src/log.cpp src/hash.cpp src/file_changer.cpp)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE OpenSSL::Crypto SQLite3::SQLite3)