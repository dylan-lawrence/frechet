#pragma once

#include "FsGridSquare.h"

class FreeSpace
{

public:
	FreeSpace(int n1, int n2);
	~FreeSpace();

	FsGridSquare GetSquare(int n1i, int n2i);

private:
	FsGridSquare** grid;
	int n1, n2;
};

