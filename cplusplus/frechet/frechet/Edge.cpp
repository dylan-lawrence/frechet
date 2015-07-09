#include "stdafx.h"
#include "Edge.h"


Edge::Edge()
{

}

void Edge::SetStart(CGAL::Gmpq input)
{
	start = input;
}

void Edge::SetEnd(CGAL::Gmpq input)
{
	end = input;
}

CGAL::Gmpq Edge::GetStart()
{
	return start;
}

CGAL::Gmpq Edge::GetEnd()
{
	return end;
}

Edge::~Edge()
{

}
