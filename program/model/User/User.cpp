#include "../User.h"

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
        std::cout << "1. Trains info" << std::endl;
        std::cout << "2. Carriages info" << std::endl;
        std::cout << "3. Stations info" << std::endl;
        std::cout << "4. Places info" << std::endl;
        std::cout << "5. Routes info" << std::endl;
        std::cout << "6. Tickets info" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Enter your choice: ";

        int command;
        std::cin >> command;
        handleInvalidInput();


    }
}
