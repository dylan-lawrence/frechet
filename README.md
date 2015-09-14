# Frechet - README NOT FINISHED!!
An implementation for strong frechet distance calculation using CGAL

### Definitions and Explanations
The frechet distance is a measure of the similarity of two curves taking into account location and ordering of the points contained within either curve. The frechet distance can be compared to the Hausdorff distance which is another measure of curve similarity. These measures however do not always return a similar answer. [As can be seen here.](http://math.stackexchange.com/questions/764286/hausdorff-and-fr%C3%A9chet-distances)

In more simplistic terms we can define the frechet distance as "how long of a leash do I need to walk my dog?" In the terms of this software, we are using strong frechet, meaning neither you nor your dog can backtrack, or to define this in a more mathematicl model, we can view the curves as a single-directed graph in which all points direct only to the next point in the line, or to nowhere (if we are at the end).

### Algorithm Design
The general outline of this algorithm is the following:

* Load in curves
* Format curves to a vector of Point_2
* Create FreeSpace object to represent the freespace
* Run CalculateSquare for all cells in the diagram (this is done externally by the user in their main or other function.)
* When all cells are calculated create PathTree object
* Call FindPath()
* This returns a vector containing PathNode objects
* Parse vector to return the path

#### How the algorithm works

First, let's look at a half drawn toy example

TODO: Pictures

### File Breakdown

#### `main.cpp`

`main.cpp` is the front end of this application. When completed, it will contain both single run and optimize run versions of this code. It also wraps up reading curve files into the code.

#### `frechet_types.h`

`frechet_types.h` is just a fnacy import handler and `typedef` file. This wraps up all CGAL `typedef` calls and keeps them neat, tidy, and easy to access by other classes.

#### `Edge.h/.cpp`

`Edge.h/.cpp` is the implementation of the `Edge` class. The `Edge` class is little more than a `struct` with a fancy name, but was required due to some issues with CGAL's pointer pooling.

### Necessary Dependencies
To compile and run the above code you will need both CGAL and boost standard libraries. This particular software is using CGAL 4.6 and boost 1.58.0. Additionally you will need the GMP library, which should be bundled with CGAL in the auxiliary/gmp directory

### Contact Information and Acknowledgements
If you have any questions or need assistance with anything in the above code, please contact Dylan Lawrence [dlawre14 (at) slu (dot) edu] if unavailable you can also contact Erin Chambers [echambe5 (at) slu (dot) edu].

Special thanks to Carola Wenk for helping with the basic concepts of this algorithm and some of the gritty math.
