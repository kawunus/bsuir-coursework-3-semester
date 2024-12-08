#include "../System.h"
#include "../../Utils.h"

void System::exit() {
    std::cout << "Exiting the program..." << std::endl;
    isWork = false;
}

int System::login() {
    while (isWork) {
        printLoginMenu();
        int command;
        std::cin >> command;
        handleInvalidInput();
        switch (command) {
            case 1: {
                std::cout << "Enter a password: " << std::endl;
                std::string password;
                std::cin >> password;
                if (password != "12345678") {
                    std::cout << "Invalid password. Please, retry!" << std::endl;
                } else return 1;
                break;
            }
            case 2: return 2;
            case 0: return 0;
            default: {
                std::cout << "Invalid command. Please, try again." << std::endl;
                break;
            }
        }
    }
}

void System::printLoginMenu() {
    std::cout << "Who will be using the system today?" << std::endl;
    std::cout << "1. Admin" << std::endl;
    std::cout << "2. User" << std::endl;
    std::cout << "0. Exit the program" << std::endl;
    std::cout << "Enter the number for your choice" << std::endl;
}
