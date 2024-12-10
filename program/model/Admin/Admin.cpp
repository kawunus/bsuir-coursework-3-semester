#include "../Admin.h"

#include "../../Utils.h"


Admin::Admin(std::string name, int userId) {
    this->name = name;
    this->userId = userId;
}


void Admin::start() {
    std::cout << "Hi, " << name << "!" << std::endl;

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

        switch (command) {
            case 1:
                clearScreen();
                std::cout << "\n===== TRAINS INFO =====\n" << std::endl;
                printTrainsMenu();
                break;

            case 2:
                clearScreen();
                std::cout << "\n===== CARRIAGES INFO =====\n" << std::endl;
                printCarriagesMenu();
                break;

            case 3:
                clearScreen();
                std::cout << "\n===== STATIONS INFO =====\n" << std::endl;
                printStationsMenu();
                break;

            case 4:
                clearScreen();
                std::cout << "\n===== PLACES INFO =====\n" << std::endl;
                printPlacesMenu();
                break;

            case 5:
                clearScreen();
                std::cout << "\n===== ROUTES INFO =====\n" << std::endl;
                printRoutesMenu();
                break;

            case 6:
                clearScreen();
                std::cout << "\n===== TICKETS INFO =====\n" << std::endl;
                printTicketsMenu();
                break;

            case 0:
                clearScreen();
                std::cout << "\nExiting... Goodbye!\n" << std::endl;
                exit();
                break;

            default:
                clearScreen();
                std::cout << "\nInvalid choice. Please try again.\n" << std::endl;

                pressToContinue();
                break;
        }
    }
}

void Admin::createStation() {
    clearScreen();
    std::string name, city;

    std::cout << "==============================" << std::endl;
    std::cout << "        CREATE STATION        " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << "Enter the station name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter the city: ";
    std::getline(std::cin, city);

    if (db.createLocation(name, city) == SQLITE_OK) {
        std::cout << "\nStation added successfully.\n";
    } else {
        std::cerr << "\nError adding the station.\n";
    }

    pressToContinue();
}

void Admin::readStations() {
    clearScreen();

    std::cout << "==============================" << std::endl;
    std::cout << "         STATIONS LIST        " << std::endl;
    std::cout << "==============================" << std::endl;

    std::vector<std::string> stations = db.readLocations();

    if (stations.empty()) {
        std::cout << "\nNo stations in the database.\n";
    } else {
        std::cout << "\nStations:\n";
        for (const auto &station: stations) {
            std::cout << " - " << station << std::endl;
        }
    }
    std::cout << "==============================\n" << std::endl;

    pressToContinue();
}

void Admin::deleteStation() {
    clearScreen();
    readStations();

    int station_id;
    std::cout << "===============================" << std::endl;
    std::cout << "        DELETE STATION         " << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Enter the station ID to delete: ";
    std::cin >> station_id;

    if (db.deleteLocation(station_id) == SQLITE_OK) {
        std::cout << "\nStation deleted successfully.\n";
    } else {
        std::cout << "\nError deleting the station.\n";
    }

    pressToContinue();
}

void Admin::printStationsMenu() {
    clearScreen();

    std::cout << "===============================" << std::endl;
    std::cout << "        STATIONS MENU          " << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. Add a station" << std::endl;
    std::cout << "2. Delete station" << std::endl;
    std::cout << "3. View all stations" << std::endl;
    std::cout << "0. Exit" << std::endl;

    int command;
    std::cout << "Enter your choice: ";
    std::cin >> command;
    handleInvalidInput();

    switch (command) {
        case 1: {
            clearScreen();
            createStation();
            break;
        }
        case 2: {
            clearScreen();
            deleteStation();
            break;
        }
        case 3: {
            clearScreen();
            readStations();
            break;
        }
        case 0: {
            clearScreen();
            return;
        }
        default: {
            clearScreen();
            std::cout << "\nInvalid choice. Please try again.\n";
            pressToContinue();
            break;
        }
    }
}

