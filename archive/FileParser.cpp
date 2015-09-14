#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser()
{
	
}

std::vector<std::vector<double>> FileParser::getParsedContent(std::string filepath, std::string filetype)
{
	std::ifstream infile(filepath);
	std::string content = "d";
	std::vector<std::string> coords = std::vector<std::string>();
	
	//Get file content
	for (int i = 0; !content.empty(); i++)
	{
		std::getline(infile, content);
		coords.push_back(content);
	}

	//Place pairs in Vector such that n,0 is the x and n,1 is the y value
	//NOTE: This currently assumes filetype is always "simple"
	int count = coords.size();
	std::vector<std::vector<double>> pairs = std::vector<std::vector<double>>();
	for (int i = 0; i < count - 1; i++)
	{
		int ind = coords[i].find(' ');
		double x = stod(coords[i].substr(0, ind));
		double y = stod(coords[i].substr(ind, coords[i].size()));

		pairs.push_back(std::vector<double>());
		pairs[i].push_back(x);
		pairs[i].push_back(y);
	}
	
	return pairs;
}

FileParser::~FileParser()
{

}
