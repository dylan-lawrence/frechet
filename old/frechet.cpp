//Basic version of frechet distance
//Compile with std=c++11

#include <iostream>
#include <vector>
#include <fstream>

struct Edge
{
  double start;
  double end;
}

struct Square
{
  Edge* top;
  Edge* right;
  Edge* bottom;
  Edge* left;
}

//Utility functions here
double clamp(doulbe& val, double min, double max)
{
  if (val < min) return min;
  if (val > max) return max;
  return val;
}
