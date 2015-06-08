#A class to represent a curve broken up into a discrete set of points

class Curve:

  def __init__(self, *points):
    self._points = points

  def __getitem__(self, index):
    if index >= len(self._points) or index < 0:
      raise IndexError("Index out of range")
    else:
      return self._points[index]

  def getPoints(self):
    return self._points

  def getPoint(self, index): #just for sake of completeness
    return self[index]

  def getSize(self): #returns number of points (not segments!)
    return len(self._points)