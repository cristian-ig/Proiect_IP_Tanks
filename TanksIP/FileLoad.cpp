#include "FileLoad.h"

#include <filesystem>
#include <fstream>
namespace tanks {

FileLoad::FileLoad()
{
}

FileLoad::~FileLoad()
{
}

bool FileLoad::readFileToBuffer(std::string filePath, std::vector<unsigned char>& vect)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}
	//seek to the end
	file.seekg(0, std::ios::end);
	//Get the file size
	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);
	//Reduce the file size by any header bytes that might be present
	fileSize -= (unsigned int)file.tellg();
	vect.resize(fileSize);
	file.read((char *)&(vect[0]), fileSize); //start adding lines to the vector
	file.close(); //safety first

	return true;
}

bool FileLoad::readFileToBuffer(std::string filePath, std::string& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= (unsigned int)file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;
}
}