#include "../Database.h"

Database::Database() : db(nullptr) {
}

bool Database::openDatabase(const std::string &dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Error opening the database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    } else {
        std::cout << "Database opened successfully..." << std::endl;
        return true;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3 *Database::getDatabase() {
    return db;
}

int Database::executeQuery(const std::string &query) {
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

int Database::createLocation(const std::string &name, const std::string &city) {
    std::string query = "INSERT INTO stations (name, city) VALUES ('" + name + "', '" + city + "');";
    return executeQuery(query);
}

int Database::deleteLocation(int station_id) {
    std::string query = "DELETE FROM stations WHERE station_id = " + std::to_string(station_id) + ";";
    return executeQuery(query);
}

std::vector<std::string> Database::readLocations() {
    std::vector<std::string> locations;
    const char *query = "SELECT station_id, name, city FROM stations;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return locations;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int station_id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string city = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        locations.push_back("ID: " + std::to_string(station_id) + ", Название: " + name + " (" + city + ")");
    }

    sqlite3_finalize(stmt);
    return locations;
}

int Database::createTrain(const std::string &train_number, const std::string &type) {
    std::string query = "INSERT INTO trains (train_number, type) VALUES ('" + train_number + "', '" + type + "');";
    return executeQuery(query);
}

int Database::deleteTrain(int train_id) {
    std::string deleteCarriagesQuery = "DELETE FROM carriages WHERE train_id = " + std::to_string(train_id) + ";";
    if (executeQuery(deleteCarriagesQuery) != SQLITE_OK) {
        std::cerr << "Failed to delete carriages for train ID: " << train_id << std::endl;
        return SQLITE_ERROR;
    }

    std::string deleteTrainQuery = "DELETE FROM trains WHERE train_id = " + std::to_string(train_id) + ";";
    return executeQuery(deleteTrainQuery);
}


std::vector<std::string> Database::readTrains() {
    std::vector<std::string> trains;
    const char *query = "SELECT train_id, train_number, type FROM trains;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return trains;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int train_id = sqlite3_column_int(stmt, 0);
        std::string train_number = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        trains.push_back("ID: " + std::to_string(train_id) + ", Номер поезда: " + train_number + ", Тип: " + type);
    }

    sqlite3_finalize(stmt);
    return trains;
}

int Database::createCarriage(int train_id, int number, const std::string &type) {
    std::string query = "INSERT INTO carriages (train_id, number, type) VALUES ("
                        + std::to_string(train_id) + ", "
                        + std::to_string(number) + ", '"
                        + type + "');";

    if (executeQuery(query) != SQLITE_OK) {
        std::cerr << "Failed to create carriage.\n";
        return SQLITE_ERROR;
    }

    int carriage_id = sqlite3_last_insert_rowid(db);
    if (carriage_id == 0) {
        std::cerr << "Failed to retrieve carriage ID.\n";
        return SQLITE_ERROR;
    }

    std::string placesQuery = "INSERT INTO places (carriage_id, number, status) VALUES ";
    for (int i = 1; i <= 30; ++i) {
        placesQuery += "(" + std::to_string(carriage_id) + ", "
                       + std::to_string(i) + ", '0'),";
    }
    placesQuery.pop_back();
    placesQuery += ";";

    if (executeQuery(placesQuery) != SQLITE_OK) {
        std::cerr << "Failed to create places for carriage ID: " << carriage_id << ".\n";
        return SQLITE_ERROR;
    }

    return SQLITE_OK;
}


int Database::deleteCarriage(int carriage_id) {
    std::string query = "DELETE FROM carriages WHERE carriage_id = " + std::to_string(carriage_id) + ";";
    return executeQuery(query);
}

std::vector<std::string> Database::readCarriages() {
    std::vector<std::string> carriages;
    const char *query = "SELECT carriage_id, train_id, number, type FROM carriages;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return carriages;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int carriage_id = sqlite3_column_int(stmt, 0);
        int train_id = sqlite3_column_int(stmt, 1);
        int number = sqlite3_column_int(stmt, 2);
        std::string type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        carriages.push_back("Carriage ID: " + std::to_string(carriage_id) + ", Train ID: "
                            + std::to_string(train_id) + ", Number: " + std::to_string(number) + ", Type: " + type);
    }

    sqlite3_finalize(stmt);
    return carriages;
}

