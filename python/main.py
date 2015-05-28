#This is the runnable file for frechet
import plugins.cs1graphics as cs1
from classes.point import Point2D
from classes.curve import Curve
import argparse

#Function Definitions
def simpleFileParser(filepath):
  #A parser for a generic segment file, returns a list of points
  points = []
  with open(filepath, 'r') as f:
    for l in f:
      l = l.lstrip('(').rstrip(')\n').split(',')
      print (l)
      points.append(Point2D(float(l[0]),float(l[1])))
  return points

def tocs1Point(point):
  return cs1.Point(point.getX(), point.getY())

def constructCurves(filepath1, filepath2, mode='simple'):
  #take the two files and construct curve objects out of them
  #returns a tuple of each segment
  p1 = None
  p2 = None
  if mode == 'simple':
    p1 = simpleFileParser(filepath1)
    p2 = simpleFileParser(filepath2)
  s1 = Curve(*p1)
  s2 = Curve(*p2)
  return (s1, s2)

def drawCurve(curve, canvas, color='black'):
  #utility method for drawing curves on the canvas
  for p in curve.getPoints():
    circ = cs1.Circle(5, cs1.Point(p.getX(), p.getY()))
    circ.setFillColor(color)
    canvas.add(circ)

  ps = [tocs1Point(p) for p in curve.getPoints()]

  path = cs1.Path(*ps)
  path.setBorderColor(color)
  path.setBorderWidth(3)
  canvas.add(path)
    #TODO: draw path

  def setupFreespace(canvas):
    #function for drawing the grid itself, does not do any real work
    pass


#Main
if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Python implementation of strong frechet calculation.')
  parser.add_argument('-f', type=str, nargs=2 , help='path to segment data (should be two files)')
  parser.add_argument('--filetype', type=str, help='the type of the files specified in -f available types: simple')
  parser.add_argument ('-v', action='store_true', default=False, help='choose whether to display visual output')
  parser.add_argument('-d', type=float, help='delay between operations, if left blank, defaults to 0')

  args = parser.parse_args()

  d = args.d

  mode = args.filetype
  if mode == None: mode = 'simple'

  curves = constructCurves(args.f[0],args.f[1],mode)

  if args.v:
     freecanv = cs1.Canvas(250, 250, None, 'Freespace Diagram')
     curvecanv = cs1.Canvas(250, 250, None, 'Curves at Runtime')
     drawCurve(curves[0], curvecanv, 'red')
     drawCurve(curves[1], curvecanv, 'blue')

  else:
     pass
