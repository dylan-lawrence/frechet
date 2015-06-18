#include "stdafx.h"
#include "Frechet.h"

//static nums
const double Frechet::WHITE = 1;
const double Frechet::BLACK = -1;
const double Frechet::MININF = -10; //Note: this is a magic number for usage in reachability

//Quick method to conver an x,y pair in a vector to a Point_2
Point_2 Frechet::GeneratePoint(std::vector<double> xy)
{
	return Point_2(CGAL::Gmpq(xy[0]), CGAL::Gmpq(xy[1]));
}

//Returns a curve which is just a renamed vector<Point_2>
Curve Frechet::GenerateCurve(std::vector<Point_2> points)
{
	Curve c = Curve();
	for (Point_2 &p : points)
		c.push_back(p);
	return c;
}

Frechet::Frechet(int size1, int size2)
{
	Frechet::n1, Frechet::n2 = size1, size2; //size of curve1 and curve2

	//Allocate memory for all of our arrays
	hFSs = new double*[Frechet::n2];
	hFSe = new double*[Frechet::n2];
	hRTs = new double*[Frechet::n2];
	hRTe = new double*[Frechet::n2];

	for (int i = 0; i < Frechet::n2; i++)
	{
		hFSs[i] = new double[Frechet::n1 - 1];
		hFSe[i] = new double[Frechet::n1 - 1];
		hRTs[i] = new double[Frechet::n1 - 1];
		hRTe[i] = new double[Frechet::n1 - 1];
	}
}

Frechet::~Frechet()
{
	//Deallocate all arrays
	for (int i = 0; i < Frechet::n2; i++)
	{
		delete hFSs[i];
		delete hFSe[i];
		delete hRTs[i];
		delete hRTs[i];
	}

	delete hFSs;
	delete hFSe;
	delete hRTs;
	delete hRTs;
}