std::vector<int> Database::getTrainIds() {
    std::vector<int> train_ids;
    const char *query = "SELECT train_id FROM trains;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        return train_ids;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int train_id = sqlite3_column_int(stmt, 0);
        train_ids.push_back(train_id);
    }

    sqlite3_finalize(stmt);
    return train_ids;
}

std::vector<int> Database::getCarriageIds(int train_id) {
    std::vector<int> carriage_ids;
    std::string query = "SELECT carriage_id FROM carriages WHERE train_id = " + std::to_string(train_id) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            carriage_ids.push_back(sqlite3_column_int(stmt, 0));
        }
    }
    sqlite3_finalize(stmt);
    return carriage_ids;
}

std::vector<std::string> Database::readPlaces(int carriage_id) {
    std::vector<std::string> places;
    std::string query = "SELECT place_id, number, status FROM places WHERE carriage_id = " + std::to_string(carriage_id) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int place_id = sqlite3_column_int(stmt, 0);
            int number = sqlite3_column_int(stmt, 1);
            const char* status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            places.emplace_back("ID: " + std::to_string(place_id) + ", Number: " + std::to_string(number) + ", Status: " + std::string(status));
        }
    }
    sqlite3_finalize(stmt);
    return places;
}

int Database::createPlace(int carriage_id, int number, const std::string& status) {
    std::string query = "INSERT INTO places (carriage_id, number, status) VALUES ("
                        + std::to_string(carriage_id) + ", "
                        + std::to_string(number) + ", '"
                        + status + "');";
    return executeQuery(query);
}

int Database::deletePlace(int place_id) {
    std::string query = "DELETE FROM places WHERE place_id = " + std::to_string(place_id) + ";";
    return executeQuery(query);
}

int Database::updatePlaceStatus(int place_id, const std::string& status) {
    std::string query = "UPDATE places SET status = '" + status + "' WHERE place_id = " + std::to_string(place_id) + ";";
    return executeQuery(query);
}

int Database::createRoute(int train_id, int start_station_id, int end_station_id, const std::string& departure_time, const std::string& arrival_time) {
    std::string query = "INSERT INTO routes (train_id, start_station_id, end_station_id, departure_time, arrival_time) VALUES ("
                        + std::to_string(train_id) + ", "
                        + std::to_string(start_station_id) + ", "
                        + std::to_string(end_station_id) + ", '"
                        + departure_time + "', '"
                        + arrival_time + "');";

    if (executeQuery(query) != SQLITE_OK) {
        std::cerr << "Failed to create route.\n";
        return SQLITE_ERROR;
    }
    return SQLITE_OK;
}

int Database::deleteRoute(int route_id) {
    std::string query = "DELETE FROM routes WHERE route_id = " + std::to_string(route_id) + ";";
    if (executeQuery(query) != SQLITE_OK) {
        std::cerr << "Failed to delete route.\n";
        return SQLITE_ERROR;
    }
    return SQLITE_OK;
}

std::vector<std::string> Database::readRoutes() {
    std::vector<std::string> routes;
    const char* query = R"(
        SELECT routes.route_id, trains.train_number, s1.name AS start_station, s2.name AS end_station,
               routes.departure_time, routes.arrival_time
        FROM routes
        JOIN trains ON routes.train_id = trains.train_id
        JOIN stations AS s1 ON routes.start_station_id = s1.station_id
        JOIN stations AS s2 ON routes.end_station_id = s2.station_id
        ORDER BY routes.route_id;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch routes: " << sqlite3_errmsg(db) << std::endl;
        return routes;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int route_id = sqlite3_column_int(stmt, 0);
        std::string train_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string start_station = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string end_station = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string departure_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::string arrival_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        routes.push_back("Route ID: " + std::to_string(route_id) +
                         ", Train: " + train_number +
                         ", Start Station: " + start_station +
                         ", End Station: " + end_station +
                         ", Departure: " + departure_time +
                         ", Arrival: " + arrival_time);
    }

    sqlite3_finalize(stmt);
    return routes;
}

