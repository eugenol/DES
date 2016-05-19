#include "test.h"
#include <fstream>

void encrypt_file(std::string message, std::string key)
{
	char buffer[1024];
	int bytesRead;
	std::ifstream inFile("helloworld.exe", std::ios::in | std::ios::binary);
	std::ofstream outFile("helloworld.exe.enc", std::ios::out | std::ios::binary);

	std::bitset<64> bitkey = key_string_to_bitset(key);

	while (inFile)
	{
		inFile.read(buffer, 1024);
		if (inFile)
		{
			bytesRead = 1024;
			int size = bytesRead / 8;
			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], bitkey, true);
			}
			outFile.write(buffer, bytesRead);
		}
		else
		{
			//last block read, pad it
			bytesRead = inFile.gcount();
			int padlength = 8 - bytesRead % 8;
			int size = (bytesRead + padlength)/8;

			for (int i = bytesRead; i < bytesRead + padlength; ++i)
			{
				buffer[i] = (char)padlength;
			}

			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], bitkey, true);
			}
			outFile.write(buffer, bytesRead + padlength);
		}
	}

	inFile.close();
	outFile.close();
}

void decrypt_file(std::string message, std::string key)
{
	char buffer[1024];
	int bytesRead;
	long fileSize;
	long last_chunk;
	long current_chunk=0;
	int padlength=0;

	struct stat stat_buf;
	stat("helloworld.exe.enc", &stat_buf);
	fileSize = stat_buf.st_size;
	last_chunk = fileSize / 1024 + ((fileSize % 1024 == 0) ? 0 : 1);

	std::ifstream inFile("helloworld.exe.enc", std::ios::in | std::ios::binary);
	std::ofstream outFile("helloworld.exe", std::ios::out | std::ios::binary);

	std::bitset<64> bitkey = key_string_to_bitset(key);

	while (inFile)
	{
		inFile.read(buffer, 1024);
		current_chunk++;
		if (inFile)
		{
			bytesRead = 1024;
			int size = bytesRead / 8;
			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], bitkey, false);
			}

			if (current_chunk == last_chunk)
			{
				padlength = buffer[1023];
			}

			outFile.write(buffer, bytesRead-padlength);
		}
		else
		{
			//last block read, pad it
			bytesRead = inFile.gcount();
			int size = bytesRead / 8;

			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], bitkey, false);
			}

			if (current_chunk == last_chunk)
			{
				padlength = buffer[bytesRead-1];
			}

			outFile.write(buffer, bytesRead- padlength);
		}
	}

	inFile.close();
	outFile.close();
}