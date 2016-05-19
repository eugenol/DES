#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "DES.h"
#include "test.h"

using namespace std;

int main(int argc, char **argv)
{
	//int menu_choice;
	//do
	//{
	//	system("cls");
	//	cout << "1. Encrypt a string\n";
	//	cout << "2. Decrypt a string\n";
	//	cout << "3. View Example\n";
	//	cout << "4. Encrypt a file\n";
	//	cout << "5. Decrypt a file\n";
	//	cin >> menu_choice;
	//} while (menu_choice < 1 || menu_choice > 5);

	//std::bitset<64> testkey(0x0f1571c947d9e859);
	//std::bitset<64> message(0x02468aceeca86420);
	//std::bitset<64> message2(0xda02ce3a89ecac3b);
	//std::bitset<64> result;

	//std::string test("Hello, how are you today?");
	//std::cout << test << std::endl;
	//test.erase(5, 5);
	//std::cout << test << std::endl;

	encrypt_file("", "Password");
	decrypt_file("", "Password");


	std::string to_encrypt = "Hello, this a test for now";
	std::cout << to_encrypt << "\n";
	std::string res = encrypt_string(to_encrypt, "Password");
	std::cout << res << "\n";
	std::string res2 = decrypt_string(res, "Password");
	std::cout << res2 << "\n";

	//result = encrypt(message, testkey);
	//result = decrypt(message2, testkey);

	//std::cout <<std::setw(16)<<std::setfill('0')<<std::hex<< result.to_ullong() << std::endl;

	//std::cout << std::hex << key_string_to_bitset("HELLO") << std::endl;

	return 0;
}