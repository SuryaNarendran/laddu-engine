#pragma once
#include "DOOM.h"

class FileHandler {


public:

	static char* readFileToString(const char* filename);
	static char getNextRelevantChar(std::fstream &file);

	static char readHRInteger(std::fstream &file, int &result);

	static char readHRInteger(std::fstream &file, float &result);

	static char readHRFloat(std::fstream &file, float &result);

	static char readHRVector3(std::fstream &file, glm::vec3 &vector);

	static char readHRVector4(std::fstream &file, glm::vec4 &vector);

	static char readHRString(std::fstream &file, char* str);

private:

	static unsigned long getFileLength(std::ifstream& file);


};
