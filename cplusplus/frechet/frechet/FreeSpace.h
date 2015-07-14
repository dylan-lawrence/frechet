#pragma once

#include "FsGridSquare.h"
#include "frechet_types.h"

class FreeSpace
{

public:
	FreeSpace(int n1, int n2, Point_2* c1, Point_2* c2, CGAL::Gmpq eps);
	~FreeSpace();

	FsGridSquare GetSquare(int n1i, int n2i);
	void CalculateSquare(int n1i, int n2i);
	Edge* CalculateEdge(Point_2 p, Point_2 curvep1, Point_2 curvep2);

	static double PercentAlongCurve(Circular_arc_point_2 ap, Point_2 curvep1, Point_2 curvep2);

private:
	FsGridSquare** grid;
	int n1, n2;
	CGAL::Gmpq epsilon;

	Point_2* curve1;
	Point_2* curve2;
};