bool Database::trainExists(int train_id) {
    std::string query = "SELECT 1 FROM trains WHERE train_id = " + std::to_string(train_id) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error checking train existence: " << sqlite3_errmsg(db) << "\n";
        return false;
    }
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

bool Database::stationExists(int station_id) {
    std::string query = "SELECT 1 FROM stations WHERE station_id = " + std::to_string(station_id) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error checking station existence: " << sqlite3_errmsg(db) << "\n";
        return false;
    }
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

int Database::createTicket(int place_id, int route_id, const std::string& passenger_name, const std::string& purchase_time) {
    std::string query = "INSERT INTO tickets (place_id, route_id, passenger_name, purchase_time) VALUES ("
                        + std::to_string(place_id) + ", "
                        + std::to_string(route_id) + ", '"
                        + passenger_name + "', '"
                        + purchase_time + "');";
    return executeQuery(query);
}

int Database::deleteTicket(int ticket_id) {
    std::string query = "DELETE FROM tickets WHERE ticket_id = " + std::to_string(ticket_id) + ";";
    return executeQuery(query);
}

std::vector<std::string> Database::readTickets() {
    std::vector<std::string> tickets;
    const char* query = "SELECT ticket_id, passenger_name, purchase_time, place_id, route_id FROM tickets;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch tickets: " << sqlite3_errmsg(db) << std::endl;
        return tickets;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int ticket_id = sqlite3_column_int(stmt, 0);
        std::string passenger_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string purchase_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int place_id = sqlite3_column_int(stmt, 3);
        int route_id = sqlite3_column_int(stmt, 4);

        tickets.push_back("Ticket ID: " + std::to_string(ticket_id) + ", Passenger: " + passenger_name +
                          ", Purchase Time: " + purchase_time + ", Place ID: " + std::to_string(place_id) +
                          ", Route ID: " + std::to_string(route_id));
    }
    sqlite3_finalize(stmt);
    return tickets;
}

std::vector<std::string> Database::getAvailablePlaces(int route_id) {
    std::vector<std::string> places;
    std::string query = "SELECT p.place_id, p.number FROM places p "
                        "LEFT JOIN tickets t ON p.place_id = t.place_id "
                        "WHERE t.place_id IS NULL AND p.carriage_id IN ("
                        "  SELECT carriage_id FROM carriages WHERE train_id = ("
                        "    SELECT train_id FROM routes WHERE route_id = " + std::to_string(route_id) + "));";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch places: " << sqlite3_errmsg(db) << std::endl;
        return places;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int place_id = sqlite3_column_int(stmt, 0);
        int number = sqlite3_column_int(stmt, 1);

        places.push_back("Place ID: " + std::to_string(place_id) + ", Number: " + std::to_string(number));
    }
    sqlite3_finalize(stmt);
    return places;
}

std::vector<std::string> Database::getRoutes() {
    std::vector<std::string> routes;
    const char* query = "SELECT route_id, train_id, start_station_id, end_station_id, departure_time, arrival_time FROM routes;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch routes: " << sqlite3_errmsg(db) << std::endl;
        return routes;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int route_id = sqlite3_column_int(stmt, 0);
        int train_id = sqlite3_column_int(stmt, 1);
        int start_station_id = sqlite3_column_int(stmt, 2);
        int end_station_id = sqlite3_column_int(stmt, 3);
        std::string departure_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::string arrival_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        routes.push_back("Route ID: " + std::to_string(route_id) + ", Train ID: " + std::to_string(train_id) +
                         ", Start Station: " + std::to_string(start_station_id) +
                         ", End Station: " + std::to_string(end_station_id) +
                         ", Departure: " + departure_time + ", Arrival: " + arrival_time);
    }
    sqlite3_finalize(stmt);
    return routes;
}
