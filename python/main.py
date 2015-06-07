#This is the runnable file for frechet
import plugins.cs1graphics as cs1
from classes.point import Point2D
from classes.curve import Curve
from math import sqrt
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

def calcFreeSpace(p1, p2, p3):
  #p1, p2 represent the start and end of a segment in a curve
  #p3 represents a point on a different curve
  #this will return a (start,end) tuple which will be bound into the freespace
  # (p1) |
  #      |
  #      |
  #     -|- end
  #      |
  #      |
  #     -|- start
  #      |
  #      |
  # (p2) |_______________
  #
  #     (p3)

  #declaring floats for later
  xdiff = p2.getX() - p1.getX()
  ydiff = p2.getY() - p1.getY()
  divisor = xdiff*xdiff + ydiff*ydiff

  if divisor == 0:
    #implies p1,p2 are the same point
    print ('Divisor is 0; x1='+str(p1.getX())+', x2='+str(p2.getX())+', y1='+str(p1.getY())+', y2='+str(p2.getY()))

  b = (p3.getX() - p1.getX()) * xdiff + (p3.getY() - p1.getY()) * ydiff
  q = (p1.getX()**2 + p1.getY()**2 + p3.getX()**2 + p3.getY()**2 - 2*p1.getX()*p3.getX() - 2*p1.getY()*p3.getY() - epsilon**2)*divisor
  root = b*b-q
  if root < 0:
    return (1,1)

  root = sqrt(root)
  t2 = (b+root)/divisor
  t1 = (b-root)/divisor
  if t1<0: t1=0
  if t1>1: t1=1
  if t2<0: t2=0
  if t2>1: t2=1

  start = t1
  end = t2

  if start == end:
    return (-1, -1)

  return (start,end)

def setupFreeSpace(no1, no2, vFSs, vFSe, hFSs, hFSe, vRTs, vRTe, hRTs, hRTe, a, b, epsilon):
  #build lists
  hFSs.extend([[]] * no2)
  hFSe.extend([[]] * no2)
  hRTs.extend([[]] * no2)
  hRTe.extend([[]] * no2)

  vFSs.extend([[]] * (no2-1))
  vFSe.extend([[]] * (no2-1))
  vRTs.extend([[]] * (no2-1))
  vRTe.extend([[]] * (no2-1))

  #Build horizontal freespace
  for i in range (no1-1):
    for j in range (no2-1):
      ret = calcFreeSpace(a[i], a[i+1], b[j])
      hFSs[j].append(ret[0])
      hFSe[j].append(ret[1])

  for i in range(no1-1):
    for j in range(no2-1):
      ret = calcFreeSpace(b[j], b[j+1], a[i])
      vFSs[j].append(ret[0])
      vFSe[j].append(ret[1])

def setReachability(no1, no2, vFSs, vFSe, hFSs, hFSe, vRTs, vRTe, hRTs, hRTe, a, b, epsilon):
    #edge cases
    for i in range(no1):
      vRTs[0].append(vFSs[0][i])
      vRTe[0].append(vFSe[0][i])
      for j in range(no2-1):
        vRTs[j].append(-5)
        vRTe[j].append(-5)

    for j in range(no2):
      hRTs[j].append(hFSs[j][0])
      hRTe[j].append(hFSe[j][0])
      for i in range(no1-1):
        hRTs[j].append(-5)
        hRTe[j].append(-5)

    #rest of the cases in the freespace and reachability
    

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

  #these are 2D arrays
  vFSs = [] #vertical freespace start
  vFSe = [] #vertical freespace end
  hFSs = [] #horizontal freespace start
  hFSe = [] #horizontal freespace end

  vRTs = [] #vertical reachability start
  vRTe = [] #vertical reachability end
  hRTs = [] #horizontal reachability start
  hRTe = [] #horizontal reachability end

  n1 = a.getSize() #length of curve a
  n2 = b.getSize() #length of curve b

  setupFreeSpace(n1, n2, vFSs, vFSe, hFSs, hFSe, vRTs, vRTe, hRTs, hRTe, a, b, epsilon)
  setReachability(n1, n2, vFSs, vFSe, hFSs, hFSe, vRTs, vRTe, hRTs, hRTe, a, b, epsilon)
