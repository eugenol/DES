#include <iostream>
#include "keyschedule.h"
#include "DES.h"


int main(int argc, char **argv)
{
	std::bitset<64> testkey(0x133457799BBCDFF1);
	std::bitset<64> message(0x0123456789ABCDEF);
	std::bitset<64> message2(0x85E813540F0AB405);

	keyschedule keys(testkey);

	for (int i = 0; i <16; i++)
	{
		std::cout << "Key " << i + 1 << ":\t" << keys[i] << std::endl;
	}

	std::cout << std::endl;

	DES enc(message, keys);
	DES dec(message2, keys);

	std::cout << std::hex << enc.encrypt().to_ullong() << std::endl;
	std::cout << std::hex << dec.decrypt().to_ullong() << std::endl;

	return 0;
}