#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//TODO: Implement parsing methods

class FileParser
{

private:
	std::string filecontent;

public:
	FileParser();
	~FileParser();

	double** getParsedContent(std::string filepath, std::string filetype);
};

