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

Frechet::Frechet(double &epsilon, int &size1, int &size2, Curve &c1, Curve &c2)
{
	n1 = size1;
	n2 = size2;
	curve1 = c1;
	curve2 = c2;
	EPSILON = CGAL::Gmpq(epsilon);

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
	/* TODO: Implement CGAL style segment/circle interesection, currently using the pure math method */

	/* Pure Math Method */

	CGAL::Gmpq xdiff, ydiff, root, b, divisor, t1, t2, q;

	xdiff = segment.target().x() - segment.source().x();
	ydiff = segment.target().y() - segment.source().y();

	divisor = xdiff*xdiff + ydiff*ydiff;

	if (divisor == 0)
	{
		std::cout << "divisor is zero" << std::endl;
	}

	b = (point.x() - segment.source().x()) * xdiff + (point.y() - segment.source().y()) * ydiff;
	q = (segment.source().x()*segment.source().x() + segment.source().y()*segment.source().y() + point.x()*point.x() + point.y() * point.y() - 2 * segment.source().x() * point.x() - 2 * segment.source().y() * point.y() - EPSILON*EPSILON) * divisor;
	root = b*b - q;

	if (root < 0)
	{
		start = end = 1;
		return;
	}

	root = (CGAL::Gmpq) sqrt(root.to_double()); //Rationals cannot be return from a square root, this might be problematic

	t2 = (b + root) / divisor;
	t1 = (b - root) / divisor;

	if (t1 < 0) t1 = 0;
	if (t2 < 0) t2 = 0;
	if (t1 > 1) t1 = 1;
	if (t2 > 1) t2 = 1;

	start = t1.to_double();
	end = t2.to_double();

	if (start == end)
	{
		start = end = -1;
	}

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
	for (int i = 0; i < n1 - 1; i++)
	{
		for (int j = 0; j < n2 - 1; j++)
		{
			Frechet::CalculateFreespace(Segment_2(curve2[j], curve2[j + 1]), curve1[i], vFSs[j][i], vFSe[j][i]);
		}
	}

}

void Frechet::SetReachability()
{
	//edge cases
	for (int i = 0; i < n1; i++)
	{
		vRTs[0][i] = vFSs[0][i];
		vRTe[0][i] = vFSe[0][i];
		for (int j = 1; j < n2 - 1; j++)
		{
			vRTs[j][i] = MININF;
			vRTe[j][i] = MININF;
		}
	}

	for (int j = 0; j < n2; j++)
	{
		hRTs[j][0] = hFSs[j][0];
		hRTe[j][0] = hFSe[j][0];
		for (int i = 0; i < n1 - 1; i++)
		{
			hRTs[j][i] = MININF;
			hRTe[j][i] = MININF;
		}
	}

	//normal case
	for (int i = 0; i < n1 - 1; i++)
	{
		for (int j = 0; j < n2 - 1; j++)
		{
			if (vRTs[j][i] >= 0 && vRTe[j][i] > vRTs[j][i])
			{
				hRTs[j + 1][i] = hFSs[j + 1][i];
				hRTe[j + 1][i] = hFSe[j + 1][i];
			}
			else
			{
				if (hRTs[j][i] >= 0 && hRTe[j][i] > hRTs[j][i])
				{
					hRTs[j + 1][i] = std::fmax(hFSs[j + 1][i], hRTs[j][i]);
					hRTe[j + 1][i] = hFSe[j + 1][i];

					if (hRTe[j + 1][i] <= hRTe[j + 1][i])
					{
						hRTs[j + 1][i] = hRTe[j + 1][i] = BLACK;
					}
				}
				else {
					hRTs[j + 1][i] = hRTe[j + 1][i] = BLACK;
				}
			}
			if (hRTs[j][i] >= 0 && hRTe[j][i] > hRTs[j][i])
			{
				vRTs[j][i + 1] = vFSs[j][i + 1];
				vRTe[j][i + 1] = vFSe[j][i + 1];
			}
			else
			{
				if (vRTs[j][i] >= 0 && vRTe[j][i] > vRTs[j][i]) {
					vRTs[j][i + 1] = std::fmax(vFSs[j][i + 1], vRTs[j][i + 1]);
					vRTe[j][i + 1] = vFSe[j][i + 1];

					if (vRTe[j][i + 1] <= vRTs[j][i + 1])
					{
						vRTe[j][i + 1] = vRTs[j][i + 1] = BLACK;
					}
				}
				else
				{
					vRTe[j][i + 1] = vRTs[j][i + 1] = BLACK;
				}
			}
		}
	}
}

int Frechet::FindPath()
{
	if (vRTe[n2 - 2][n1 - 1] == 1 && hRTe[n2 - 1][n1 - 2] == 1 && (vRTs[n2 - 1][n1 - 2] < vRTe[n2 - 2][n1 - 1] || hRTs[n2 - 1][n1 - 2] < hRTe[n2 - 1][n1 - 2]))
	{
		if (vRTs[0][0] == 0 && hRTs[0][0] == 0 && (vRTs[0][0] < vRTe[0][0] || hRTs[0][0] < hRTe[0][0]))
		{
			return 3; //path confirmed to exist
		}
	}
	return 2; //no path exists
}

/* Setters */

void Frechet::SetEpsilon(double &epsilon)
{
	EPSILON = CGAL::Gmpq(epsilon);
}

/* Getters */

const CGAL::Gmpq Frechet::GetEpsilon()
{
	return EPSILON;
}

const int Frechet::GetSize1()
{
	return n1;
}

const int Frechet::GetSize2()
{
	return n2;
}

const Curve Frechet::GetCurve1()
{
	return curve1;
}

const Curve Frechet::GetCurve2()
{
	return curve2;
}


Frechet::~Frechet()
{
	//TODO: Delete all arrays
}