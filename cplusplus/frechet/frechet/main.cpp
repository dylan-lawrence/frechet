// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <CGAL/Exact_circular_kernel_2.h>
#include <gmp.h>
#include <CGAL/Gmpq.h>

#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{

	typedef CGAL::Exact_circular_kernel_2 Kernel;
	typedef CGAL::Point_2<Kernel> Point_2;
	typedef CGAL::Line_2<Kernel> Line_2;
	typedef CGAL::Circle_2<Kernel> Circle_2;

	//rabble rabble

	std::cout << "Press enter to exit..." << std::endl;
	std::cin.get();

	return 0;
}

