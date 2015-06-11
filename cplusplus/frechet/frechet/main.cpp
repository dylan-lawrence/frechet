// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <boost/program_options.hpp>
#include "CGAL\Simple_cartesian.h"
//#include "CGAL\Gmpq.h" TODO: Fix imports of gmp

#include "FileParser.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Define argument parsing
	try {
		namespace po = boost::program_options; //simple binding

		po::options_description desc("Options");
		//TODO: determine why this isn't working...

		/*desc.add_options()
			("help,h", "Print help options.")
			("file1,f1", po::value<std::string>(), "A file containing a curve.")
			("file2,f2", po::value<std::string>(), "A different file containing a curve.")
			//("outfile", "The file to write output data.") TODO: Determine what goes here
			("filetype,ft", po::value<std::string>(), "The format of the curve files.")
			("epsilon,e", po::value<double>(), "The epsilon to use for calculation.")
			("verbose,v", po::value<int>(), "Activate verbose logging.");*/

		//TODO: implement proper parsing
	}
	catch (std::exception &e) {
		std::cout << "An error occured in argument parsing" << std::endl;
	}

	//TODO: Create file reading

	std::cout << "Press enter to exit..." << std::endl;
	std::cin.get();
}

