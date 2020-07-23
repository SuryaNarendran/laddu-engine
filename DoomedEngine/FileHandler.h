#pragma once
#include "DOOM.h"

class FileHandler {


public:

	static char* readFileToString(const char* filename);

private:

	static unsigned long getFileLength(std::ifstream& file);


};
