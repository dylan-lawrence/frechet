// frechet.cpp : Defines the entry point for the console application.
//
#pragma once

//#include "stdafx.h"

#include "utility.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <map>
#include <set>

#include <math.h>
#include <iomanip>

utility::point kmerPoint(std::string kmer, double prob, double size)
{
	double x = 0, y = 0, z = 0;
	y = prob;

	for (char l : kmer)
	{
		if (l == 'A')
		{
			x += -0.5;
			z += 1;
		}
		else if (l == 'G')
		{
			x += 0.5;
			z += 1;
		}
		else if (l == 'T')
		{
			x += -0.5;
			z += -1;
		}
		else if (l == 'C')
		{
			x += 0.5;
			z += -1;
		}
	}
	return utility::point(x/size, y, z/size);
}

double maxeps(utility &obj, double start_val, double error)
{
	double eps = start_val;
	double left = error;
	double right = eps;
	bool found = false;

	while (fabs(left - right) > error)
	{
	//	std::cout << "left: " << left << " right: " << right;
	  	std::cout << " testing reachablity for eps: " << std::setprecision(25) << eps << std::endl;
		if (obj.reachable(eps))
		{
			found = true;
			right = eps;
			eps = (right + left) / 2.0;
		}
		else
		{
			if (!found)
			{
				eps *= 2;
				right = eps;
			}
			else
			{
				left = eps;
				eps = (right + left) / 2.0;
			}
		}

		if (left > right)
		{
			double temp = left;
			left = right;
			right = temp;
		}
	}
	//std::cout << "returning... left: " << left << " right: " << right << std::endl;
	//std::cout << "abs diff: " << fabs(left - right) << " error is: " << error  << std::endl;
	return eps;
}

int main(int argc, char* argv[])
{

	if (argc != 3)
		return -1;

	std::string f1 = argv[1];
	std::string f2 = argv[2];

	//std::cout << "fileshort: " << f1 << std::endl;

	std::ifstream curve1;
	curve1.open(f1);

	std::ifstream curve2;
	curve2.open(f2);

	std::map<std::string, int> count1 = std::map<std::string, int>();
	std::map<std::string, int> count2 = std::map<std::string, int>();

	std::string line;
	while (std::getline(curve1, line))
	{
		int ind = line.find(':');
		std::string kmer = line.substr(0, ind);
		std::string count = line.substr(ind+1, line.size());

		count1.insert(std::pair<std::string, int> (kmer, std::stoi(count)));
	}

	line.clear();
	while (std::getline(curve2, line))
	{
		int ind = line.find(':');
		std::string kmer = line.substr(0, ind);
		std::string count = line.substr(ind + 1, line.size());

		count2.insert(std::pair<std::string, int>(kmer, std::stoi(count)));
	}


	curve1.close();
	curve2.close();

	//std::cout << "count 1: " << count1.size() << " count 2: " << count2.size() << std::endl;

	int sum1 = 0;
	for (auto& kmer : count1)
	{
		sum1 += kmer.second;
	}

	std::map<std::string, double> countprob1 = std::map<std::string, double>();
	for (auto& kmer : count1)
	{
		countprob1.insert(std::pair<std::string, double>(kmer.first, log((float) kmer.second / (float) sum1)));
	}

	int sum2 = 0;
	for (auto& kmer : count2)
	{
		sum2 += kmer.second;
	}

	std::map<std::string, double> countprob2 = std::map<std::string, double>();
	for (auto& kmer : count2)
	{
		countprob2.insert(std::pair<std::string, double>(kmer.first, log((float)kmer.second / (float)sum2)));
	}

//TODO: Generate better curves
	std::set<std::string> kmers = std::set<std::string>();
	for (auto& kmer : count1)
		kmers.insert(kmer.first);
	for (auto& kmer : count2)
		kmers.insert(kmer.first);

	std::vector<utility::point> c1 = std::vector<utility::point>();
	std::vector<utility::point> c2 = std::vector<utility::point>();
	for (auto& kmer : kmers)
	{
		c1.push_back(kmerPoint(kmer, countprob1[kmer],31));
		c2.push_back(kmerPoint(kmer, countprob2[kmer],31));
	}

	std::cout << "Done with pre-processing" << std::endl;

	utility frechet = utility::utility(c1, c2);

	double eps = maxeps(frechet, 20, 0.25);

	std::stringstream ss;
	ss << f1 << "--" << f2 << " -- epsilon|" << std::setprecision(25) << eps << std::endl;
	std::string output = ss.str();

	std::cout << output;

	std::ofstream out;
	out.open("counts.txt", std::ios::app);
	out << output;
	out.close();

//	std::cin.clear();
//	std::cin.get();
}
