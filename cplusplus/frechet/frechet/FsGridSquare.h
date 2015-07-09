#pragma once
#include "Edge.h"

class FsGridSquare
{

public:
	FsGridSquare();
	~FsGridSquare();

	Edge top;
	Edge bottom;
	Edge left;
	Edge right;
};

