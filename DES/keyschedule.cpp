#include "keyschedule.h"

keyschedule::keyschedule(std::bitset<64> key)
{
	std::bitset<56> keyplus;
	std::bitset<28> C0;
	std::bitset<28> D0;
	std::bitset<28> Cn[16];
	std::bitset<28> Dn[16];
	std::bitset<56> CnDn[16];

	// Apply PC-1 to key
	for(int i = 0; i<56; i++)
	{
		keyplus[55-i] = key[64-PC_1[i]];
	}

	//split into left and right keys
	for (int i = 0; i < 28; ++i)
	{
		C0[i] = keyplus[i+28];
		D0[i] = keyplus[i];
	}

	// rotate left and right keys
	Cn[0] = C0;
	Dn[0] = D0;

	for (int i = 0; i < 16; ++i)
	{
		rotate_left(Cn[i], shifts[i]);
		rotate_left(Dn[i], shifts[i]);

		if (i < 15)
		{
			Cn[i + 1] = Cn[i];
			Dn[i + 1] = Dn[i];
		}
	}

	//concatenate left and right keys
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			CnDn[i][j+28] = Cn[i][j];
			CnDn[i][j] = Dn[i][j];
		}
	}

	//apply PC-2
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 48; ++j)
		{
			keys[i][47-j] = CnDn[i][56-PC_2[j]];
		}
	}
}


keyschedule::~keyschedule()
{
}


void keyschedule::rotate_left(std::bitset<28> &b, int m)
{
	b = b << m | b >> (28 - m);
}

std::bitset<48> keyschedule::operator[](std::size_t idx)
{
	return keys[idx];
};