#include "../System.h"

#include "../Admin.h"
#include "../../Utils.h"
#include "../User.h"

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
                clearScreen();
                std::string email, password;
                std::cout << "Enter email: ";
                std::cin >> email;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen();
                std::cout << "Enter password: ";
                std::cin >> password;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                int userId = db.login(email, hashPassword(password));
                if (userId != -1) {
                    clearScreen();
                    std::cout << "Login successful! Your user ID is " << userId << "." << std::endl;

                    pressToContinue();

                    if (db.isAdmin(email)) {
                        Admin admin(db.getUserNameByEmail(email), userId);
                        admin.start();
                    } else {
                        User user(db.getUserNameByEmail(email), userId);
                        user.start();
                    }

                    return userId;
                } else {
                    clearScreen();
                    std::cout << "Invalid email or password. Try again." << std::endl;
                }
                break;
            }
            case 2: {
                clearScreen();
                std::string name, email, password;
                std::cout << "Enter your name: ";
                std::cin >> name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen();
                std::cout << "Enter your email: ";
                std::cin >> email;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen();
                std::cout << "Enter your password: ";
                std::cin >> password;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen();

                if (db.registerUser(name, email, hashPassword(password))) {
                    std::cout << "Registration successful!" << std::endl;

                    pressToContinue();

                    User user(db.getUserNameByEmail(email), db.getUserIdByEmail(email));
                    user.start();
                } else {
                    clearScreen();
                    std::cout << "Registration failed. Email might already be in use." << std::endl;
                    pressToContinue();
                }
                break;
            }
            case 0: {
                clearScreen();
                isWork = false;
                std::cout << "Exiting the system. Goodbye!" << std::endl;
                break;
            }
            default: {
                clearScreen();
                std::cout << "Invalid option. Please try again." << std::endl;

                pressToContinue();

                break;
            }
        }
    }
    return -1;
}

void System::printLoginMenu() {
    clearScreen();
    std::cout << "======= Login Menu =======" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Select an option: ";
}
