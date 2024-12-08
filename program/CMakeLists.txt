cmake_minimum_required(VERSION 3.29)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp
        model/Entity/Entity.cpp
        model/Entity.h
        model/Database/Database.cpp
        model/Database.h
        model/System/System.cpp
        model/System.h
        Utils.cpp
        Utils.h
        model/Admin/Admin.cpp
        model/Admin.h
        model/User.h
        model/User/User.cpp)

# Добавляем SQLite3
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})
link_libraries(${SQLite3_LIBRARIES})
target_link_libraries(code SQLite::SQLite3)
