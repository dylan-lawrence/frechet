#pragma once

#include "Edge.h"
#include "FsGridSquare.h"
#include "FreeSpace.h"

#include <vector>

class PathTree
{
private:
	class Node
	{
	public:
		int n1, n2; //Coordinate of the node
		Node* parent;
		Node* rightedge;
		Node* topedge;
		Edge* incoming_edge;
	};

	FreeSpace* diagram;
	Node* root;

	Node* Traverse(Node* node, std::vector<double> &path);
	bool Passable(Edge* edge);
	int n1max, n2max;

public:
	PathTree(FreeSpace *freespace_diagram);
	std::vector<double> FindPath();
	~PathTree();
};

