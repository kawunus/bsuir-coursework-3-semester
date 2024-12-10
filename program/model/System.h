#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>

#include "Database.h"

class System {
private:
    bool isWork = true;
    Database db;
    const std::string dbName = "/home/stanislau/bsuir-coursework-3-semester/program/station.db";

public:
    void exit();

    int login();

    static void printLoginMenu();
};

#endif // SYSTEM_H
