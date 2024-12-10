#include "../System.h"
#include "../../Utils.h"

void System::exit() {
    std::cout << "Exiting the program..." << std::endl;
    isWork = false;
}

int System::login() {
    if (!db.openDatabase(dbName)) {
        std::cerr << "Failed to open the database. Terminating." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    clearScreen();

    while (isWork) {
        printLoginMenu();
        int command;
        std::cin >> command;
        handleInvalidInput();

        switch (command) {
            case 1: {
                std::string email, password;
                std::cout << "Enter email: ";
                std::cin >> email;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter password: ";
                std::cin >> password;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                int userId = db.login(email, hashPassword(password));
                if (userId != -1) {
                    std::cout << "Login successful! Your user ID is " << userId << "." << std::endl;
                    return userId;
                } else {
                    std::cout << "Invalid email or password. Try again." << std::endl;
                }
                break;
            }
            case 2: {
                std::string name, email, password;
                std::cout << "Enter your name: ";
                std::cin >> name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter your email: ";
                std::cin >> email;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter your password: ";
                std::cin >> password;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (db.registerUser(name, email, hashPassword(password))) {
                    std::cout << "Registration successful! You can now login." << std::endl;
                    cout << db.login(email, hashPassword(password));
                } else {
                    std::cout << "Registration failed. Email might already be in use." << std::endl;
                }
                break;
            }
            case 0: {
                isWork = false;
                std::cout << "Exiting the system. Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }
    }
    return -1;
}

void System::printLoginMenu() {
    std::cout << "======= Login Menu =======" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Select an option: ";
}
