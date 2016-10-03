#pragma once

//#include "stdafx.h"

#include "utility.h"

#include <cmath>
#include <stack>
#include <set>

#include <iostream>

//statics

double utility::edge::clamp(double val, double lower, double upper)
{
	return std::fmax(lower, std::fmin(val, upper));
}

utility::utility(std::vector<utility::point> curve1, std::vector<utility::point> curve2)
{
	c1 = curve1;
	c2 = curve2;

	n1 = c1.size() - 1;
	n2 = c2.size() - 1;
}


bool utility::reachable(double epsilon)
{
	edge left = calcedge(epsilon, c2[0], c1[0], c1[1]);
	edge bottom = calcedge(epsilon, c1[0], c2[0], c2[1]);
	left.verify();
	bottom.verify();

	if (left.start != 0 || bottom.start != 0)
		return false;

	edge top = calcedge(epsilon, c1[n1], c2[n2 - 1], c2[n2]);
	edge right = calcedge(epsilon, c2[n2], c1[n1 - 1], c1[n1]);
	top.verify();
	right.verify();

	if (right.end != 1 || top.end != 1)
		return false;

	
	std::stack<std::vector<int>> jobs = std::stack<std::vector<int>>();

	std::set<std::vector<int>> seen = std::set<std::vector<int>>();
	jobs.push({ 0,0 });
	seen.insert({ 0,0 });

	while (!jobs.empty())
	{
		std::vector<int> ind = jobs.top();

		//std::cout << "Processing... " << ind[0] << "," << ind[1] << std::endl;

		jobs.pop();

		top = calcedge(epsilon, c1[ind[0]+1], c2[ind[1]], c2[ind[1] + 1]);
		right = calcedge(epsilon, c2[ind[1]+1], c1[ind[0]], c1[ind[0] + 1]);
		top.verify();
		right.verify();

		if (ind[0] == n1 - 1 && ind[1] == n2 - 1)
			return true; //we reached end, already checked above

		if (top.passable() && ind[0] + 1 < n1 && seen.count({ ind[0] + 1, ind[1] }) == 0)
		{
			jobs.push({ ind[0] + 1, ind[1] });
			seen.insert({ ind[0] + 1, ind[1] });
		}
		if (right.passable() && ind[1] + 1 < n2 && seen.count({ ind[0], ind[1] + 1 }) == 0)
		{
			jobs.push({ ind[0], ind[1] + 1 });
			seen.insert({ ind[0], ind[1] + 1 });
		}
	}	
	
	return false;
}

utility::edge utility::calcedge(double epsilon, point center, point p1, point p2)
{
	double cx = center.x;
	double cy = center.y;
	double cz = center.z;

	double px = p1.x;
	double py = p1.y;
	double pz = p2.y;

	double vx = p2.x - px;
	double vy = p2.y - py;
	double vz = p2.z - pz;

	double a = vx*vx + vy*vy + vz*vz;

	if (a == 0)
		return edge(-1, -1);

	double b = 2 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
	double c = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy + pz * pz - 2 * pz * cz + cz * cz - epsilon * epsilon;

	double d = b * b - 4 * a * c;

	if (d < 0)
		return edge(-1, -1);

	double start = (-b - std::sqrt(d)) / (2 * a);
	double end = (-b + std::sqrt(d)) / (2 * a);

	return edge(start, end);
}

utility::~utility()
{
}

//Inner classes

utility::edge::edge(double s, double e) 
{
	start = s;
	end = e;
}

bool utility::edge::passable()
{
	if (start >= 0 && start <= 1 && end >= 0 && end <= 1)
		return true;
	else
		return false;
}

void utility::edge::verify()
{
	//modify edge values to bind between 0 and 1

	if (start < 0 && end < 0) //two off hits
	{
		start = end = -1;
		return;
	}

	if (start > 1 && end > 1) //two off hits
	{
		start = end = -1;
		return;
	}

	if (start == end && (start < 0 || start > 1)) //one off hit
	{
		start = end = -1;
		return;
	}

	start = clamp(start, 0, 1);
	end = clamp(end, 0, 1);
	return;
}

utility::edge::~edge() { }

utility::point::point(double ax, double ay, double az)
{
	x = ax;
	y = ay;
	z = az;
}

utility::point::~point() { }
