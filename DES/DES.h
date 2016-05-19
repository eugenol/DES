#pragma once
#include <bitset>
#include <string>
#include "keyschedule.h"

std::bitset<32> feistel(std::bitset<32> Rn, std::bitset<48> kn);
std::bitset<64> do_DES(std::bitset<64> msg, keyschedule key);

void encrypt_block(unsigned char *block, keyschedule key);
