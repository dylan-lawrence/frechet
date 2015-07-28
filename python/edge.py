#calculate edge tester
from math import sqrt

class Point:

  def __init__(self, x, y):
    self.x = x
    self.y = y

def Calculate(radius, p, cp1, cp2):
  xdiff = cp2.x - cp1.x
  ydiff = cp2.y - cp1.y

  print ("xdiff: " + str(xdiff))
  print ("ydiff: " + str(ydiff))

  b = 2 * ((cp1.x - p.x) * xdiff + (cp1.y - p.y) * ydiff)
  c = (cp1.x - p.x)**2 + (cp1.y - p.y)**2 -radius**2
  a = xdiff**2 + ydiff**2

  det = b**2 - 4*a*c

  print ("a: " + str(a))
  print ("b: " + str(b))
  print ("c: " + str(c))
  print ("det: " + str(det))

  print ("sqrt det: " + str(sqrt(det)))
  print ("-b + sqrt det: " + str(-b + sqrt(det)))
  print ("2*a: " + str(2*a))
  print ("the whole thing: " + str((-b + sqrt(det))/(2*a)))

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
