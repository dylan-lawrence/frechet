#pragma once

#include "Edge.h"
#include "FsGridSquare.h"
#include "FreeSpace.h"

#include <vector>

class PathTree
{
public: 
	class PathNode
	{
	public:
		int n1, n2;
		double entryval;

		PathNode(int n1n, int n2n, double val)
		{
			n1 = n1n;
			n2 = n2n;
			entryval = val;
		}
	};

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

	Node* Traverse(Node* node, std::vector<PathNode> &path);
	bool Passable(Edge* edge);
	int n1max, n2max;

public:
	PathTree(FreeSpace *freespace_diagram);
	std::vector<PathNode> FindPath();
	~PathTree();
};

