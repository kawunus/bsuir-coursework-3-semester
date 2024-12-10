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
        }
    }
}

void User::createTicketMenu() {
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
