#include "bitsetToText.h"


bitsetToText::bitsetToText(std::bitset<64> text_bits)
{
	std::bitset<8> characters[8];

	//split up into 8 parts of 8 bits each
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			characters[i][7 - j] = text_bits[63 - (8 * i + j)];
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		char temp = characters[i].to_ulong();
		text.insert(text.end(), temp);
	}
}


bitsetToText::~bitsetToText()
{
}
