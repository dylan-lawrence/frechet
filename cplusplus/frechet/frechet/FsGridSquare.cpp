#include "stdafx.h"
#include "FsGridSquare.h"

#include <sstream>

FsGridSquare::FsGridSquare()
{
	
}

FsGridSquare::~FsGridSquare()
{

}

std::ostream& operator<< (std::ostream& os, const FsGridSquare& gs)
{

	std::stringstream ss;

	/* Sample output
	   Note: @ denotes a blank space

	--S:-0.32--E:@0.78--
	|@@@@@@@@@@@@@@@@@@|
	|@@@@@@@@@@@@@@@@@@|
	E:@1.27@@@@@@E:@0.95
	|@@@@@@@@@@@@@@@@@@|
	|@@@@@@@@@@@@@@@@@@|
	S:-0.25@@@@@@S:@0.34
	|@@@@@@@@@@@@@@@@@@|
	|@@@@@@@@@@@@@@@@@@|
	--S:-1.32--E:@0.33--
	
	*/

	ss << std::fixed <<  "--S:";
	if (gs.top->GetStart() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.top->GetStart() << "--E:";
	}
	else
	{
		ss << std::setprecision(2) << gs.top->GetStart() << "--E:";
	}

	if (gs.top->GetEnd() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.top->GetEnd() << "--" << std::endl;
	}
	else
	{
		ss << std::setprecision(2) << gs.top->GetEnd() << "--" << std::endl;
	}
	
	ss << "|" << "                  " << "|" << std::endl << "|" << "                  " << "|" << std::endl << "E:";

	if (gs.left->GetEnd() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.left->GetEnd() << "      " << "E:";
	}
	else
	{
		ss << std::setprecision(2) << gs.left->GetEnd() << "      " << "E:";
	}

	if (gs.right->GetEnd() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.right->GetEnd() << std::endl;
	}
	else
	{
		ss << std::setprecision(2) << gs.right->GetEnd() << std::endl;
	}

	ss << "|" << "                  " << "|" << std::endl << "|" << "                  " << "|" << std::endl << "S:";

	if (gs.left->GetStart() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.left->GetStart() << "      " << "E:";
	}
	else
	{
		ss << std::setprecision(2) << gs.left->GetStart() << "      " << "E:";
	}

	if (gs.right->GetStart() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.right->GetStart() << std::endl;
	}
	else
	{
		ss << std::setprecision(2) << gs.right->GetStart() << std::endl;
	}

	ss << "|" << "                  " << "|" << std::endl << "|" << "                  " << "|" << std::endl << "--S:";

	if (gs.bottom->GetStart() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.bottom->GetStart() << "--E:";
	}
	else
	{
		ss << std::setprecision(2) << gs.bottom->GetStart() << "--E:";
	}

	if (gs.bottom->GetEnd() >= 0)
	{
		ss << " " << std::setprecision(2) << gs.bottom->GetEnd() << "--" << std::endl;
	}
	else
	{
		ss << std::setprecision(2) << gs.bottom->GetEnd() << "--" << std::endl;
	}

	os << ss.str();
	return os;
}