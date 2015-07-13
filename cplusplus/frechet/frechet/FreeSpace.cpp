#include "stdafx.h"
#include "FreeSpace.h"

#include <iostream>
#include <string>

double FreeSpace::PercentAlongCurve(Circular_arc_point_2 ap, Point_2 curvep1, Point_2 curvep2)
{
	//TODO: Calculate percentage along the line the point is.

	//If the percentage was known: curvep1 + (percent)(curvep2 - curvep1) = ap
	//(ap - curvep1)/(curvep2 - curvep1) = percent
}

FreeSpace::FreeSpace(int n1i, int n2i, Point_2* c1, Point_2* c2, CGAL::Gmpq eps)
{
	n1 = n1i;
	n2 = n2i;

	curve1 = c1;
	curve2 = c2;

	epsilon = eps;

	grid = new FsGridSquare*[n1i - 1];
	for (int i = 0; i < n1i - 1; i++)
		grid[i] = new FsGridSquare[n2i - 1];
}

FsGridSquare FreeSpace::GetSquare(int n1i, int n2i)
{
	return grid[n1i][n2i];
}

void FreeSpace::CalculateSquare(int n1i, int n2i)
{
	if (n1i == 0 && n2i == 0) //first square, must calculate all four edges
	{

	}
}

Edge FreeSpace::CalculateEdge(Point_2 p, Point_2 curvep1, Point_2 curvep2) //curvep1, curvep2 represent the start/end of a segment.
{
	Edge edge = Edge();

	Line_2 l(curvep1, curvep2);
	Circle_2 c(p, epsilon*epsilon);

	std::vector<IntersectOut> output;
	typedef CGAL::Dispatch_output_iterator < CGAL::cpp11::tuple<IntersectOut>, CGAL::cpp0x::tuple<std::back_insert_iterator<std::vector<IntersectOut>>>> Dispatcher;

	Dispatcher disp = CGAL::dispatch_output<IntersectOut>(std::back_inserter(output));
	CGAL::intersection(l, c, disp);

	if (output.size() > 1) //two intersection points
	{

	}
	else if (output.size() > 0) //one intersection point
	{
		Circular_arc_point_2 inp = output[0].first;
	}
	else // no intersection
	{
		edge.SetStart(-1);
		edge.SetEnd(-1);
	}

	return edge;
}

FreeSpace::~FreeSpace()
{
}
