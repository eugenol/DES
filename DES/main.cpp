#include <iostream>
#include <vector>
#include <string>
#include "DES.h"
#include "bitsetToText.h"


int main(int argc, char **argv)
{
	std::bitset<64> testkey(0x133457799BBCDFF1);
	std::bitset<64> message(0x0123456789ABCDEF);
	std::bitset<64> message2(0x85E813540F0AB405);
	std::bitset<64> result;

	std::string res = encrypt_string("HELLO", "TEST");

	result = encrypt(message, testkey);

	std::cout <<std::hex<< result.to_ullong() << std::endl;

	std::cout << std::hex << key_string_to_bitset("HELLO") << std::endl;

	return 0;
}