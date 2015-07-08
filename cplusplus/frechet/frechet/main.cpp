// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/iterator.h>
#include <gmp.h>
#include <CGAL/Gmpq.h>

#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{

	typedef CGAL::Exact_circular_kernel_2 Kernel;
	typedef CGAL::Point_2<Kernel> Point_2;
	typedef CGAL::Circular_arc_point_2<Kernel> Circular_arc_point_2;
	typedef CGAL::Line_2<Kernel> Line_2;
	typedef CGAL::Line_arc_2<Kernel> LineArc_2;
	typedef CGAL::Circle_2<Kernel> Circle_2;
	typedef std::pair<Circular_arc_point_2, unsigned> IntersectOut;

	Line_2 l(Point_2(2, 4), Point_2(6, 8));
	Circle_2 c(Point_2(3, 7),3);

	std::vector<IntersectOut> output;

	typedef CGAL::Dispatch_output_iterator < CGAL::cpp11::tuple<IntersectOut>, CGAL::cpp0x::tuple<std::back_insert_iterator<std::vector<IntersectOut>>>> Dispatcher;

	Dispatcher disp = CGAL::dispatch_output<IntersectOut>(std::back_inserter(output));
	CGAL::intersection(l, c, disp);

	if (output.size() > 0)
	{
		std::cout << CGAL::to_double(output[0].first.x()) << ", " << CGAL::to_double(output[0].first.y()) << std::endl;
		std::cout << output[0].second << std::endl;
		if (output.size() > 1)
		{
			std::cout << CGAL::to_double(output[1].first.x()) << ", " << CGAL::to_double(output[1].first.y()) << std::endl;
		}
	}

	std::cout << "Press enter to exit..." << std::endl;
	std::cin.get();

	return 0;
}

