#include <iostream>
#include "keyschedule.h"


int main(int argc, char **argv)
{
	std::bitset<64> testkey(0x133457799BBCDFF1);
	keyschedule keys(testkey);

	for (int i = 0; i <16; i++)
	{
		std::cout << "Key " << i + 1 << ":\t" << keys[i] << std::endl;
	}

	return 0;
}