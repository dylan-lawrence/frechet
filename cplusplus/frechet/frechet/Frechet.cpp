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

Frechet::Frechet(int size1, int size2, Curve c1, Curve c2)
{
	n1, n2 = size1, size2; //size of curve1 and curve2
	curve1, curve2 = c1, c2;

	//Allocate memory for all of our arrays
	hFSs = new double*[n2];
	hFSe = new double*[n2];
	hRTs = new double*[n2];
	hRTe = new double*[n2];

	for (int i = 0; i < n2; i++)
	{
		hFSs[i] = new double[n1 - 1];
		hFSe[i] = new double[n1 - 1];
		hRTs[i] = new double[n1 - 1];
		hRTe[i] = new double[n1 - 1];
	}

	vFSs = new double*[n2 - 1];
	vFSe = new double*[n2 - 1];
	vRTs = new double*[n2 - 1];
	vRTe = new double*[n2 - 1];

	for (int i = 0; i < n2 - 1; i++)
	{
		vFSs[i] = new double[n1];
		vFSe[i] = new double[n1];
		vRTs[i] = new double[n1];
		vRTe[i] = new double[n1];
	}
}

void Frechet::CalculateFreespace(Segment_2 &segment, Point_2 &point, double &start, double & end)
{
	return;
}

//Drives the main building of the freespace
void Frechet::SetFreespace()
{
	//Fill in horizontal freespace
	for (int i = 0; i < n1 - 1; i++)
	{
		for (int j = 0; j < n2 - 1; j++)
		{
			Frechet::CalculateFreespace(Segment_2(curve1[i], curve1[i + 1]), curve2[j], hFSs[j][i], hFSe[j][i]);
		}
	}

	//Fill in vertical freespace
}

Frechet::~Frechet()
{
	//Deallocate all arrays
	for (int i = 0; i < n2; i++)
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
