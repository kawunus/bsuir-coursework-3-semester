#include "Utils.h"

#include <iostream>

void handleInvalidInput() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again!" << std::endl;
    }
}

void clearScreen() {
    std::system("clear");
}

void pressToContinue() {
    std::cout << "\nPress enter to continue...";
    std::cin.get();
    clearScreen();
}
