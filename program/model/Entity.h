// Entity.h
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

#include "Database.h"

class Entity {
public:
    virtual ~Entity() = default;

    std::string name;
    int userId;

protected:
    bool isWork = true;
    Database db;
    const std::string dbName = "/home/stanislau/bsuir-coursework-3-semester/program/station.db";

    void exit();

    virtual void printStationsMenu() =0;

    virtual void printPlacesMenu() =0;

    //virtual void updatePlaceStatus() =0;

    virtual void printTicketsMenu() = 0;

    virtual void createTicketMenu() = 0;

    virtual void readTicketsMenu() = 0;

    virtual void deleteTicketMenu() = 0;
};

#endif // ENTITY_H
