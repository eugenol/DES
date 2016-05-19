#pragma once
#include <string>
#include "DES.h"

void encrypt_file(std::string message, std::string key);
void decrypt_file(std::string message, std::string key);