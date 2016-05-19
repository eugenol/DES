/*
This file contains the main interfaces for using the DES implementation

*/

#pragma once
#include <string>
#include "DES.h"
#include "keyschedule.h"

std::string encrypt_string(std::string message, std::string key);
std::string decrypt_string(std::string message, std::string key);

void encrypt_file(std::string message, std::string key);
void decrypt_file(std::string message, std::string key);

std::bitset<64> encrypt_bits(std::bitset<64> message, std::bitset<64> key);
std::bitset<64> decrypt_bits(std::bitset<64> message, std::bitset<64> key);