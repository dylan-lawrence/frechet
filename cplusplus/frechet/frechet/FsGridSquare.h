#pragma once
#include "Edge.h"
#include <iostream>

class FsGridSquare
{

public:
	FsGridSquare();
	~FsGridSquare();

	Edge* top;
	Edge* bottom;
	Edge* left;
	Edge* right;
	friend std::ostream& operator<< (std::ostream& os, const FsGridSquare& gs);

};

