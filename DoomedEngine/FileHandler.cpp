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


char FileHandler::getNextRelevantChar(std::fstream &file) {

	while (true) {
		//strip front whitespace
		char charBuffer = file.get();
		while (charBuffer == '\n' || charBuffer == ' ' || charBuffer == '\r' || charBuffer == '\t')
			charBuffer = file.get();
		//if line is preceded by a comment marker, ignore the line and take the character after the newline
		if (charBuffer == '#') {
			while (charBuffer != '\n' && charBuffer != EOF) {
				charBuffer = file.get();
			}
		}
		else if (charBuffer == '$') {
			while (charBuffer != '$' && charBuffer != EOF) {
				charBuffer = file.get();
			}
		}
		else return charBuffer; //if character is anything else, return the value
	}

}

char FileHandler::readHRInteger(std::fstream &file, int &result) {
	result = 0;

	char charBuffer = getNextRelevantChar(file);

	//read successive integers and increment value of result accordingly	
	while (charBuffer != '\n' && charBuffer != ' ' && charBuffer != EOF) {

		result *= 10;
		result += charBuffer - CHAR_TO_INT;
		charBuffer = file.get();
	}
	return charBuffer;
}

char FileHandler::readHRInteger(std::fstream &file, float &result) {

	int intVal;
	char retval = readHRInteger(file, intVal);
	result = intVal;
	return retval;
}

char FileHandler::readHRFloat(std::fstream &file, float &result) {
	result = 0;

	char charBuffer = getNextRelevantChar(file);

	int decimalPlaces = 0;
	bool isAfterDecPoint = false;
	bool negative = false;

	//read successive integers and increment value of result accordingly	
	while (charBuffer != '\n' && charBuffer != ' ' && charBuffer != EOF && charBuffer != ',') {

		if (charBuffer == '.') {
			isAfterDecPoint = true;
			charBuffer = file.get();
			continue;
		}

		if (charBuffer == '-') {
			negative = true;
			charBuffer = file.get();
			continue;
		}

		if (charBuffer < '0' || charBuffer > '9') {
			break;
		}

		if (isAfterDecPoint) {
			decimalPlaces++;
			result += (charBuffer - CHAR_TO_INT) / pow(10, decimalPlaces);
		}
		else {
			result *= 10;
			result += charBuffer - CHAR_TO_INT;
		}

		charBuffer = file.get();
	}

	if (negative) result *= -1;

	return charBuffer;
}

char FileHandler::readHRVector3(std::fstream &file, glm::vec3 &vector) {
	getNextRelevantChar(file); //'('
	readHRFloat(file, vector.x);
	readHRFloat(file, vector.y);
	return readHRFloat(file, vector.z); //returns the last encountered character
}

char FileHandler::readHRString(std::fstream &file, char* str) {
	char charBuffer = getNextRelevantChar(file);
	if (charBuffer == '\"') {
		charBuffer = file.get();
		int i;
		for (i = 0; charBuffer != '\n' && charBuffer != EOF && charBuffer != '\"'; i++) {
			str[i] = charBuffer;
			charBuffer = file.get();
		}

		str[i] = '\0';
	}
	else str[0] = '\0';

	return charBuffer;
}
