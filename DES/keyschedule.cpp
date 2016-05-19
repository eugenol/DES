#include "keyschedule.h"
#include <algorithm>
#include <iterator>

//Constructor with bitset
keyschedule::keyschedule(std::bitset<64> key)
{
	do_keyschedule(key);
}
//Constructor with string
keyschedule::keyschedule(std::string key)
{
	int keylen = key.length();
	int padlength;
	char tempKey[8];
	unsigned char* keyPtr;

	//pad the key if it is less than 8 characters, else just truncate it
	if (keylen < 8)
	{
		padlength = 8 - keylen % 8; //padding length

		int keylength_new = keylen + padlength; 

		for (int i = keylen; i < keylength_new; ++i)
		{
			key.insert(key.end(), (char)padlength); //pad
		}
	}
	//copy to a character array, only the first 8 characters
	for (int i = 0; i < 8; ++i)
	{
		strncpy(tempKey, key.c_str(), 8);
	}
	// to avoid signed/unsigned conversion problems, cast to unsigned char
	keyPtr = (unsigned char*)tempKey;

	std::bitset<64> bitkey;

	for (int j = 0; j < 8;++j)
	{
		std::bitset<64> temp = keyPtr[j];
		bitkey <<= 8;
		bitkey |= temp;
	}

	do_keyschedule(bitkey);
}

//Default Constructor
keyschedule::keyschedule( )
{

}
//Destructor
keyschedule::~keyschedule()
{
}
//Key Schedule algorithm
void keyschedule::do_keyschedule(std::bitset<64> key)
{
	std::bitset<56> keyplus;	//After PC-1
	std::bitset<28> C0;			//Left half
	std::bitset<28> D0;			//Right half
	std::bitset<28> Cn[16];		// all 16 left halves
	std::bitset<28> Dn[16];		// all 16 right halves
	std::bitset<56> CnDn[16];	// all 16 keys before PC-2

	// Apply PC-1 to key
	for (int i = 0; i<56; i++)
	{
		keyplus[55 - i] = key[64 - PC_1[i]];
	}

	//split into left and right keys
	for (int i = 0; i < 28; ++i)
	{
		C0[i] = keyplus[i + 28];
		D0[i] = keyplus[i];
	}


	Cn[0] = C0;
	Dn[0] = D0;
	// rotate left and right keys
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
			CnDn[i][j + 28] = Cn[i][j];
			CnDn[i][j] = Dn[i][j];
		}
	}

	//apply PC-2
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 48; ++j)
		{
			keys[i][47 - j] = CnDn[i][56 - PC_2[j]];
		}
	}
}
// rotate keys left by m
void keyschedule::rotate_left(std::bitset<28> &b, int m)
{
	b = b << m | b >> (28 - m);
}
//overloaded operator
std::bitset<48> keyschedule::operator[](std::size_t idx)
{
	return keys[idx];
};
//reverse for decryption
void keyschedule::reverse()
{
	std::reverse(std::begin(keys), std::end(keys));
}