void Admin::createTrain() {
    clearScreen();

    std::string train_number, type;
    std::cout << "=============================" << std::endl;
    std::cout << "        CREATE TRAIN         " << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << "Enter the train number: ";
    std::cin.ignore();
    std::getline(std::cin, train_number);

    std::cout << "Enter the train type: ";
    std::getline(std::cin, type);

    if (db.createTrain(train_number, type) == SQLITE_OK) {
        std::cout << "\nTrain added successfully.\n";
    } else {
        std::cout << "\nError adding the train.\n";
    }

    pressToContinue();
}

void Admin::deleteTrain() {
    clearScreen();

    readTrains();
    int train_id;
    std::cout << "=============================" << std::endl;
    std::cout << "        DELETE TRAIN         " << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << "Enter the train ID to delete: ";
    std::cin >> train_id;

    if (db.deleteTrain(train_id) == SQLITE_OK) {
        std::cout << "\nTrain deleted successfully.\n";
    } else {
        std::cout << "\nError deleting the train.\n";
    }

    pressToContinue();
}


void Admin::readTrains() {
    clearScreen();

    std::vector<std::string> trains = db.readTrains();

    std::cout << "=============================" << std::endl;
    std::cout << "         TRAINS LIST         " << std::endl;
    std::cout << "=============================" << std::endl;

    if (trains.empty()) {
        std::cout << "\nNo trains in the database.\n";
    } else {
        std::cout << "\nTrains:\n";
        for (const auto &train: trains) {
            std::cout << " - " << train << std::endl;
        }
    }
    std::cout << "=============================\n" << std::endl;


    pressToContinue();
}

void Admin::printTrainsMenu() {
    clearScreen();

    std::cout << "=============================" << std::endl;
    std::cout << "         TRAIN MENU          " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "1. Add Train                " << std::endl;
    std::cout << "2. Delete Train             " << std::endl;
    std::cout << "3. View All Trains          " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "0. Exit                     " << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Enter your choice: ";

    int command;
    std::cin >> command;
    handleInvalidInput();
    std::cin.ignore();
    switch (command) {
        case 1: {
            createTrain();
            break;
        }
        case 2: {
            deleteTrain();
            break;
        }
        case 3: {
            readTrains();
            break;
        }
        case 0: {
            clearScreen();
            return;
        }
        default: {
            clearScreen();
            std::cout << "\nInvalid choice. Please try again.\n";

            pressToContinue();
            break;
        }
    }
}

void Admin::createCarriage() {
    clearScreen();

    std::cout << "===============================" << std::endl;
    std::cout << "        CREATE CARRIAGE       " << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Choose train ID: " << std::endl;
    std::vector<int> train_ids = db.getTrainIds();
    if (train_ids.empty()) {
        std::cout << "No trains available.\n";
        return;
    }

    for (int id: train_ids) {
        std::cout << "Train ID: " << id << std::endl;
    }

    int train_id;
    std::cout << "Enter train ID: ";
    std::cin >> train_id;

    if (std::cin.fail()) {
        std::cout << "Invalid input for train ID.\n";
        return;
    }

    auto it = std::find(train_ids.begin(), train_ids.end(), train_id);
    if (it == train_ids.end()) {
        std::cout << "Invalid train ID.\n";
        return;
    }

    int number;
    std::string type;
    std::cout << "Enter carriage number: ";
    std::cin >> number;
    std::cout << "Enter carriage type (Compartment, Economy, Luxury): ";
    std::cin >> type;

    if (db.createCarriage(train_id, number, type) == SQLITE_OK) {
        std::cout << "\nCarriage added successfully.\n";
    } else {
        std::cout << "\nError adding carriage.\n";
    }


    pressToContinue();
}

void Admin::deleteCarriage() {
    clearScreen();

    int carriage_id;
    std::cout << "===============================" << std::endl;
    std::cout << "        DELETE CARRIAGE       " << std::endl;
    std::cout << "===============================" << std::endl;

    std::cout << "Enter carriage ID to delete: ";
    std::cin >> carriage_id;

    if (db.deleteCarriage(carriage_id) == SQLITE_OK) {
        std::cout << "\nCarriage deleted successfully.\n";
    } else {
        std::cout << "\nError deleting carriage.\n";
    }


    pressToContinue();
}

