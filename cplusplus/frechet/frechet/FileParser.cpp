#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser(std::string filepath)
{
	try {
		std::ifstream in = std::ifstream(filepath);
		FileParser::filecontent = std::string(static_cast<std::stringstream const&> (std::stringstream() << in.rdbuf()).str());
	}
	catch (std::exception &e) {
		std::cout << "Error opening file " << filepath << std::endl;
	}
}

std::string const FileParser::getFileContent() {
	return FileParser::filecontent;
}

FileParser::~FileParser()
{
}
