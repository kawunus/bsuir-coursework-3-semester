#include "../Admin.h"

#include "../../Utils.h"

void Admin::start() {
    cout << "Hi, " << name << "!" << std::endl;
    if (!db.openDatabase(dbName)) {
        std::cerr << "Failed to open the database. Terminating." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while (isWork) {
        cout << "Menu:" << endl;
        cout << "1. Trains info" << endl;
        cout << "2. Carriages info" << endl;
        cout << "3. Stations info" << endl;
        cout << "4. Places info" << endl;
        cout << "5. Routes info" << endl;
        cout << "6. Tickets info" << endl;
        cout << "0. Exit" << endl;

        int command;
        cin >> command;
        handleInvalidInput();
        switch (command) {
            case 1: {
                printTrainsMenu();
                break;
            }
            case 2: {
                printCarriagesMenu();
                break;
            }
            case 3: {
                printStationsMenu();
                break;
            }
            case 4: {
                printPlacesMenu();
                break;
            }
            case 5: {
                printRoutesMenu();
                break;
            }
            case 6: {
                printTicketsMenu();
                break;
            }
            case 0: {
                exit();
            }
            default: {
            }
        }
    }
}

void Admin::createStation() {
    std::string name, city;
    std::cout << "Введите название станции: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Введите город: ";
    std::getline(std::cin, city);

    if (db.createLocation(name, city) == SQLITE_OK) {
        std::cout << "Станция добавлена успешно.\n";
    } else {
        std::cout << "Ошибка при добавлении станции.\n";
    }
}

void Admin::readStations() {
    std::vector<std::string> stations = db.readLocations();
    if (stations.empty()) {
        std::cout << "Нет станций в базе данных.\n";
    } else {
        std::cout << "\nСтанции:\n";
        for (const auto &station: stations) {
            std::cout << station << std::endl;
        }
    }
}

void Admin::deleteStation() {
    readStations();
    int station_id;
    std::cout << "Введите ID станции для удаления: ";
    std::cin >> station_id;

    if (db.deleteLocation(station_id) == SQLITE_OK) {
        std::cout << "Станция удалена успешно.\n";
    } else {
        std::cout << "Ошибка при удалении станции.\n";
    }
}

void Admin::printStationsMenu() {
    std::cout << "1. Add a station\n";
    std::cout << "2. Delete station\n";
    std::cout << "3. View all stations\n";
    std::cout << "0. Exit\n";

    int command;
    cin >> command;
    handleInvalidInput();
    switch (command) {
        case 1: {
            createStation();
            break;
        }
        case 2: {
            deleteStation();
            break;
        }
        case 3: {
            readStations();
            break;
        }
        case 0: { return; }
        default: {
            break;
        }
    }
}

void Admin::createTrain() {
    std::string train_number, type;
    std::cout << "Введите номер поезда: ";
    std::cin.ignore();
    std::getline(std::cin, train_number);
    std::cout << "Введите тип поезда: ";
    std::getline(std::cin, type);

    if (db.createTrain(train_number, type) == SQLITE_OK) {
        std::cout << "Поезд добавлен успешно.\n";
    } else {
        std::cout << "Ошибка при добавлении поезда.\n";
    }
}

void Admin::deleteTrain() {
    readTrains();
    int train_id;
    std::cout << "Введите ID поезда для удаления: ";
    std::cin >> train_id;

    if (db.deleteTrain(train_id) == SQLITE_OK) {
        std::cout << "Поезд удален успешно.\n";
    } else {
        std::cout << "Ошибка при удалении поезда.\n";
    }
}

void Admin::readTrains() {
    std::vector<std::string> trains = db.readTrains();
    if (trains.empty()) {
        std::cout << "Нет поездов в базе данных.\n";
    } else {
        std::cout << "\nПоезда:\n";
        for (const auto &train: trains) {
            std::cout << train << std::endl;
        }
    }
}

void Admin::printTrainsMenu() {
    std::cout << "\n1. Добавить поезд\n";
    std::cout << "2. Удалить поезд\n";
    std::cout << "3. Просмотреть все поезда\n";
    std::cout << "4. Выйти\n";

    int command;
    cin >> command;
    handleInvalidInput();
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
        case 0: { return; }
        default: {
            break;
        }
    }
}

