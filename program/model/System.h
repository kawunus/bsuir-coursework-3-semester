#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>

class System {
private:
    bool isWork = true;

public:
    void exit();
    int login();
    void printLoginMenu();
};

#endif // SYSTEM_H
