#include "encrypt.h"



encrypt::encrypt(std::bitset<64> msg, keyschedule keys, bool encrypt)
{
	// Apply IP1 to message
	std::bitset<64> L0R0;
	std::bitset<32> L0;
	std::bitset<32> R0;

	std::bitset<32> *L;
	std::bitset<32> *R;

	for (int i = 0; i<64; i++)
	{
		L0R0[63 - i] = msg[64 - IP[i]];
	}

	for (int i = 0; i < 32; i++)
	{
		L0[i] = L0R0[i + 32];
		R0[i] = L0R0[i];
	}

	L = &L0;
	R = &R0;

	for (int i = 0; i < 16; i++)
	{

	}

}


encrypt::~encrypt()
{
}
