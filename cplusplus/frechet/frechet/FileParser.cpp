#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser()
{
	
}

double** FileParser::getParsedContent(std::string filepath, std::string filetype)
{
	std::string filecontent;

	try
	{
		std::ifstream in = std::ifstream(filepath);
		filecontent = std::string(static_cast<std::stringstream const&> (std::stringstream() << in.rdbuf()).str());
	}
	catch (std::exception &e)
	{
		std::cout << "Error opening file " << filepath << std::endl;
		return nullptr;
	}

	std::cout << filecontent << std::endl;
}

FileParser::~FileParser()
{
}