void Admin::createCarriage() {
    std::cout << "Choose train ID: " << endl;
    std::vector<int> train_ids = db.getTrainIds();
    if (train_ids.empty()) {
        std::cout << "No trains available.\n";
        return;;
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

    auto it = ranges::find(train_ids.begin(), train_ids.end(), train_id);
    if (it == train_ids.end()) {
        std::cout << "Invalid train ID.\n";
        return;
    }

    int number;
    std::string type;
    std::cout << "Enter carriage number: ";
    std::cin >> number;
    std::cout << "Enter carriage type (купе, плацкарт, СВ): ";
    std::cin >> type;

    if (db.createCarriage(train_id, number, type) == SQLITE_OK) {
        std::cout << "Carriage added successfully.\n";
    } else {
        std::cout << "Error adding carriage.\n";
    }
}

void Admin::deleteCarriage() {
    int carriage_id;
    std::cout << "Enter carriage ID to delete: ";
    std::cin >> carriage_id;

    if (db.deleteCarriage(carriage_id) == SQLITE_OK) {
        std::cout << "Carriage deleted successfully.\n";
    } else {
        std::cout << "Error deleting carriage.\n";
    }
}

void Admin::readCarriages() {
    std::vector<std::string> carriages = db.readCarriages();
    if (carriages.empty()) {
        std::cout << "No carriages available.\n";
    } else {
        std::cout << "\nCarriages:\n";
        for (const auto &carriage: carriages) {
            std::cout << carriage << std::endl;
        }
    }
}

void Admin::printCarriagesMenu() {
    std::cout << "\n1. Add carriage\n";
    std::cout << "2. Delete carriage\n";
    std::cout << "3. View all carriages\n";
    std::cout << "4. Exit\n";

    int command;
    cin >> command;
    handleInvalidInput();
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
        case 0: { return; }
        default: {
            break;
        }
    }
}


