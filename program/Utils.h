#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <openssl/sha.h>

void handleInvalidInput();

void clearScreen();

void pressToContinue();

std::string hashPassword(const std::string& password);
#endif // UTILS_H
