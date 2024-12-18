#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include "../Utils.h"

using namespace std;

class Database {
private:
    sqlite3 *db;

    int executeQuery(const std::string &query);

public:
    Database();

    bool openDatabase(const std::string &dbName);

    ~Database();

    sqlite3 *getDatabase();

    int createLocation(const std::string &name, const std::string &city);

    int deleteLocation(int station_id);

    std::vector<std::string> readLocations();

    int createTrain(const std::string &train_number, const std::string &type);

    int deleteTrain(int train_id);

    std::vector<std::string> readTrains();

    int createCarriage(int train_id, int number, const std::string &type);

    int deleteCarriage(int carriage_id);

    std::vector<std::string> readCarriages();

    std::vector<int> getTrainIds();

    std::vector<int> getCarriageIds(int train_id);

    std::vector<std::string> readPlaces(int carriage_id);

    int createPlace(int carriage_id, int number, const std::string &status);

    int deletePlace(int place_id);

    int updatePlaceStatus(int place_id, const std::string &status);

    int createRoute(int train_id, int start_station_id, int end_station_id, const std::string &departure_time,
                    const std::string &arrival_time);

    int deleteRoute(int route_id);

    std::vector<std::string> readRoutes();

    bool trainExists(int train_id);

    bool stationExists(int station_id);

    int createTicket(int place_id, int route_id, int passenger_id, const std::string &purchase_time);

    int deleteTicket(int ticket_id);

    std::vector<std::string> readTickets();

    std::vector<std::string> getAvailablePlaces(int route_id);

    std::vector<std::string> getRoutes();

    int login(const std::string &email, const std::string &password);

    bool registerUser(const std::string &name, const std::string &email, const std::string &password);

    bool getUserByEmail(const std::string &email);

    bool isAdmin(const std::string &email);

    std::string getUserNameByEmail(const std::string &email);

    std::string getPassengerName(int passenger_id);

    std::vector<std::string> readAllPassengers();

    int getUserIdByEmail(const std::string &email);

    std::vector<std::tuple<int, int, int, std::string> > getTicketsByUserId(int userId);
};

#endif // DATABASE_H
