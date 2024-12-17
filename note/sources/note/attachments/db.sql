CREATE TABLE Trains (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name VARCHAR(100) NOT NULL
);

CREATE TABLE Cars (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      train_id INTEGER NOT NULL,
                      car_type VARCHAR(50) NOT NULL,
                      FOREIGN KEY (train_id) REFERENCES Trains(id)
);

CREATE TABLE Seats (
                       id INTEGER PRIMARY KEY AUTOINCREMENT,
                       car_id INTEGER NOT NULL,
                       seat_number INTEGER NOT NULL,
                       is_occupied INTEGER NOT NULL,
                       FOREIGN KEY (car_id) REFERENCES Cars(id)
);

CREATE TABLE Stations (
                          id INTEGER PRIMARY KEY AUTOINCREMENT,
                          name VARCHAR(100) NOT NULL,
                          location VARCHAR(100)
);

CREATE TABLE Tickets (
                         id INTEGER PRIMARY KEY AUTOINCREMENT,
                         seat_id INTEGER NOT NULL,
                         train_id INTEGER NOT NULL,
                         passenger_name VARCHAR(100) NOT NULL,
                         departure_station_id INTEGER NOT NULL,
                         arrival_station_id INTEGER NOT NULL,
                         price REAL NOT NULL,
                         departure_time DATETIME NOT NULL,
                         arrival_time DATETIME NOT NULL,
                         FOREIGN KEY (seat_id) REFERENCES Seats(id),
                         FOREIGN KEY (train_id) REFERENCES Trains(id),
                         FOREIGN KEY (departure_station_id) REFERENCES Stations(id),
                         FOREIGN KEY (arrival_station_id) REFERENCES Stations(id)
);

CREATE TABLE Employees (
                           id INTEGER PRIMARY KEY AUTOINCREMENT,
                           name VARCHAR(100) NOT NULL,
                           position VARCHAR(50) NOT NULL,
                           train_id INTEGER,
                           FOREIGN KEY (train_id) REFERENCES Trains(id)
);