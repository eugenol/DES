/*
This file contains the main interfaces for using the DES implementation
The following functions are available:
1. encrypt string
2. decrypt string
3. encrypt file
4. decrypt file
5. encrypt bitset
6. decrypt bitset

For encryption, the string/file is padded to be a multiple of 64bits in size
The padding used is "PKCS5 padding" and works as follows:

If the message is not a multiple of 8 characters, the message is padded to be a multiple of
8 characters. This means that 1 to 8 characters can be added. The padding is the number of
characters that was added. This aids the decryption routine, as the last byte always is the
number of padding characters to remove. This means that an encryped file is always a multiple
of 8 bytes in size.

*/
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include "interfaces.h"

std::string encrypt_string(std::string message, std::string key)
{
	keyschedule keys(key); //generate key schedule

	int mlength = message.length();
	int mlength_new, padlength;

	//pad the message
	padlength = 8 - mlength % 8;

	mlength_new = mlength + padlength;
	//pad message
	for (int i = mlength; i < mlength_new; ++i)
	{
		message.insert(message.end(), (char)padlength);
	}

	int size = mlength_new / 8;

	char *msgPtr = new char[mlength_new + 1];
	strncpy(msgPtr, message.c_str(), mlength_new + 1);
	// casting to unsigned char
	for (int i = 0; i < size; ++i)
	{
		encrypt_block((unsigned char*)&msgPtr[8 * i], keys); //encrypt
	}

	std::string retval(msgPtr);

	delete[] msgPtr;

	return retval;
}


std::string decrypt_string(std::string message, std::string key)
{
	keyschedule keys(key); //generate key schedule
	keys.reverse(); //reverse order for decryption

	int mlength = message.length();
	int padlength;
	int size = mlength / 8;

	char *msgPtr = new char[mlength + 1];
	strncpy(msgPtr, message.c_str(), mlength + 1);

	for (int i = 0; i < size; ++i)
	{
		encrypt_block((unsigned char*)&msgPtr[8 * i], keys); //decrypt
	}

	//find pad length
	padlength = (int)msgPtr[mlength - 1];
	padlength = (padlength < 0 || padlength > 8) ? 0 : padlength;

	//remove padding
	std::string retval(msgPtr);
	retval.erase(mlength - padlength, padlength); //remove padding
	delete[] msgPtr;

	return retval;
}
/*
File is read 1024 bytes at a time into a buffer
Each 8 bytes is then encrypted at a time until the
buffer is empty. if the remaining size is < buffer size,
read it in, pad to be a multiple of 8bytes, then encrypt.
*/
void encrypt_file(std::string filename, std::string key)
{
	char buffer[1024];
	int bytesRead;
	std::string outfilename = filename;
	outfilename.append(".enc");
	std::ifstream inFile(filename, std::ios::in | std::ios::binary); //input file
	std::ofstream outFile(outfilename, std::ios::out | std::ios::binary); //output file

	keyschedule keys(key); //generate keyschedule
						   //read file in chunks
	while (inFile)
	{
		inFile.read(buffer, 1024);
		if (inFile)
		{
			bytesRead = 1024;
			int size = bytesRead / 8;
			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], keys); //encrypt
			}
			outFile.write(buffer, bytesRead);
		}
		else
		{
			//last block read, pad it
			bytesRead = (int)inFile.gcount();
			int padlength = 8 - bytesRead % 8;
			int size = (bytesRead + padlength) / 8;

			for (int i = bytesRead; i < bytesRead + padlength; ++i)
			{
				buffer[i] = (char)padlength;
			}

			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], keys);
			}
			outFile.write(buffer, bytesRead + padlength);
		}
	}

	inFile.close();
	outFile.close();
	remove(filename.c_str());
	rename(outfilename.c_str(), filename.c_str());
}
/*
File is read 1024 bytes at a time into a buffer
Each 8 bytes is then decrypted at a time until the
buffer is empty. The number of chunks is calculated.
chunk = buffer, so how many times must a buffer be filled.
if the  last chunk is being read, find the padding size and remove the padding.
*/
void decrypt_file(std::string filename, std::string key)
{
	char buffer[1024];
	int bytesRead;
	long fileSize;
	long last_chunk;
	long current_chunk = 0;
	int padlength = 0;

	std::string outfilename = filename;
	outfilename.append(".dec");
	//find file size and number of chucnks it is split into
	struct stat stat_buf;
	stat(filename.c_str(), &stat_buf);
	fileSize = stat_buf.st_size;
	last_chunk = fileSize / 1024 + ((fileSize % 1024 == 0) ? 0 : 1);

	std::ifstream inFile(filename, std::ios::in | std::ios::binary); //infile
	std::ofstream outFile(outfilename, std::ios::out | std::ios::binary); //outfile

	keyschedule keys(key); //generate keyschedule
	keys.reverse(); //reverse order for decryption

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
				encrypt_block((unsigned char*)&buffer[8 * i], keys); //decrypt
			}

			if (current_chunk == last_chunk)
			{
				padlength = buffer[1023];
			}

			outFile.write(buffer, bytesRead - padlength);
		}
		else
		{
			//last block read, pad it
			bytesRead = (int)inFile.gcount();
			int size = bytesRead / 8;

			for (int i = 0; i < size; ++i)
			{
				encrypt_block((unsigned char*)&buffer[8 * i], keys); //decrypt
			}

			if (current_chunk == last_chunk)
			{
				padlength = buffer[bytesRead - 1];
			}

			outFile.write(buffer, bytesRead - padlength);
		}
	}

	inFile.close();
	outFile.close();
	remove(filename.c_str());
	rename(outfilename.c_str(), filename.c_str());
}

//encrypt 64 bits
std::bitset<64> encrypt_bits(std::bitset<64> message, std::bitset<64> key)
{
	keyschedule keys(key); //generate keyschedule
	return do_DES(message, keys);
}

//encrypt 64 bits
std::bitset<64> decrypt_bits(std::bitset<64> message, std::bitset<64> key)
{
	keyschedule keys(key); //generate keyschedule
	keys.reverse(); //reverse order for decryption
	return do_DES(message, keys);
}
