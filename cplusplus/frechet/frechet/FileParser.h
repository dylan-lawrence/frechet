#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

//TODO: Implement parsing methods

class FileParser
{

private:
	std::string filecontent;

public:
	FileParser(std::string filepath);
	~FileParser();

	std::string const getFileContent();
};

