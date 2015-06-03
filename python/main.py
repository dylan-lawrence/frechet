#This is the runnable file for frechet
import plugins.cs1graphics as cs1
from classes.point import Point2D
from classes.curve import Curve
import argparse

verbosity = 0

def log(message, level):
  #wrap up prints in a level lock
  if verbosity > level:
    print(message)
  else:
    return

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

def setupFreespace(canvas, n1, n2):
  #function for drawing the grid itself, does not do any real work
  #n1,n2 are sizes of curves
  #NOTE: For our use we can assume the canvas is 250 x 250
  for i in range(n1):
    path = cs1.Path(cs1.Point(25,(200/n1)*i+25),cs1.Point(225,(200/n1)*i+25))
    canvas.add(path)
  for i in range(n2):
    path = cs1.Path(cs1.Point((200/n2)*i+25, 25),cs1.Point((200/n2)*i+25, 225))
    canvas.add(path)

#Main
if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Python implementation of strong frechet calculation.')
  parser.add_argument('-f', type=str, nargs=2 , help='path to segment data (should be two files)')
  parser.add_argument('--filetype', type=str, help='the type of the files specified in -f available types: simple')
  parser.add_argument ('-g', action='store_true', default=False, help='choose whether to display visual output')
  parser.add_argument('-d', type=float, help='delay between operations, if left blank, defaults to 0')
  parser.add_argument('-e', type=float, help='epsilon value to test')
  parser.add_argument('-v', type=int, help='verbosity level, 1 is low logging, 2 is full logging')

  args = parser.parse_args()

  #setup startup binding
  d = args.d
  epsilon = args.e
  verbosity = args.v

  mode = args.filetype
  if mode == None: mode = 'simple'

  curves = constructCurves(args.f[0],args.f[1],mode)

  #aliasing curves as a and b for shortness
  a = curves[0]
  b = curves[1]
