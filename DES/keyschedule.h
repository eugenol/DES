/*
This is the keyschedule for the DES Algorithm
It takes as an argument a 64bit key as a bitset
On creation of the object it will create the 16
subkeys needed for DES encryption.
To access a subkey, use the [] operator on the
object.
Bitsets are numbered from LSB to MSB, so LSB is
bitset[0], opposite from how arrays work.
*/

#pragma once
#include <bitset>
#include <string>

class keyschedule
{
private:
	std::bitset<48> keys[16]; //stores the 16 subkeys of 48bits each

							  // PC-1 Table
	int PC_1[56] = { 57,	49,	41,	33,	25,	17,	9,
		1,	58,	50,	42,	34,	26,	18,
		10,	2,	59,	51,	43,	35,	27,
		19,	11,	3,	60,	52,	44,	36,
		63,	55,	47,	39,	31,	23,	15,
		7,	62,	54,	46,	38,	30,	22,
		14,	6,	61,	53,	45,	37,	29,
		21,	13,	5,	28,	20,	12,	4 };

	//Number of shifs for each round
	int shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

	// PC-2 Table
	int PC_2[48] = { 14,	17,	11,	24,	1,	5,
		3,	28,	15,	6,	21,	10,
		23,	19,	12,	4,	26,	8,
		16,	7,	27,	20,	13,	2,
		41,	52,	31,	37,	47,	55,
		30,	40,	51,	45,	33,	48,
		44,	49,	39,	56,	34,	53,
		46,	42,	50,	36,	29,	32 };


	void rotate_left(std::bitset<28> &key, int shift); //rotate the bits left by shift amount
	void do_keyschedule(std::bitset<64> key); //actual function that does the keyschdule

public:
	keyschedule(std::bitset<64> key); //constructor with bitset
	keyschedule(std::string key); //constructor with string
	keyschedule(); //Default constructor, allows for copying object
	~keyschedule(); //Destructor
	std::bitset<48> operator[](std::size_t idx); //Access subkey by overloading
	void reverse(); //reverse keys for decryption
};

