#Python version of frechet distance (for testing and prototyping)

# |
# |
# |
# n 0,0
#  m ------

#import ctypes

import sys

class Edge:

  def __init__(self):
    self.start = 0
    self.end = 0

  def passable(self):
      if self.start >= 0 and self.start <= 1 and self.end >= 0 and self.end <= 1:
          return True
      else:
          return False

  def __repr__(self):
      return '{' + self.start + ',' + self.end + '}'

class GridBox:

  def __init__(self):
    self.top = None
    self.right = None
    self.bottom = None
    self.left = None

#helper functions
def clamp(val, low, high):
  return min(max(low, val), high)

def normalize_edge(edge):
  if edge.start < 0 and edge.end < 0: #two off hits
      edge.start = -1
      edge.end = -1
      return

  if edge.start > 1 and edge.end < 1: #two off hits
    edge.start = -1
    edge.end = -1
    return

  if edge.start == edge.end and (edge.start < 0 or edge.start > 1): #one off hit
      edge.start = -1
      edge.end = -1
      return

  #clamp edges
  edge.start = clamp(edge.start,0,1)
  edge.end = clamp(edge.end,0,1)
  return

def readCurve(path): #reads in a curve, returns list of tuple points
  curve = []
  with open(path, 'r') as f:
      for line in f:
        line = line.rstrip('\n').split()
        curve.append((float(line[0]), float(line[1])))

  return curve

if __name__ == '__main__':
    curve1 = readCurve(sys.argv[1])
    curve2 = readCurve(sys.argv[2])

    n = len(curve1)
    m = len(curve2)

    grid = []
    for i in range(n):
        grid.append([Edge()]*m)

    print (grid)
