// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <boost/program_options.hpp>
#include "FileParser.h"
#include "Frechet.h"

int _tmain(int argc, _TCHAR* argv[])
{

	bool PARSE_ERR = false; //Check if required args were used
	int VERBOSITY = 0; //How verbose we want our run to be, will be passed to frechet instant

	std::string file1;
	std::string file2;
	std::string filetype = "simple";
	double epsilon;

	//Define argument parsing
	try 
	{
		namespace po = boost::program_options; //simple binding

		po::options_description desc("Options");
		//TODO: determine why this isn't working...

		desc.add_options() //required was not used here due to issues with how it parses
			("help,h", "Print help options.")
			("file1", po::value<std::string>(), "A file containing a curve.")
			("file2", po::value<std::string>(), "A different file containing a curve.")
			//("outfile", "The file to write output data.") TODO: Determine what goes here
			//("filetype,t", po::value<std::string>(), "The format of the curve files.")
			("epsilon,e", po::value<double>(), "The epsilon to use for calculation.")
			("verbose,v", po::value<int>(), "Activate verbose logging.");

		po::variables_map vm;
		try
		{
			po::store(po::parse_command_line(argc, argv, desc), vm);

			//help selected
			if (vm.count("help"))
			{
				std::cout << "Strong Frechet Implementation" << std::endl << desc << std::endl;
			}
			else
			{

				if (vm.count("verbose"))
				{
					VERBOSITY = vm["verbose"].as<int>();
					std::cout << "Verbosity set to " << VERBOSITY << std::endl;
				}

				if (vm.count("file1"))
				{
					file1 = vm["file1"].as<std::string>();
					std::cout << "First file path set to " << file1 << std::endl;
				}
				else
				{
					PARSE_ERR = true;
					std::cout << "Error: Missing argument 'file1 arg'" << std::endl;
				}

				if (vm.count("file2"))
				{
					file2 = vm["file2"].as<std::string>();
					std::cout << "Second file path set to " << file2 << std::endl;
				}
				else
				{
					PARSE_ERR = true;
					std::cout << "Error: Missing argument 'file2 arg'" << std::endl;
				}

				if (vm.count("epsilon"))
				{
					epsilon = vm["epsilon"].as<double>();
					std::cout << "Epsilon value set to " << epsilon << std::endl;
				}
				else
				{
					PARSE_ERR = true;
					std::cout << "Error: Missing argument 'epsilon arg'" << std::endl;
				}

				/* TODO: Implement typing eventually
				if (vm.count("filetype"))
				{
					
				} */
			}

		}
		catch (std::exception &e)
		{
			std::cout << "Error reading command line arguments." << std::endl;
			return -1;
		}		
	}
	catch (std::exception &e)
	{
		std::cout << "An error occured in argument parsing" << std::endl;
		return -1;
	}

	std::cout << std::endl << std::endl << "================" << std::endl << "Beginning Program" << std::endl << "================" << std::endl;

	//TODO: Create file reading
	FileParser fp = FileParser();
	std::vector<std::vector<double>> file1data = fp.getParsedContent(file1, filetype);
	std::vector<std::vector<double>> file2data = fp.getParsedContent(file2, filetype);
	
	//Size of the two curves
	int n1 = file1data.size();
	int n2 = file2data.size();

	std::cout << std::endl << "Press enter to exit..." << std::endl;
	std::cin.get();

	return 0;
}

