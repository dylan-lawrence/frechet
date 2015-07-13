#pragma once

#include <gmp.h>
#include <CGAL/Gmpq.h>

class Edge
{
public:
	Edge();
	~Edge();

	void SetStart(double input);
	void SetEnd(double input);
	double GetStart();
	double GetEnd();

private:
	double start;
	double end;
};

