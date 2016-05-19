#include "DES.h"

std::bitset<64> do_DES(std::bitset<64> msg, keyschedule keys)
{

	//Initial permutation Table
	int IP[64] = {	58,	50,	42,	34,	26,	18,	10,	2,
					60,	52,	44,	36,	28,	20,	12,	4,
					62,	54,	46,	38,	30,	22,	14,	6,
					64,	56,	48,	40,	32,	24,	16,	8,
					57,	49,	41,	33,	25,	17,	9,	1,
					59,	51,	43,	35,	27,	19,	11,	3,
					61,	53,	45,	37,	29,	21,	13,	5,
					63,	55,	47,	39,	31,	23,	15,	7};
	//Inverse permutation table
	int IP_inverse[64] = {	40,	8,	48,	16,	56,	24,	64,	32,
							39,	7,	47,	15,	55,	23,	63,	31,
							38,	6,	46,	14,	54,	22,	62,	30,
							37,	5,	45,	13,	53,	21,	61,	29,
							36,	4,	44,	12,	52,	20,	60,	28,
							35,	3,	43,	11,	51,	19,	59,	27,
							34,	2,	42,	10,	50,	18,	58,	26,
							33,	1,	41,	9,	49,	17,	57,	25};


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
		R0 = swap^feistel(R0, keys[i]); // call fiestel function
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

std::bitset<32> feistel(std::bitset<32> Rn, std::bitset<48> kn)
{
	//Expansion Table
	int E[48] = {	32,	1,	2,	3,	4,	5,
					4,	5,	6,	7,	8,	9,
					8,	9,	10,	11,	12,	13,
					12,	13,	14,	15,	16,	17,
					16,	17,	18,	19,	20,	21,
					20,	21,	22,	23,	24,	25,
					24,	25,	26,	27,	28,	29,
					28,	29,	30,	31,	32,	1 };

	//S BOXES
	unsigned int SBOX[8][64] = { {	14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
									0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
									4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
									15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13},

								{	15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
									3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
									0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
									13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9},

								{	10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
									13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
									13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
									1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12},

								{	7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
									13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
									10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
									3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14},

								{	2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
									14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
									4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
									11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3},

								{	12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
									10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
									9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
									4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13},

								{	4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
									13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
									1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
									6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12},

								{	13	,2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
									1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
									7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
									2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11}};

	//Permutation Table
	int P[32] = {	16,	7,	20,	21,
					29,	12,	28,	17,
					1,	15,	23,	26,
					5,	18,	31,	10,
					2,	8,	24,	14,
					32,	27,	3,	9,
					19,	13,	30,	6,
					22,	11,	4,	25};

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

	expanded ^= kn; //xor with key;

	//Split up into 8 parts of 6 bits each
	for (int i = 0; i < 8;++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			B[i][5 - j] = expanded[47 - (6 * i + j)];
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
/*
Encrypts a block of 8 characters using DES
This step converts the 8 characters o a 64 bit
bitset, does the encryption, and then converts
the bitset back into 8 characters
unsigned char has to be used, otherwise the characters that
are > 128 are interpreted as negative numbers, and this messes
up the conversion to bits.
*/
void encrypt_block(unsigned char *block, keyschedule key)
{

	std::bitset<64> bitmessage; //message as 64bit
	std::bitset<64> enc_res;	//result of encryption
	
	//convert characters to bits
	for (int j = 0; j < 8;++j)
	{
		std::bitset<64> temp((unsigned int)block[j]);
		bitmessage <<= 8;
		bitmessage |= temp;
	}

	enc_res = do_DES(bitmessage, key); //encrypt/decrypt

	//convert 64bit bitset into 8 8bit bitsets
	std::bitset<8> parts[8];
	for (int j = 0; j < 8; ++j)
	{
		for (int k = 0; k < 8; ++k)
		{

			parts[7 - j][k] = enc_res[j * 8 + k];
		}
	}
	//convert 8 bit bitsets to characters
	for (int j = 0; j < 8; ++j)
	{
		unsigned char c;
		c = (unsigned char)parts[j].to_ulong();
		block[j] = c;
	}
}