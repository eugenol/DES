#pragma once
#include <bitset>
#include <string>

class bitsetToText
{
private:
	std::string text;
public:
	bitsetToText(std::bitset<64> text_bits);
	~bitsetToText();
	std::string getText() { return text; }
};

