#include "../User.h"

User::User(std::string name, int userId) {
    this->name = name;
    this->userId = userId;
}

void User::start() {
    std::cout << "Welcome to the station information system" << std::endl;
    if (!db.openDatabase(dbName)) {
        std::cerr << "Failed to open the database. Terminating." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    clearScreen();

    while (isWork) {
        std::cout << "==========================" << std::endl;
        std::cout << "         MAIN MENU        " << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "1. Buy ticket             " << std::endl;
        std::cout << "2. Show my tickets        " << std::endl;
        std::cout << "3. Return the ticket      " << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Enter your choice: ";

        int command;
        std::cin >> command;
        handleInvalidInput();

        switch (command) {
            case 0: {
                clearScreen();
                exit();
                break;
            }

            case 1: {
                createTicketMenu();
                break;
            }
        }
    }
}

void User::createTicketMenu() {
    clearScreen();
    std::cout << "=============================" << std::endl;
    std::cout << "      Create Ticket          " << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << "Available Routes:\n";
    auto routes = db.getRoutes();
    if (routes.empty()) {
        std::cout << "No available routes.\n";
        return;
    }

    for (const auto &route: routes) {
        std::cout << route << '\n';
    }

    int route_id;
    std::cout << "Enter Route ID: ";
    std::cin >> route_id;

    auto places = db.getAvailablePlaces(route_id);
    if (places.empty()) {
        std::cout << "No available places for this route.\n";
        pressToContinue();
        return;
    }

    std::cout << "Available Places:\n";
    for (const auto &place: places) {
        std::cout << place << '\n';
    }

    int place_id;
    std::cout << "Enter Place ID: ";
    std::cin >> place_id;

    auto passengers = db.readAllPassengers();
    if (passengers.empty()) {
        std::cout << "No passengers found.\n";
        pressToContinue();
        return;
    }

    std::cout << "Available Passengers:\n";
    for (const auto &passenger: passengers) {
        std::cout << passenger << '\n';
    }


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if (db.createTicket(place_id, route_id, userId, getCurrentTime()) == SQLITE_OK) {
        std::cout << "Ticket created successfully.\n";
    } else {
        std::cout << "Failed to create ticket.\n";
    }
}

void User::deleteTicketMenu() {
}

void User::printPlacesMenu() {
}

void User::printStationsMenu() {
}

void User::printTicketsMenu() {
}

void User::readTicketsMenu() {
}
