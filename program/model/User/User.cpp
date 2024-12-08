#include "../User.h"

void User::start() {
    std::cout << "Welcome to the station information system" << std::endl;
    if (!db.openDatabase(dbName)) {
        std::cerr << "Failed to open the database. Terminating." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
