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
	std::cout << "Calculating cell " << n1i << "," << n2i << std::endl;
	if (n1i == 0 && n2i == 0) //first square, must calculate all four edges
	{
		grid[n1i][n2i].left = CalculateEdge(curve2[n2i], curve1[n1i], curve1[n1i + 1]);
		grid[n1i][n2i].top = CalculateEdge(curve1[n1i + 1], curve2[n2i], curve2[n2i + 1]);
		grid[n1i][n2i].right = CalculateEdge(curve2[n2i + 1], curve1[n1i], curve1[n1i + 1]);
		grid[n1i][n2i].bottom = CalculateEdge(curve1[n1i], curve2[n2i], curve2[n2i + 1]);
	}
	else if (n1i == 0)
	{
		grid[n1i][n2i].left = grid[n1i][n2i - 1].right;

		grid[n1i][n2i].top = CalculateEdge(curve1[n1i + 1], curve2[n2i], curve2[n2i + 1]);
		grid[n1i][n2i].right = CalculateEdge(curve2[n2i + 1], curve1[n1i], curve1[n1i + 1]);
		grid[n1i][n2i].bottom = CalculateEdge(curve1[n1i], curve2[n2i], curve2[n2i + 1]);
	}
	else if (n2i == 0)
	{
		grid[n1i][n2i].bottom = grid[n1i - 1][n2i].top;

		grid[n1i][n2i].left = CalculateEdge(curve2[n2i], curve1[n1i], curve1[n1i + 1]);
		grid[n1i][n2i].top = CalculateEdge(curve1[n1i + 1], curve2[n2i], curve2[n2i + 1]);
		grid[n1i][n2i].right = CalculateEdge(curve2[n2i + 1], curve1[n1i], curve1[n1i + 1]);
	}
	else
	{
		grid[n1i][n2i].left = grid[n1i][n2i - 1].right;
		grid[n1i][n2i].bottom = grid[n1i - 1][n2i].top;
		grid[n1i][n2i].top = CalculateEdge(curve1[n1i + 1], curve2[n2i], curve2[n2i + 1]);
		grid[n1i][n2i].right = CalculateEdge(curve2[n2i + 1], curve1[n1i], curve1[n1i + 1]);
	}
}

Edge* FreeSpace::CalculateEdge(Point_2 p, Point_2 curvep1, Point_2 curvep2) //curvep1, curvep2 represent the start/end of a segment.
{
	std::cout << "calculating edge for line from " << curvep1 << " to " << curvep2 << " and a circle at " << p << " with radius " << epsilon << std::endl;
	Edge* edge = new Edge();

	CGAL::Gmpq xdiff = curvep2.x() - curvep1.x();
	CGAL::Gmpq ydiff = curvep2.y() - curvep1.y();

	CGAL::Gmpq b_t = 2 * ((curvep1.x() - p.x()) * xdiff + (curvep1.y() - p.y()) * ydiff);
	CGAL::Gmpq c_t = (curvep1.x() - p.x()) * (curvep1.x() - p.x()) + (curvep1.y() - p.y()) * (curvep1.y() - p.y()) - epsilon * epsilon;
	CGAL::Gmpq a_t = xdiff*xdiff + ydiff*ydiff;

	//check a_t value if 0

	CGAL::Gmpq determinant = b_t * b_t - 4 * a_t * c_t;

	if (determinant >= 0)
	{
		edge->SetEnd((CGAL::to_double(-b_t) + std::sqrt(CGAL::to_double(determinant)))/CGAL::to_double(2 * a_t));
		edge->SetStart((CGAL::to_double(-b_t) - std::sqrt(CGAL::to_double(determinant))) / CGAL::to_double(2 * a_t));
	}
	else
	{
		std::cout << "determinant is 0" << std::endl;
	}

	return edge;
}

FreeSpace::~FreeSpace()
{
}