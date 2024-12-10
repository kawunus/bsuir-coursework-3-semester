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
                clearScreen();
                createTicketMenu();
                break;
            }

            case 2: {
                clearScreen();
                readTicketsMenu();
                break;
            }

            case 3: {
                deleteTicketMenu();
                break;
            }
            default: {
                clearScreen();
                std::cout << "Invalid choice." << std::endl;
                pressToContinue();
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


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if (db.createTicket(place_id, route_id, userId, getCurrentTime()) == SQLITE_OK) {
        std::cout << "Ticket created successfully.\n";
        pressToContinue();
    } else {
        std::cout << "Failed to create ticket.\n";
        pressToContinue();
    }
}

void User::deleteTicketMenu() {
    clearScreen();
    std::cout << "=============================" << std::endl;
    std::cout << "      Delete Ticket          " << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << "Your Tickets:\n";
    auto tickets = db.getTicketsByUserId(userId);
    if (tickets.empty()) {
        std::cout << "You have no tickets.\n";
        pressToContinue();
        return;
    }

    for (const auto &ticket: tickets) {
        std::cout << "Ticket ID: " << std::get<0>(ticket)
                << ", Route: " << std::get<1>(ticket)
                << ", Place: " << std::get<2>(ticket)
                << ", Purchase Time: " << std::get<3>(ticket) << '\n';
    }

    int ticket_id;
    std::cout << "Enter Ticket ID to delete: ";
    std::cin >> ticket_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a valid Ticket ID.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        pressToContinue();
        return;
    }

    bool ticketFound = false;
    for (const auto &ticket: tickets) {
        if (std::get<0>(ticket) == ticket_id) {
            ticketFound = true;
            break;
        }
    }
    if (!ticketFound) {
        std::cout << "You cannot delete a ticket that does not belong to you.\n";
        pressToContinue();
        return;
    }

    if (db.deleteTicket(ticket_id) == SQLITE_OK) {
        std::cout << "Ticket deleted successfully.\n";
    } else {
        std::cout << "Failed to delete ticket.\n";
    }

    pressToContinue();
}

void User::printPlacesMenu() {
}

void User::printStationsMenu() {
}

void User::printTicketsMenu() {
}

void User::readTicketsMenu() {
}
