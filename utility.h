#pragma once

#include <vector>

class utility
{

public:
	class point
	{
	public:
		point(double ax, double ay, double az);
		~point();

		double x;
		double y;
		double z;
	};

	utility(std::vector<point> curve1, std::vector<point> curve2);
	~utility();

	bool reachable(double epsilon);

private:
	std::vector<point> c1;
	std::vector<point> c2;

	unsigned long n1;
	unsigned long n2;

	class edge
	{
	public:
		edge(double s = 0, double e = 0);
		~edge();
		void verify();
		bool passable();

		static double clamp(double val, double lower, double upper);

		double start;
		double end;
	};

	edge calcedge(double epsilon, point center, point p1, point p2);
};