// TODO: Зарефакторить
void Admin::printPlacesMenu() {
    auto train_ids = db.getTrainIds();
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

    if (ranges::find(train_ids.begin(), train_ids.end(), train_id) == train_ids.end()) {
        std::cout << "Invalid train ID.\n";
        return;
    }

    auto carriage_ids = db.getCarriageIds(train_id);
    if (carriage_ids.empty()) {
        std::cout << "No carriages available for this train.\n";
        return;
    }

    for (int id: carriage_ids) {
        std::cout << "Carriage ID: " << id << std::endl;
    }

    int carriage_id;
    std::cout << "Enter carriage ID: ";
    std::cin >> carriage_id;

    if (ranges::find(carriage_ids.begin(), carriage_ids.end(), carriage_id) == carriage_ids.end()) {
        std::cout << "Invalid carriage ID.\n";
        return;
    }

    while (true) {
        std::cout << "1. View places\n2. Create place\n3. Delete place\n4. Change status\n5. Exit\nChoose an option: ";
        int option;
        std::cin >> option;

        if (option == 1) {
            auto places = db.readPlaces(carriage_id);
            if (places.empty()) {
                std::cout << "No places available.\n";
            } else {
                for (const auto &place: places) {
                    std::cout << place << std::endl;
                }
            }
        } else if (option == 2) {
            int number;
            std::cout << "Enter place number: ";
            std::cin >> number;
            if (db.createPlace(carriage_id, number, "0") == SQLITE_OK) {
                std::cout << "Place created successfully.\n";
            } else {
                std::cout << "Error creating place.\n";
            }
        } else if (option == 3) {
            int place_id;
            std::cout << "Enter place ID to delete: ";
            std::cin >> place_id;
            if (db.deletePlace(place_id) == SQLITE_OK) {
                std::cout << "Place deleted successfully.\n";
            } else {
                std::cout << "Error deleting place.\n";
            }
        } else if (option == 4) {
            int place_id;
            std::cout << "Enter place ID: ";
            std::cin >> place_id;
            if (db.updatePlaceStatus(place_id, "1") == SQLITE_OK) {
                std::cout << "Place status updated successfully.\n";
            } else {
                std::cout << "Error updating place status.\n";
            }
        } else if (option == 5) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void Admin::printRoutesMenu() {
    while (true) {
        std::cout << "\n--- Manage Routes ---\n";
        std::cout << "1. Create Route\n";
        std::cout << "2. Delete Route\n";
        std::cout << "3. View Routes\n";
        std::cout << "0. Back\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::vector<std::string> trains = db.readTrains();
                if (trains.empty()) {
                    std::cout << "No trains available. Create a train first.\n";
                    break;
                }

                std::vector<std::string> stations = db.readLocations();
                if (stations.empty()) {
                    std::cout << "No stations available. Create stations first.\n";
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
                    break;
                }

                std::cout << "Enter Start Station ID: ";
                std::cin >> start_station_id;
                if (!db.stationExists(start_station_id)) {
                    std::cout << "Invalid Start Station ID. Try again.\n";
                    break;
                }

                std::cout << "Enter End Station ID: ";
                std::cin >> end_station_id;
                if (!db.stationExists(end_station_id)) {
                    std::cout << "Invalid End Station ID. Try again.\n";
                    break;
                }

                if (start_station_id == end_station_id) {
                    std::cout << "Start and End stations must be different. Try again.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, departure_time);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, arrival_time);

                if (departure_time >= arrival_time) {
                    std::cout << "Departure time must be earlier than arrival time. Try again.\n";
                    break;
                }

                if (db.createRoute(train_id, start_station_id, end_station_id, departure_time, arrival_time) ==
                    SQLITE_OK) {
                    std::cout << "Route created successfully.\n";
                } else {
                    std::cout << "Failed to create route.\n";
                }
                break;
            }
            case 2: {
                db.readRoutes();
                int route_id;
                std::cout << "Enter Route ID to delete: ";
                std::cin >> route_id;

                if (db.deleteRoute(route_id) == SQLITE_OK) {
                    std::cout << "Route deleted successfully.\n";
                }
                break;
            }
            case 3: {
                std::vector<std::string> routes = db.readRoutes();
                if (routes.empty()) {
                    std::cout << "No routes found.\n";
                } else {
                    for (const auto &route: routes) {
                        std::cout << route << "\n";
                    }
                }
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void Admin::printTicketsMenu() {
    while (true) {
        std::cout << "\nTicket Management Menu:\n";
        std::cout << "1. Create Ticket\n";
        std::cout << "2. View Tickets\n";
        std::cout << "3. Delete Ticket\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

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
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void Admin::createTicketMenu() {
    std::cout << "Available Routes:\n";
    auto routes = db.getRoutes();
    for (const auto &route: routes) {
        std::cout << route << '\n';
    }

    int route_id;
    std::cout << "Enter Route ID: ";
    std::cin >> route_id;

    auto places = db.getAvailablePlaces(route_id);
    if (places.empty()) {
        std::cout << "No available places for this route.\n";
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
    std::string passenger_name;
    std::cout << "Enter Passenger Name: ";
    std::getline(std::cin, passenger_name);

    std::string purchase_time;
    std::cout << "Enter Purchase Time (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, purchase_time);

    if (db.createTicket(place_id, route_id, passenger_name, purchase_time) == SQLITE_OK) {
        std::cout << "Ticket created successfully.\n";
    } else {
        std::cout << "Failed to create ticket.\n";
    }
}

void Admin::readTicketsMenu() {
    auto tickets = db.readTickets();
    if (tickets.empty()) {
        std::cout << "No tickets found.\n";
        return;
    }
    for (const auto &ticket: tickets) {
        std::cout << ticket << '\n';
    }
}

void Admin::deleteTicketMenu() {
    int ticket_id;
    std::cout << "Enter Ticket ID to delete: ";
    std::cin >> ticket_id;

    if (db.deleteTicket(ticket_id) == SQLITE_OK) {
        std::cout << "Ticket deleted successfully.\n";
    } else {
        std::cout << "Failed to delete ticket.\n";
    }
}
