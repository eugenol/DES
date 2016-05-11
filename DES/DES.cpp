#include "DES.h"


DES::DES(std::bitset<64> message, keyschedule key):msg(message),keys(key)
{

}


DES::~DES()
{
}


std::bitset<32> DES::feistel(std::bitset<32> Rn, std::bitset<48> kn)
{
	std::bitset<48> expanded;
	std::bitset<6> B[8];
	std::bitset<4> S[8];
	std::bitset<32> concat;
	std::bitset<32> final;


	//Use expansion table to expand Rn to 32 bits
	for (int i = 0; i < 48;++i)
	{
		expanded[47 - i] = Rn[32 - E[i]];
	}

	expanded ^= kn;

	//Split up into 8 parts of 6 bits each
	for (int i = 0; i < 8;++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			B[i][5-j] = expanded[47-(6*i+j)];
		}
	}

	//Apply S-Boxes
	for (int i = 0; i < 8;++i)
	{
		std::bitset<2> outer_bits(0UL);
		std::bitset<4> inner_bits(0UL);

		outer_bits[1] = B[i][5];
		outer_bits[0] = B[i][0];

		inner_bits[3] = B[i][4];
		inner_bits[2] = B[i][3];
		inner_bits[1] = B[i][2];
		inner_bits[0] = B[i][1];

		std::bitset<4> temp_s(SBOX[i][16 * outer_bits.to_ulong() + inner_bits.to_ulong()]);

		S[i] = temp_s;

	}

	//Concatenate after s-box is applied
	for (int i = 0; i < 8;++i)
	{
		std::bitset<32> temp(S[i].to_ulong());
		concat <<= 4;
		concat |= temp;
	}

	//Apply final permutation
	for (int i = 0; i<32; i++)
	{
		final[31 - i] = concat[32 - P[i]];
	}

	return final;
}

std::bitset<64> DES::encrypt()
{
	std::bitset<64> L0R0;
	std::bitset<64> R16L16(0UL);
	std::bitset<32> L0;
	std::bitset<32> R0;
	std::bitset<64> final;

	// Apply IP1 to message
	for (int i = 0; i<64; i++)
	{
		L0R0[63 - i] = msg[64 - IP[i]];
	}

	//Split message into left and right sections
	for (int i = 0; i < 32; i++)
	{
		L0[i] = L0R0[i + 32];
		R0[i] = L0R0[i];
	}

	//perform 16 rounds
	for (int i = 0; i < 16; ++i)
	{
		std::bitset<32> swap;
		swap = L0;
		L0 = R0;
		R0 = swap^feistel(R0, keys[i]);
	}

	//concate in reverse order (swap L and R and concatenate)
	std::bitset<64> tempR(R0.to_ulong());
	std::bitset<64> tempL(L0.to_ulong());
	R16L16 |= tempR;
	R16L16 <<= 32;
	R16L16 |= tempL;

	for (int i = 0; i<64; i++)
	{
		final[63 - i] = R16L16[64 - IP_inverse[i]];
	}

	return final;
}

std::bitset<64> DES::decrypt()
{
	std::bitset<64> dec;
	//reverse keyes
	keys.reverse();
	dec = encrypt();
	keys.reverse();
	return dec;
}