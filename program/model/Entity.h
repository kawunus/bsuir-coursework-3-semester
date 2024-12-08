// Entity.h
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

#include "Database.h"

class Entity {
protected:
    bool isWork = true;
    Database db;
    const std::string dbName = "/home/stanislau/bsuir-itas-stp-latex/program/station.db";

    void exit();
};

#endif // ENTITY_H
