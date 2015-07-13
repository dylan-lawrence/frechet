#include "stdafx.h"
#include "FsGridSquare.h"

FsGridSquare::FsGridSquare()
{
	
}

FsGridSquare::~FsGridSquare()
{

}

std::ostream& operator<< (std::ostream& os, const FsGridSquare& gs)
{
	os << "Grid Square:" << std::endl
		<< "Left Start: " << gs.left->GetStart() << " Left End: " << gs.left->GetEnd() << std::endl
		<< "Top Start: " << gs.top->GetStart() << " Top End: " << gs.top->GetEnd() << std::endl
		<< "Right Start: " << gs.right->GetStart() << " Right End: " << gs.right->GetEnd() << std::endl
		<< "Bottom Start: " << gs.bottom->GetStart() << " Bottom End: " << gs.bottom->GetEnd();

	return os;
}