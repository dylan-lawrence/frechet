#pragma once

//Tokens for reachability

#include <vector>

#include "CGAL\Simple_cartesian.h"
#include "gmp.h"
#include "CGAL\Gmpq.h"

typedef CGAL::Simple_cartesian<CGAL::Gmpq> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

typedef std::vector<Point_2> Curve; //Simple method of storing multiple line segments

class Frechet
{

public:
	Frechet(int size1, int size2, Curve c1, Curve c2);
	~Frechet();
	static Point_2 GeneratePoint(std::vector<double> xy);
	static Curve GenerateCurve(std::vector<Point_2> points);

	void CalculateFreespace(Segment_2 &segment, Point_2 &point, double &start, double &end);
	void SetFreespace();

	static const double WHITE;
	static const double BLACK;
	static const double MININF;

private:
	//Freespace diagram representation
	double **vFSs;
	double **vFSe;
	double **hFSs;
	double **hFSe;

	//Reachability representation
	double **vRTs;
	double **vRTe;
	double **hRTs;
	double **hRTe;

	int n1, n2;
	
	Curve curve1, curve2;
};

