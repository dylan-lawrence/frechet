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

	std::vector<std::vector<double>> getParsedContent(std::string filepath, std::string filetype);
};

