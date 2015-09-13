#include "stdafx.h"
#include "PathTree.h"


PathTree::PathTree(FreeSpace *freespace_diagram)
{
	diagram = freespace_diagram;
	root = new Node();
	root->parent = nullptr;
	root->incoming_edge = nullptr;
}

std::vector<double> PathTree::FindPath()
{
	std::vector<double> path = std::vector<double>();
	n1max = diagram->n1 - 2;
	n2max = diagram->n2 - 2;

	FsGridSquare first = diagram->GetSquare(0, 0);
	FsGridSquare last = diagram->GetSquare(n1max,n2max); //TODO Set as last

	//Check that bottom and top corners are reachable
	if (first.bottom->GetStart() != 0 || first.left->GetStart() != 0 || last.right->GetEnd() != 1 || last.top->GetEnd() != 1)
	{
		std::cout << "Bottom or top is not reachable..." << std::endl;
		std::cout << diagram->GetSquare(0, 0) << std::endl;
		std::cout << diagram->GetSquare(n1max, n2max) << std::endl;
		return path;
	}

	//Try and traverse
	Node* n = Traverse(root, path);
	while (n->parent != nullptr)
	{
		std::cout << n->n1 << "," << n->n2;
		
		//TODO: traverse path back properly

		n = n->parent;
	}

	return path;
}

bool PathTree::Passable(Edge* edge)
{
	if (edge->GetStart() >= 0 && edge->GetEnd() <= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

PathTree::Node* PathTree::Traverse(Node* node, std::vector<double> &path)
{
	//Look both right and up
	if (node->n1 < n1max && node->n2 < n2max)
	{
		std::cout << "Can go right and up" << std::endl;
		//Make right
		//If edge can be moved through
		if (Passable(diagram->GetSquare(node->n1, node->n2).right))
		{
			node->rightedge = new Node();
			node->rightedge->n1 = node->n1;
			node->rightedge->n2 = node->n2 + 1;
			node->rightedge->parent = node;
			node->incoming_edge = diagram->GetSquare(node->n1, node->n2).right;
			return Traverse(node->rightedge, path);
		}
		//Make top
		if (Passable(diagram->GetSquare(node->n1, node->n2).top))
		{
			node->topedge = new Node();
			node->topedge->n1 = node->n1 + 1;
			node->topedge->n2 = node->n2;
			node->topedge->parent = node;
			node->incoming_edge = diagram->GetSquare(node->n1, node->n2).top;
			return Traverse(node->topedge, path);
		}
	}
	//Look up only
	else if (node->n1 < n1max)
	{
		std::cout << "Can go up" << std::endl;
		if (Passable(diagram->GetSquare(node->n1, node->n2).top))
		{
			node->topedge = new Node();
			node->topedge->n1 = node->n1 + 1;
			node->topedge->n2 = node->n2;
			node->topedge->parent = node;
			node->incoming_edge = diagram->GetSquare(node->n1, node->n2).top;
			return Traverse(node->topedge, path);
		}
	}
	//Look right only
	else if (node->n2 < n2max)
	{
		std::cout << "Can go right" << std::endl;
		if (Passable(diagram->GetSquare(node->n1, node->n2).right))
		{
			node->rightedge = new Node();
			node->rightedge->n1 = node->n1;
			node->rightedge->n2 = node->n2 + 1;
			node->rightedge->parent = node;
			node->incoming_edge = diagram->GetSquare(node->n1, node->n2).right;
			return Traverse(node->rightedge, path);
		}
	}
	//We are the end cell
	else
	{
		return node;
	}
}

PathTree::~PathTree()
{
}