void Admin::readCarriages() {
    clearScreen();

    std::vector<std::string> carriages = db.readCarriages();

    std::cout << "===============================" << std::endl;
    std::cout << "        CARRIAGES LIST        " << std::endl;
    std::cout << "===============================" << std::endl;

    if (carriages.empty()) {
        std::cout << "\nNo carriages available.\n";
    } else {
        std::cout << "\nCarriages:\n";
        for (const auto &carriage: carriages) {
            std::cout << " - " << carriage << std::endl;
        }
    }

    std::cout << "===============================" << std::endl;

    pressToContinue();
}

void Admin::printCarriagesMenu() {
    clearScreen();

    std::cout << "===============================" << std::endl;
    std::cout << "       CARRIAGES MENU         " << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. Add carriage               " << std::endl;
    std::cout << "2. Delete carriage            " << std::endl;
    std::cout << "3. View all carriages         " << std::endl;
    std::cout << "4. Exit                       " << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";

    int command;
    std::cin >> command;
    handleInvalidInput();
    std::cin.ignore();
    switch (command) {
        case 1: {
            createCarriage();
            break;
        }
        case 2: {
            deleteCarriage();
            break;
        }
        case 3: {
            readCarriages();
            break;
        }
        case 4: {
            return;
        }
        default: {
            clearScreen();
            std::cout << "\nInvalid choice. Please try again.\n";
            pressToContinue();
            break;
        }
    }
}


// TODO: Зарефакторить
void Admin::printPlacesMenu() {
    clearScreen();

    auto train_ids = db.getTrainIds();
    if (train_ids.empty()) {
        std::cout << "==========================" << std::endl;
        std::cout << "     No trains available  " << std::endl;
        std::cout << "==========================" << std::endl;
        pressToContinue();
        return;
    }
    std::cout << "==========================" << std::endl;
    std::cout << "     Choose the train,    " << std::endl;
    std::cout << "    that interests you    " << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "       TRAIN IDs          " << std::endl;
    std::cout << "==========================" << std::endl;
    for (int id: train_ids) {
        std::cout << "Train ID: " << id << std::endl;
    }

    int train_id;
    std::cout << "\nEnter train ID: ";
    std::cin >> train_id;
    clearScreen();
    if (ranges::find(train_ids.begin(), train_ids.end(), train_id) == train_ids.end()) {
        std::cout << "Invalid train ID.\n";
        pressToContinue();
        return;
    }

    auto carriage_ids = db.getCarriageIds(train_id);
    if (carriage_ids.empty()) {
        std::cout << "==========================" << std::endl;
        std::cout << " No carriages available   " << std::endl;
        std::cout << "==========================" << std::endl;
        pressToContinue();
        return;
    }

    std::cout << "==========================" << std::endl;
    std::cout << "       CARRIAGE IDs       " << std::endl;
    std::cout << "==========================" << std::endl;
    for (int id: carriage_ids) {
        std::cout << "Carriage ID: " << id << std::endl;
    }

    int carriage_id;
    std::cout << "\nEnter carriage ID: ";
    std::cin >> carriage_id;

    if (ranges::find(carriage_ids.begin(), carriage_ids.end(), carriage_id) == carriage_ids.end()) {
        std::cout << "Invalid carriage ID.\n";
        pressToContinue();
        return;
    }

    while (true) {
        clearScreen();
        std::cout << "==========================" << std::endl;
        std::cout << "       PLACES MENU        " << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "1. View places            " << std::endl;
        std::cout << "2. Create place           " << std::endl;
        std::cout << "3. Delete place           " << std::endl;
        std::cout << "4. Change place status    " << std::endl;
        std::cout << "5. Exit                   " << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Choose an option: ";

        int option;
        std::cin >> option;
        handleInvalidInput();
        std::cin.ignore();
        switch (option) {
            case 1: {
                auto places = db.readPlaces(carriage_id);
                if (places.empty()) {
                    std::cout << "No places available.\n";
                } else {
                    for (const auto &place: places) {
                        std::cout << place << std::endl;
                    }
                }
                pressToContinue();
                break;
            }
            case 2: {
                int number;
                std::cout << "Enter place number: ";
                std::cin >> number;
                if (db.createPlace(carriage_id, number, "0") == SQLITE_OK) {
                    std::cout << "Place created successfully.\n";
                } else {
                    std::cout << "Error creating place.\n";
                }
                pressToContinue();
                break;
            }
            case 3: {
                int place_id;
                std::cout << "Enter place ID to delete: ";
                std::cin >> place_id;
                if (db.deletePlace(place_id) == SQLITE_OK) {
                    std::cout << "Place deleted successfully.\n";
                } else {
                    std::cout << "Error deleting place.\n";
                }
                pressToContinue();
                break;
            }
            case 4: {
                int place_id;
                std::cout << "Enter place ID: ";
                std::cin >> place_id;
                if (db.updatePlaceStatus(place_id, "1") == SQLITE_OK) {
                    std::cout << "Place status updated successfully.\n";
                } else {
                    std::cout << "Error updating place status.\n";
                }
                pressToContinue();
                break;
            }
            case 5: {
                clearScreen();
                return;
            }
            default: {
                std::cout << "Invalid option. Please try again.\n";
                pressToContinue();
                break;
            }
        }
    }
}

