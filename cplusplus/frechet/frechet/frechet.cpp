// frechet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <boost/program_options.hpp>
#include "CGAL\Simple_cartesian.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

int _tmain(int argc, _TCHAR* argv[])
{
	//Define argument parsing
	try {
		namespace po = boost::program_options; //simple binding

		po::options_description desc("Options");
		desc.add_options()
			("help", "Print help options.")
			("file1", "A file containing a curve.")
			("file2", "A different file containing a curve.")
			("outfile", "The file to write output data.")
			("filetype", "The format of the curve files.")
			("epsilon", "The epsilon to use for calculation.")
			("epsilonrange", "A range of epsilon values to test.")
			("epsilonstep", "The step between epsilons in epsilonrange.")
			("verbose", "Activate verbose logging.");

	}
	catch (std::exception &e) {
		std::cout << "An error occured in argument parsing" << std::endl;
	}

	std::cout << "Press enter to exit..." << std::endl;
	std::cin.get();
}

