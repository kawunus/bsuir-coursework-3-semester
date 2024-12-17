INSERT INTO Trains (name) VALUES
    ('001'),
    ('002'),
    ('003');

INSERT INTO Employees (name, position, train_id) VALUES 
    ('Driver', 'Vasily Moroz', 1),
    ('Driver', 'Daniil Prudnikov', 2),
    ('Driver', 'Ivan Korzun', 3);

INSERT INTO Cars (train_id, car_type) VALUES 
    (1, 'Sleeper'),
    (1, 'Coupe'),
    (1, 'Economy'),
    (2, 'Sleeper'),
    (2, 'Coupe'),
    (2, 'Economy'),
    (3, 'Sleeper'),
    (3, 'Coupe'),
    (3, 'Economy');

INSERT INTO Seats (car_id, seat_number, is_occupied) VALUES
    (1, 1, False), (1, 2, False), (1, 3, False), (1, 4, False), (1, 5, False),
    (1, 6, False), (1, 7, False), (1, 8, False), (1, 9, False), (1, 10, False),
    (1, 11, False), (1, 12, False), (1, 13, False), (1, 14, False), (1, 15, False),
    (1, 16, False), (1, 17, False), (1, 18, False), (1, 19, False), (1, 20, False),

    (2, 1, False), (2, 2, False), (2, 3, False), (2, 4, False), (2, 5, False),
    (2, 6, False), (2, 7, False), (2, 8, False), (2, 9, False), (2, 10, False),
    (2, 11, False), (2, 12, False), (2, 13, False), (2, 14, False), (2, 15, False),
    (2, 16, False), (2, 17, False), (2, 18, False), (2, 19, False), (2, 20, False),

    (3, 1, False), (3, 2, False), (3, 3, False), (3, 4, False), (3, 5, False),
    (3, 6, False), (3, 7, False), (3, 8, False), (3, 9, False), (3, 10, False),
    (3, 11, False), (3, 12, False), (3, 13, False), (3, 14, False), (3, 15, False),
    (3, 16, False), (3, 17, False), (3, 18, False), (3, 19, False), (3, 20, False),

    (4, 1, False), (4, 2, False), (4, 3, False), (4, 4, False), (4, 5, False),
    (4, 6, False), (4, 7, False), (4, 8, False), (4, 9, False), (4, 10, False),
    (4, 11, False), (4, 12, False), (4, 13, False), (4, 14, False), (4, 15, False),
    (4, 16, False), (4, 17, False), (4, 18, False), (4, 19, False), (4, 20, False),

    (5, 1, False), (5, 2, False), (5, 3, False), (5, 4, False), (5, 5, False),
    (5, 6, False), (5, 7, False), (5, 8, False), (5, 9, False), (5, 10, False),
    (5, 11, False), (5, 12, False), (5, 13, False), (5, 14, False), (5, 15, False),
    (5, 16, False), (5, 17, False), (5, 18, False), (5, 19, False), (5, 20, False),

    (6, 1, False), (6, 2, False), (6, 3, False), (6, 4, False), (6, 5, False),
    (6, 6, False), (6, 7, False), (6, 8, False), (6, 9, False), (6, 10, False),
    (6, 11, False), (6, 12, False), (6, 13, False), (6, 14, False), (6, 15, False),
    (6, 16, False), (6, 17, False), (6, 18, False), (6, 19, False), (6, 20, False),

    (4, 1, False), (4, 2, False), (4, 3, False), (4, 4, False), (4, 5, False),
    (4, 6, False), (4, 7, False), (4, 8, False), (4, 9, False), (4, 10, False),
    (4, 11, False), (4, 12, False), (4, 13, False), (4, 14, False), (4, 15, False),
    (4, 16, False), (4, 17, False), (4, 18, False), (4, 19, False), (4, 20, False),

    (5, 1, False), (5, 2, False), (5, 3, False), (5, 4, False), (5, 5, False),
    (5, 6, False), (5, 7, False), (5, 8, False), (5, 9, False), (5, 10, False),
    (5, 11, False), (5, 12, False), (5, 13, False), (5, 14, False), (5, 15, False),
    (5, 16, False), (5, 17, False), (5, 18, False), (5, 19, False), (5, 20, False),

    (6, 1, False), (6, 2, False), (6, 3, False), (6, 4, False), (6, 5, False),
    (6, 6, False), (6, 7, False), (6, 8, False), (6, 9, False), (6, 10, False),
    (6, 11, False), (6, 12, False), (6, 13, False), (6, 14, False), (6, 15, False),
    (6, 16, False), (6, 17, False), (6, 18, False), (6, 19, False), (6, 20, False);