void Admin::printRoutesMenu() {
    while (true) {
        clearScreen();
        std::cout << "===========================" << std::endl;
        std::cout << "     Manage Routes         " << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "1. Create Route           " << std::endl;
        std::cout << "2. Delete Route           " << std::endl;
        std::cout << "3. View Routes            " << std::endl;
        std::cout << "0. Back                   " << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        handleInvalidInput();
        std::cin.ignore();
        switch (choice) {
            case 1: {
                std::vector<std::string> trains = db.readTrains();
                if (trains.empty()) {
                    std::cout << "===========================" << std::endl;
                    std::cout << " No trains available.     " << std::endl;
                    std::cout << "===========================" << std::endl;
                    pressToContinue();
                    break;
                }

                std::vector<std::string> stations = db.readLocations();
                if (stations.empty()) {
                    std::cout << "===========================" << std::endl;
                    std::cout << " No stations available.   " << std::endl;
                    std::cout << "===========================" << std::endl;
                    pressToContinue();
                    break;
                }

                std::cout << "\nAvailable Trains:\n";
                for (const auto &train: trains) {
                    std::cout << train << "\n";
                }

                std::cout << "\nAvailable Stations:\n";
                for (const auto &station: stations) {
                    std::cout << station << "\n";
                }

                int train_id, start_station_id, end_station_id;
                std::string departure_time, arrival_time;

                std::cout << "\nEnter Train ID: ";
                std::cin >> train_id;
                if (!db.trainExists(train_id)) {
                    std::cout << "Invalid Train ID. Try again.\n";
                    pressToContinue();
                    break;
                }

                std::cout << "Enter Start Station ID: ";
                std::cin >> start_station_id;
                if (!db.stationExists(start_station_id)) {
                    std::cout << "Invalid Start Station ID. Try again.\n";
                    pressToContinue();
                    break;
                }

                std::cout << "Enter End Station ID: ";
                std::cin >> end_station_id;
                if (!db.stationExists(end_station_id)) {
                    std::cout << "Invalid End Station ID. Try again.\n";
                    pressToContinue();
                    break;
                }

                if (start_station_id == end_station_id) {
                    std::cout << "Start and End stations must be different. Try again.\n";
                    pressToContinue();
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, departure_time);
                std::cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, arrival_time);

                if (departure_time >= arrival_time) {
                    std::cout << "Departure time must be earlier than arrival time. Try again.\n";
                    pressToContinue();
                    break;
                }

                if (db.createRoute(train_id, start_station_id, end_station_id, departure_time, arrival_time) ==
                    SQLITE_OK) {
                    std::cout << "Route created successfully.\n";
                } else {
                    std::cout << "Failed to create route.\n";
                }
                pressToContinue();
                break;
            }
            case 2: {
                std::vector<std::string> routes = db.readRoutes();
                if (routes.empty()) {
                    std::cout << "===========================" << std::endl;
                    std::cout << " No routes found.         " << std::endl;
                    std::cout << "===========================" << std::endl;
                    pressToContinue();
                    break;
                }
                std::cout << "Enter Route ID to delete: ";
                int route_id;
                std::cin >> route_id;

                if (db.deleteRoute(route_id) == SQLITE_OK) {
                    std::cout << "Route deleted successfully.\n";
                } else {
                    std::cout << "Error deleting route.\n";
                }
                pressToContinue();
                break;
            }
            case 3: {
                std::vector<std::string> routes = db.readRoutes();
                if (routes.empty()) {
                    std::cout << "===========================" << std::endl;
                    std::cout << " No routes found.         " << std::endl;
                    std::cout << "===========================" << std::endl;
                } else {
                    std::cout << "===========================" << std::endl;
                    std::cout << " Available Routes:        " << std::endl;
                    std::cout << "===========================" << std::endl;
                    for (const auto &route: routes) {
                        std::cout << route << "\n";
                    }
                }
                pressToContinue();
                break;
            }
            case 0: {
                clearScreen();
                return;
            }
            default: {
                std::cout << "Invalid choice. Try again.\n";
                pressToContinue();
                break;
            }
        }
    }
}

