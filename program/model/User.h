#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Entity.h"
#include "../Utils.h"

class User : public Entity {
private:
    void printTicketsMenu() override;

    void createTicketMenu() override;

    void readTicketsMenu() override;

    void deleteTicketMenu() override;

    void printStationsMenu() override;

    void printPlacesMenu() override;

public:
    void start();

    User(std::string name, int userId);
};

#endif // USER_H
