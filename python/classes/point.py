#A set of point classes

class Point2D:

  def __init__(self, x=0, y=0):
    self._x = x
    self._y = y

  def getX(self):
    return self._x

  def getY(self):
    return self._y
