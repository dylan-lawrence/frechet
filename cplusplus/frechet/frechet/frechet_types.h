#include "stdafx.h"

#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/iterator.h>
#include <gmp.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Exact_circular_kernel_2 Kernel;
typedef CGAL::Point_2<Kernel> Point_2;
typedef CGAL::Circular_arc_point_2<Kernel> Circular_arc_point_2;
typedef CGAL::Line_2<Kernel> Line_2;
typedef CGAL::Line_arc_2<Kernel> LineArc_2;
typedef CGAL::Circle_2<Kernel> Circle_2;
typedef std::pair<Circular_arc_point_2, unsigned> IntersectOut;