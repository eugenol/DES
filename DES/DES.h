#pragma once
#include <bitset>
#include <string>
#include "keyschedule.h"

std::bitset<32> feistel(std::bitset<32> Rn, std::bitset<48> kn);
std::bitset<64> do_DES(std::bitset<64> msg, keyschedule key);

std::bitset<64> encrypt(std::bitset<64> msg, std::bitset<64> key);
std::bitset<64> decrypt(std::bitset<64> msg, std::bitset<64> key);

std::string encrypt_string(std::string message, std::string key);
std::string decrypt_string(std::string message, std::string key);

std::bitset<64> key_string_to_bitset(std::string key);

