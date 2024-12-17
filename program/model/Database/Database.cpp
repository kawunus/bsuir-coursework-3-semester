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
    sqlite3_stmt *stmt;
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
    std::string query = "SELECT place_id, number, status FROM places WHERE carriage_id = " + std::to_string(carriage_id)
                        + ";";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int place_id = sqlite3_column_int(stmt, 0);
            int number = sqlite3_column_int(stmt, 1);
            const char *status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            places.emplace_back(
                "ID: " + std::to_string(place_id) + ", Number: " + std::to_string(number) + ", Status: " +
                std::string(status));
        }
    }
    sqlite3_finalize(stmt);
    return places;
}

int Database::createPlace(int carriage_id, int number, const std::string &status) {
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

int Database::updatePlaceStatus(int place_id, const std::string &status) {
    std::string query = "UPDATE places SET status = '" + status + "' WHERE place_id = " + std::to_string(place_id) +
                        ";";
    return executeQuery(query);
}

int Database::createRoute(int train_id, int start_station_id, int end_station_id, const std::string &departure_time,
                          const std::string &arrival_time) {
    std::string query =
            "INSERT INTO routes (train_id, start_station_id, end_station_id, departure_time, arrival_time) VALUES ("
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
    const char *query = R"(
        SELECT routes.route_id, trains.train_number, s1.name AS start_station, s2.name AS end_station,
               routes.departure_time, routes.arrival_time
        FROM routes
        JOIN trains ON routes.train_id = trains.train_id
        JOIN stations AS s1 ON routes.start_station_id = s1.station_id
        JOIN stations AS s2 ON routes.end_station_id = s2.station_id
        ORDER BY routes.route_id;
    )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch routes: " << sqlite3_errmsg(db) << std::endl;
        return routes;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int route_id = sqlite3_column_int(stmt, 0);
        std::string train_number = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string start_station = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string end_station = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        std::string departure_time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        std::string arrival_time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

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
    sqlite3_stmt *stmt;
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
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error checking station existence: " << sqlite3_errmsg(db) << "\n";
        return false;
    }
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

int Database::createTicket(int place_id, int route_id, int passenger_id, const std::string &purchase_time) {
    std::string query = "INSERT INTO tickets (place_id, route_id, passenger_id, purchase_time) VALUES ("
                        + std::to_string(place_id) + ", "
                        + std::to_string(route_id) + ", "
                        + std::to_string(passenger_id) + ", '"
                        + purchase_time + "');";
    return executeQuery(query);
}


int Database::deleteTicket(int ticket_id) {
    std::string query = "DELETE FROM tickets WHERE ticket_id = " + std::to_string(ticket_id) + ";";
    return executeQuery(query);
}

std::vector<std::string> Database::readTickets() {
    std::vector<std::string> tickets;
    const char *query = R"(
        SELECT t.ticket_id, t.passenger_id, t.purchase_time, t.place_id,
               r.route_id, start_station.name AS start_station_name,
               end_station.name AS end_station_name
        FROM tickets t
        JOIN routes r ON t.route_id = r.route_id
        JOIN stations start_station ON r.start_station_id = start_station.station_id
        JOIN stations end_station ON r.end_station_id = end_station.station_id;
    )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch tickets: " << sqlite3_errmsg(db) << std::endl;
        return tickets;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int ticket_id = sqlite3_column_int(stmt, 0);
        int passenger_id = sqlite3_column_int(stmt, 1);
        std::string purchase_time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        int place_id = sqlite3_column_int(stmt, 3);
        int route_id = sqlite3_column_int(stmt, 4);
        std::string start_station_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        std::string end_station_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));

        // Получаем имя пассажира по его passenger_id
        std::string passenger_name = getPassengerName(passenger_id);

        tickets.push_back("Ticket ID: " + std::to_string(ticket_id) + ", Passenger: " + passenger_name +
                          ", Purchase Time: " + purchase_time + ", Place ID: " + std::to_string(place_id) +
                          ", Route ID: " + std::to_string(route_id) +
                          ", From: " + start_station_name + " To: " + end_station_name);
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

    sqlite3_stmt *stmt;
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
    const char *query =
        R"(
        SELECT r.route_id, r.train_id,
               s1.name AS start_station,
               s2.name AS end_station,
               r.departure_time, r.arrival_time
        FROM routes r
        JOIN stations s1 ON r.start_station_id = s1.station_id
        JOIN stations s2 ON r.end_station_id = s2.station_id;
        )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch routes: " << sqlite3_errmsg(db) << std::endl;
        return routes;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int route_id = sqlite3_column_int(stmt, 0);
        int train_id = sqlite3_column_int(stmt, 1);
        std::string start_station = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string end_station = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        std::string departure_time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        std::string arrival_time = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

        routes.push_back("Route ID: " + std::to_string(route_id) +
                         ", Train ID: " + std::to_string(train_id) +
                         ", Start Station: " + start_station +
                         ", End Station: " + end_station +
                         ", Departure: " + departure_time +
                         ", Arrival: " + arrival_time);
    }
    sqlite3_finalize(stmt);
    return routes;
}


