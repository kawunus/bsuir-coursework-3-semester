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
    std::string name = "admin";

    void printStationsMenu();

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

    void printPlacesMenu();

    void readPlaces();

    void createPlace();

    void deletePlace();

    void updatePlaceStatus();

    // TODO: Зарефакторить!

    void printRoutesMenu();

    // TODO: Зарефакторить!

    void createTicketMenu();
    void readTicketsMenu();
    void deleteTicketMenu();
    void printTicketsMenu();
public:
    void start();
};

#endif // ADMIN_H
