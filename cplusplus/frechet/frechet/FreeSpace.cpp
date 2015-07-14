#include "stdafx.h"
#include "FreeSpace.h"

#include <iostream>
#include <string>

double FreeSpace::PercentAlongCurve(Circular_arc_point_2 ap, Point_2 curvep1, Point_2 curvep2) //Calculate percentage along the line the point is.
{	

	Circular_arc_point_2 cp1 = Circular_arc_point_2(curvep1);
	Circular_arc_point_2 cp2 = Circular_arc_point_2(curvep2);

	return std::sqrt(CGAL::to_double((cp1.x() - cp2.x())*(cp1.x() - cp2.x()) + (cp1.y() - cp2.y())*(cp1.y() - cp2.y()) / (cp1.x() - ap.x())*(cp1.x() - ap.x()) + (cp1.y() - ap.y())*(cp1.y() - ap.y())));
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
		grid[n1i][n2i].left = CalculateEdge(curve2[n2i], curve1[n1i], curve1[n1i + 1]);
		grid[n1i][n2i].top = CalculateEdge(curve1[n1i+1], curve2[n2i], curve2[n2i+1]);
		grid[n1i][n2i].right = CalculateEdge(curve2[n2i+1], curve1[n1i], curve1[n1i+1]);
		grid[n1i][n2i].bottom = CalculateEdge(curve1[n1i], curve2[n2i], curve2[n2i+1]);
	}
}

Edge* FreeSpace::CalculateEdge(Point_2 p, Point_2 curvep1, Point_2 curvep2) //curvep1, curvep2 represent the start/end of a segment.
{
	Edge* edge = new Edge();

	Line_2 l(curvep1, curvep2);
	Circle_2 c(p, epsilon*epsilon);

	std::vector<IntersectOut> output;
	typedef CGAL::Dispatch_output_iterator < CGAL::cpp11::tuple<IntersectOut>, CGAL::cpp0x::tuple<std::back_insert_iterator<std::vector<IntersectOut>>>> Dispatcher;

	std::cout << "Intersecting a circle at: " << p << " with radius " << epsilon << " with the segment from: " << curvep1 << " to " << curvep2 << std::endl;

	Dispatcher disp = CGAL::dispatch_output<IntersectOut>(std::back_inserter(output));
	CGAL::intersection(l, c, disp);

	if (output.size() > 1) //two intersection points
	{
		std::cout << "Found two intersections at: " << CGAL::to_double(output[0].first.x()) << CGAL::to_double(output[0].first.y()) << " and " << CGAL::to_double(output[1].first.x()) << CGAL::to_double(output[1].first.y()) << std::endl;

		//Note: need to special case and check if the intersections are beyond the segment
		double percent1 = PercentAlongCurve(output[0].first, curvep1, curvep2);
		double percent2 = PercentAlongCurve(output[1].first, curvep1, curvep2);

		if (percent1 > percent2)
		{
			edge->SetStart(percent2);
			edge->SetEnd(percent1);
		}
		else
		{
			edge->SetStart(percent1);
			edge->SetEnd(percent2);
		}
	}
	else if (output.size() > 0) //one intersection point
	{
		double percent = PercentAlongCurve(output[0].first, curvep1, curvep2);

		edge->SetStart(percent);
		edge->SetEnd(percent);
	}
	else // no intersection
	{
		edge->SetStart(-1);
		edge->SetEnd(-1);
	}

	return edge;
}

FreeSpace::~FreeSpace()
{
}
