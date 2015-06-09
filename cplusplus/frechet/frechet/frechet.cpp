// frechet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "CGAL\Simple_cartesian.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

int _tmain(int argc, _TCHAR* argv[])
{
	Point_2 p(2, 2);
	std::cout << "p=" << p << std::endl;
	return 0;
}

