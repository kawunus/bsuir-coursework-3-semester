#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include "Entity.h"

class Admin : public Entity {
private:



    void printStationsMenu() override;

    void createStation();

    void readStations();

    void deleteStation();

    void printTrainsMenu();

    void createTrain();

    void readTrains();

    void deleteTrain();

    void printCarriagesMenu();

    void createCarriage();

    void readCarriages();

    void deleteCarriage();

    // TODO: Зарефакторить!

    void printPlacesMenu() override;

    // TODO: Зарефакторить!

    void printRoutesMenu();

    // TODO: Зарефакторить!

    void createTicketMenu() override;

    void readTicketsMenu() override;

    void deleteTicketMenu() override;

    void printTicketsMenu() override;

public:
    void start();

    Admin(std::string name, int userId);
};

#endif // ADMIN_H
