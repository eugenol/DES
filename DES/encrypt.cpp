#include "encrypt.h"
#include <iostream>



encrypt::encrypt(std::bitset<64> msg, keyschedule keys, bool encrypt)
{
	// Apply IP1 to message
	std::bitset<64> L0R0;
	std::bitset<32> L0;
	std::bitset<32> R0;


	std::cout << "Initial message: "<<msg << std::endl;

	for (int i = 0; i<64; i++)
	{
		L0R0[63 - i] = msg[64 - IP[i]];
	}

	std::cout << "After IP: " << L0R0 << std::endl;

	for (int i = 0; i < 32; i++)
	{
		L0[i] = L0R0[i + 32];
		R0[i] = L0R0[i];
	}

	std::cout << "L0: " << L0 << std::endl;
	std::cout << "R0: " << R0 << std::endl;



	for (int i = 0; i < 16; ++i)
	{
		std::bitset<32> swap;
		swap = L0;
		L0 = R0;
		R0 = swap^feistel(R0, keys[i]);

	}

}


encrypt::~encrypt()
{
}


std::bitset<32> encrypt::feistel(std::bitset<32> Rn, std::bitset<48> kn)
{
	std::bitset<48> expanded;

	for (int i = 0; i < 48;++i)
	{

	}
}