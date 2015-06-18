#Frechet
An implementation for strong frechet distance calculation using CGAL

## Definitions and Explanations
The frechet distance is a measure of the similarity of two curves taking into account location and ordering of the points contained within either curve. The frechet distance can be compared to the Hausdorff distance which is another measure of curve similarity. These measures however do not always return a similar answer. [As can be seen here.](http://math.stackexchange.com/questions/764286/hausdorff-and-fr%C3%A9chet-distances)

In more simplistic terms we can define the frechet distance as "how long of a leash do I need to walk my dog?" In the terms of this software, we are using strong frechet, meaning neither you nor your dog can backtrack, or to define this in a more mathematicl model, we can view the curves as a single-directed graph in which all points direct only to the next point in the line, or to nowhere (if we are at the end).

## Project Structure
This project is structured to compartmentalize each piece of its runtime.

The `main.cpp` file is using solely as a driver for single-use run of two curves and a specified epsilon.

The `FileParser.cpp` file contains the parsing method for converting files containg curves into runtime data types.

The `Frechet.cpp` file contains all code pertaining to the actually runtime of the frechet calculation as well as all specified data types.

### In-Depth details
TODO

### Necessary Dependencies
To compile and run the above code you will need both CGAL and boost standard libraries. This particular software is using CGAL 4.6 and boost 1.58.0. Additionally you will need the GMP library, which should be bundled with CGAL in the auxiliary/gmp directory

### Contact Information
If you have any questions or need assistance with anything in the above code, please contact Dylan Lawrence [dlawre14 (at) slu (dot) edu]
