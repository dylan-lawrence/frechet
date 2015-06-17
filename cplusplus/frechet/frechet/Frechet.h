#pragma once

#include <vector>

#include "CGAL\Simple_cartesian.h"
#include "CGAL\Gmpq.h"

typedef CGAL::Simple_cartesian<CGAL::Gmpq> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

typedef std::vector<Point_2> Curve; //Simple method of storing multiple line segments

class Frechet
{

public:
	Frechet();
	~Frechet();
};

