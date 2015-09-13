#include "stdafx.h"
#include "Edge.h"

Edge::Edge()
{
	start = end = 0;
}

void Edge::SetStart(double input)
{
	start = input;
}

void Edge::SetEnd(double input)
{
	end = input;
}

double Edge::GetStart()
{
	return start;
}

double Edge::GetEnd()
{
	return end;
}

Edge::~Edge()
{

}