int Database::login(const std::string &email, const std::string &password) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT entity_id, password FROM entities WHERE email = ?";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Ошибка связывания email: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int userId = -1;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int dbId = sqlite3_column_int(stmt, 0);
        const unsigned char *dbPassword = sqlite3_column_text(stmt, 1);
        if (dbPassword) {
            std::string dbPasswordStr(reinterpret_cast<const char *>(dbPassword));
            if (password == dbPasswordStr) {
                userId = dbId;
            } else {
                std::cerr << "\nПароль не совпадает!" << std::endl;
            }
        }
    } else {
        std::cerr << "Пользователь с таким email не найден!" << std::endl;
    }

    sqlite3_finalize(stmt);
    return userId;
}


bool Database::registerUser(const std::string &name, const std::string &email, const std::string &password) {
    sqlite3_stmt *stmt;
    std::string query = "INSERT INTO entities (name, email, password) VALUES (?, ?, ?)";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Ошибка связывания данных: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
       // std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Database::isAdmin(const std::string &email) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT is_admin FROM entities WHERE email = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    bool is_admin = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_admin = sqlite3_column_int(stmt, 0) == 1;
    }

    sqlite3_finalize(stmt);
    return is_admin;
}

bool Database::getUserByEmail(const std::string &email) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT entity_id, name, email, is_admin FROM entities WHERE email = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    bool user_found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user_found = true;
        int entity_id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string user_email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        bool is_admin = sqlite3_column_int(stmt, 3) == 1;
    }

    sqlite3_finalize(stmt);
    return user_found;
}

std::string Database::getUserNameByEmail(const std::string &email) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT name FROM entities WHERE email = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    std::string name;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);

    return name;
}

int Database::getUserIdByEmail(const std::string &email) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT entity_id FROM entities WHERE email = ?;";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    int userId = -1;
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return userId;
}

std::string Database::getPassengerName(int passenger_id) {
    std::string name;
    std::string query = "SELECT name FROM entities WHERE entity_id = " + std::to_string(passenger_id) + ";";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch passenger name: " << sqlite3_errmsg(db) << std::endl;
        return name;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    }
    sqlite3_finalize(stmt);
    return name;
}

std::vector<std::string> Database::readAllPassengers() {
    std::vector<std::string> passengers;
    const char *query = "SELECT entity_id, name, email FROM entities;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch passengers: " << sqlite3_errmsg(db) << std::endl;
        return passengers;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int entity_id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        passengers.push_back("ID: " + std::to_string(entity_id) + ", Name: " + name + ", Email: " + email);
    }

    sqlite3_finalize(stmt);
    return passengers;
}

std::vector<std::tuple<int, int, int, std::string>> Database::getTicketsByUserId(int userId) {
    sqlite3_stmt *stmt;
    std::string query = R"(
        SELECT tickets.ticket_id, tickets.route_id, tickets.place_id, tickets.purchase_time
        FROM tickets
        WHERE tickets.passenger_id = ?;
    )";

    std::vector<std::tuple<int, int, int, std::string>> tickets;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return tickets;
    }

    sqlite3_bind_int(stmt, 1, userId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int ticketId = sqlite3_column_int(stmt, 0);
        int routeId = sqlite3_column_int(stmt, 1);
        int placeId = sqlite3_column_int(stmt, 2);
        std::string purchaseTime = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

        tickets.emplace_back(ticketId, routeId, placeId, purchaseTime);
    }

    sqlite3_finalize(stmt);

    return tickets;
}
