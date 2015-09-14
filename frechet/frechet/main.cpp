// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/iterator.h>
#include <gmp.h>
#include <CGAL/Gmpq.h>

#include <vector>

#include "FreeSpace.h"
#include "PathTree.h"

#include "frechet_types.h"

int _tmain(int argc, _TCHAR* argv[])
{
	/* Circle stuff for reference
	Line_2 l(Point_2(2, 4), Point_2(6, 8));
	Circle_2 c(Point_2(3, 7),9); //Note this constructor takes squared radius, so this is a circle at (3,7) with radius 3

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
	*/

	CGAL::Gmpq epsilon;
	std::cout << "Enter an epsilon value: ";
	std::cin >> epsilon;

	Point_2 curve1[6] = {
		Point_2(1,7),
		Point_2(3,2),
		Point_2(4,5),
		Point_2(6,3),
		Point_2(8,6),
		Point_2(9,1)
	};
	Point_2 curve2[6] = {
		Point_2(2, 3),
		Point_2(4, 6),
		Point_2(5, 2),
		Point_2(6, 5),
		Point_2(7, 2),
		Point_2(10, 3)
	};

	FreeSpace fs = FreeSpace(6, 6, curve1, curve2, epsilon);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
		{
			fs.CalculateSquare(i, j);
		}
	}

	PathTree tree = PathTree(&fs);

	std::cout << "Path is as follows..." << std::endl;
	std::vector<PathTree::PathNode> path = tree.FindPath();
	std::reverse(path.begin(), path.end());
	for (PathTree::PathNode n : path)
	{
		std::cout << "Into " << n.n1 << "," << n.n2 << " through value " << n.entryval << std::endl;
	}


	std::cout << "Press enter to exit..." << std::endl;

	std::cin.ignore();
	std::cin.get();

	return 0;
}

