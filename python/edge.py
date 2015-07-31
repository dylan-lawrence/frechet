#calculate edge tester
from math import sqrt

class Point:

  def __init__(self, x, y):
    self.x = x
    self.y = y

def Calculate(radius, p, cp1, cp2):
  xdiff = cp2.x - cp1.x
  ydiff = cp2.y - cp1.y

  b = 2 * ((cp1.x - p.x) * xdiff + (cp1.y - p.y) * ydiff)
  c = (cp1.x - p.x)**2 + (cp1.y - p.y)**2 -radius**2
  a = xdiff**2 + ydiff**2

  det = b**2 - 4*a*c

  if det < 0:
    return 'Determinant is less than 0, edge not reachable'

  end = (-b + sqrt(det))/(2*a)
  start = (-b - sqrt(det))/(2*a)

  return (start, end)

if __name__ == '__main__':
  radius = input("enter the radius: ")
  p1 = input("enter the center (x y): ")
  cp1 = input("enter curvep1: ")
  cp2 = input("enter curvep2: ")

  radius = float(radius)

  p1 = p1.split()
  p1 = Point(float(p1[0]), float(p1[1]))

  cp1 = cp1.split()
  cp1 = Point(float(cp1[0]), float(cp1[1]))

  cp2 = cp2.split()
  cp2 = Point(float(cp2[0]), float(cp2[1]))

  print (Calculate(radius, p1, cp1, cp2))
