#pragma once

#include <gmp.h>
#include <CGAL/Gmpq.h>

class Edge
{
public:
	Edge();
	~Edge();

	void SetStart(CGAL::Gmpq input);
	void SetEnd(CGAL::Gmpq input);
	CGAL::Gmpq GetStart();
	CGAL::Gmpq GetEnd();

private:
	CGAL::Gmpq start;
	CGAL::Gmpq end;
};

