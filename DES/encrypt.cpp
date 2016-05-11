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
	std::bitset<6> B[8];
	std::bitset<4> S[8];


	//Use expansion table to expand Rn to 32 bits
	for (int i = 0; i < 48;++i)
	{
		expanded[47 - i] = Rn[32 - E[i]];
	}

	std::cout << "Expanded " << expanded << std::endl;

	expanded ^= kn;

	std::cout << "XOR with key " << expanded << std::endl;

	for (int i = 0; i < 8;++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			B[i][5-j] = expanded[47-(6*i+j)];
		}
		std::cout << "B" <<i+1<<": "<< B[i] << std::endl;
	}

	for (int i = 0; i < 8;++i)
	{
		std::bitset<2> outer_bits;
		std::bitset<4> inner_bits;

		outer_bits[1] = B[i][5];
		outer_bits[0] = B[i][0];

		std::cout << "Outer Bits " << i + 1 << ": " << outer_bits << std::endl;

		inner_bits[3] = B[i][4];
		inner_bits[2] = B[i][3];
		inner_bits[1] = B[i][2];
		inner_bits[0] = B[i][1];

		std::cout << "Inner Bits " << i + 1 << ": " << inner_bits << std::endl;

		std::cout << "Row:" << outer_bits.to_ulong() << std::endl;
		std::cout << "Column:" << inner_bits.to_ulong() << std::endl;
		std::cout << "Value:" << SBOX[i][4 * outer_bits.to_ulong() + inner_bits.to_ulong()] << std::endl;

		std::bitset<4> temp_s(SBOX[i][4 * outer_bits.to_ulong() + inner_bits.to_ulong()]);

		std::cout << "Temp S" << i + 1 << ": " << temp_s << std::endl;

		S[i] = temp_s;

		std::cout << "S" << i + 1 << ": " << S[i] << std::endl;
	}



	return Rn;
}