#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "DES.h"
#include "bitsetToText.h"


int main(int argc, char **argv)
{
	std::bitset<64> testkey(0x0f1571c947d9e859);
	std::bitset<64> message(0x02468aceeca86420);
	std::bitset<64> message2(0xda02ce3a89ecac3b);
	std::bitset<64> result;

	std::string test("Hello, how are you today?");
	std::cout << test << std::endl;
	test.erase(5, 5);
	std::cout << test << std::endl;


	
	std::string res = encrypt_string("HELLO, THIS IS A TEST", "TEST");
	std::cout << res << "\n";
	std::string res2 = decrypt_string(res, "TEST");
	std::cout << res2 << "\n";

	//result = encrypt(message, testkey);
	//result = decrypt(message2, testkey);

	//std::cout <<std::setw(16)<<std::setfill('0')<<std::hex<< result.to_ullong() << std::endl;

	//std::cout << std::hex << key_string_to_bitset("HELLO") << std::endl;

	return 0;
}