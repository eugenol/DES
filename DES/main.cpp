#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "interfaces.h"

using namespace std;

//function prototypes
void menu_option1();
void menu_option2();
void menu_option3();
void menu_option4();
void menu_option5();
void menu_option6();
void menu_option7();

int main(int argc, char **argv)
{
	int menu_choice;

	for (;;)
	{
		do
		{
			system("cls");
			cout << "1. Encrypt a string\n";
			cout << "2. Decrypt a string\n";
			cout << "3. View Example\n";
			cout << "4. Encrypt a file\n";
			cout << "5. Decrypt a file\n";
			cout << "6. Encrypt a hex number\n";
			cout << "7. Decrypt a hex Number\n";
			cout << "8. Exit\n>";
			cin >> menu_choice;
		} while (menu_choice < 1 || menu_choice > 8);
		system("cls");
		if (menu_choice == 1)
			menu_option1();
		if (menu_choice == 2)
			menu_option2();
		else if (menu_choice == 3)
			menu_option3();
		else if (menu_choice == 4)
			menu_option4();
		else if (menu_choice == 5)
			menu_option5();
		else if (menu_choice == 6)
			menu_option6();
		else if (menu_choice == 7)
			menu_option7();
		else if (menu_choice == 8)
			break;
	}

	return 0;
}

void menu_option1()
{
	string message;
	string key;
	string result;
	char temp;

	cin.ignore();
	cout << "Encrypt Text\n\n";
	cout << "Enter the text to encrypt > ";
	getline(cin, message);
	cout << "Enter the encryption key > ";
	getline(cin, key);
	cout << "The encrypted text is: ";
	cout << encrypt_string(message, key) << "\n\n";

	cout << "Press enter key to return to the main menu\n";
	//cin.ignore();
	temp = cin.get();
}

void menu_option2()
{
	string message;
	string key;
	string result;
	char temp;

	cin.ignore();
	cout << "Decrypt Text\n\n";
	cout << "Enter the text to decrypt > ";
	getline(cin, message);
	cout << "Enter the encryption key > ";
	getline(cin, key);
	cout << "The decrypted text is: ";
	cout << decrypt_string(message, key) << "\n\n";

	cout << "Press enter key to return to the main menu\n";
	//cin.ignore();
	temp = cin.get();
}
void menu_option3()
{
	cout << "Welcome to the demonstration!\n\n";

	string to_encrypt = "Hello, this is a test for now";
	cout << "The string to encrypt is: " <<to_encrypt << "\n";

	string key = "Password";
	cout << "The encryption key is: " << key << "\n";

	string res = encrypt_string(to_encrypt, key);

	cout << "The encrypted text is: \n";
	cout << res << "\n\n";

	cout << "The resultant text will now be decrypted\n";


	string res2 = decrypt_string(res, "Password");
	cout << "The decrypted text is: \n";
	cout << res2 << "\n\n";

	cout << "Press enter key to return to the main menu\n";
	cin.ignore();
	char temp = cin.get();
}
void menu_option4()
{
	string filename;
	string key;
	string result;
	char temp;

	cout << "Encrypt a file\n\n";

	cout << "Enter the filename of the file to encrypt > ";
	cin >> filename;
	cout << "Enter the encryption key > ";
	cin >> key;
	cout << "Encrypting "<< filename <<"...\n";
	encrypt_file(filename, key);
	cout <<filename<< " is now encrypted.\n\n";

	cout << "Press enter key to return to the main menu\n";
	cin.ignore();
	temp = cin.get();
}
void menu_option5()
{
	string filename;
	string key;
	string result;
	char temp;

	cout << "Decrypt a file\n\n";

	cout << "Enter the filename of the file to decrypt > ";
	cin >> filename;
	cout << "Enter the encryption key > ";
	cin >> key;
	cout << "Decrypting " << filename << "...\n";
	decrypt_file(filename, key);
	cout << filename << " is now decrypted.\n\n";

	cout << "Press enter key to return to the main menu\n";
	cin.ignore();
	temp = cin.get();
}

void menu_option6()
{
	unsigned long long tmp_msg, tmp_key;
	char temp;

	cin.ignore();
	cout << "Encrypt 64bit hex number\n\n";
	cout << "Enter the number to encrypt > ";
	cin >> hex >> tmp_msg;
	cout << "Enter the encryption key (64bit hex number) > ";
	cin >> hex >> tmp_key;

	
	std::bitset<64>  message(tmp_msg);
	std::bitset<64>  key(tmp_key);
	std::bitset<64>  result;

	result = encrypt_bits(message, key);

	cout << "The encrypted number is: ";
	cout <<hex<<setw(16)<<setfill('0')<< result.to_ullong() << "\n\n";

	cout << "Press enter key to return to the main menu\n";
	cin.ignore();
	temp = cin.get();
}

void menu_option7()
{
	unsigned long long tmp_msg, tmp_key;
	char temp;

	cin.ignore();
	cout << "Decrypt 64bit hex number\n\n";
	cout << "Enter the number to decrypt > ";
	cin >> hex >> tmp_msg;
	cout << "Enter the encryption key (64bit hex number) > ";
	cin >> hex >> tmp_key;


	std::bitset<64>  message(tmp_msg);
	std::bitset<64>  key(tmp_key);
	std::bitset<64>  result;

	result = decrypt_bits(message, key);

	cout << "The decrypted number is: ";
	cout << hex << setw(16) << setfill('0') << result.to_ullong() << "\n\n";

	cout << "Press enter key to return to the main menu\n";
	cin.ignore();
	temp = cin.get();
}