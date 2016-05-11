#include <iostream>
#include "keyschedule.h"
#include "encrypt.h"


int main(int argc, char **argv)
{
	std::bitset<64> testkey(0x133457799BBCDFF1);
	std::bitset<64> message(0x0123456789ABCDEF);

	keyschedule keys(testkey);

	for (int i = 0; i <16; i++)
	{
		std::cout << "Key " << i + 1 << ":\t" << keys[i] << std::endl;
	}

	std::cout << std::endl;

	encrypt enc(message, keys, true);


	return 0;
}