#include "FileHandler.h"

unsigned long FileHandler::getFileLength(std::ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = (unsigned long)file.tellg();
	file.seekg(0, std::ios::end);
	unsigned long len = (unsigned long)file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

char* FileHandler::readFileToString(const char* filename)
{
	std::ifstream myfile;
	myfile.open(filename, std::ios::in);
	if (!myfile) return NULL;

	unsigned long len = getFileLength(myfile);

	if (len == 0) return NULL;   // "Empty File" 

	char* ShaderSource = new char[len + 1];
	if (ShaderSource == 0) return NULL;   // can't reserve memory

	ShaderSource[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
							// it is important to 0-terminate the real length later, len is just max possible value...
	unsigned int i = 0;
	while (myfile.good())
	{
		ShaderSource[i] = myfile.get();       // get character from file.
		if (!myfile.eof())
			i++;
	}

	ShaderSource[i] = 0;  // 0 terminate it.

	myfile.close();

	return ShaderSource;
}