void Admin::printTicketsMenu() {
    while (true) {
        clearScreen();
        std::cout << "=============================" << std::endl;
        std::cout << "     Ticket Management       " << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "1. Create Ticket            " << std::endl;
        std::cout << "2. View Tickets             " << std::endl;
        std::cout << "3. Delete Ticket            " << std::endl;
        std::cout << "0. Back to Main Menu        " << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        handleInvalidInput();
        std::cin.ignore();
        switch (choice) {
            case 1:
                createTicketMenu();
                break;
            case 2:
                readTicketsMenu();
                break;
            case 3:
                deleteTicketMenu();
                break;
            case 0:
                clearScreen();
                return;
            default: {
                std::cout << "=============================" << std::endl;
                std::cout << " Invalid choice. Try again. " << std::endl;
                std::cout << "=============================" << std::endl;
                pressToContinue();
                break;
            }
        }
    }
}

void Admin::createTicketMenu() {
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
    for (const auto &passenger : passengers) {
        std::cout << passenger << '\n';
    }

    int passenger_id;
    std::cout << "Enter Passenger ID: ";
    std::cin >> passenger_id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string purchase_time;
    std::cout << "Enter Purchase Time (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, purchase_time);

    if (db.createTicket(place_id, route_id, passenger_id, purchase_time) == SQLITE_OK) {
        std::cout << "Ticket created successfully.\n";
    } else {
        std::cout << "Failed to create ticket.\n";
    }
}

void Admin::readTicketsMenu() {
    clearScreen();
    std::cout << "=============================" << std::endl;
    std::cout << "      View Tickets           " << std::endl;
    std::cout << "=============================" << std::endl;

    auto tickets = db.readTickets();
    if (tickets.empty()) {
        std::cout << "No tickets found.\n";
        pressToContinue();
        return;
    }

    std::cout << "Tickets:\n";
    for (const auto &ticket: tickets) {
        std::cout << ticket << '\n';
    }
    pressToContinue();
}

void Admin::deleteTicketMenu() {
    clearScreen();
    std::cout << "=============================" << std::endl;
    std::cout << "      Delete Ticket          " << std::endl;
    std::cout << "=============================" << std::endl;

    int ticket_id;
    std::cout << "Enter Ticket ID to delete: ";
    std::cin >> ticket_id;

    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a valid Ticket ID.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
