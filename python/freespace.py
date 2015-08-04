import cs1graphics as cs1

class Point:

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return "<" + str(self.x) + "," + str(self.y) + ">"

    def __str__(self):
        return self.__repr__()

class Edge():

  def __init__(self):
      self.start = -5
      self.end = -5

class FreeSquare:

  def __init__(self):
    self.left = Edge()
    self.right = Edge()
    self.top = Edge()
    self.bottom = Edge()

class FreeSpace:

    def __init__(self, n1, n2, c1, c2, epsilon):
        self.epsilon = epsilon
        self.n1 = n1
        self.n2 = n2
        self.c1 = c1
        self.c2 = c2

        self.grid = []
        for i in range(n1-1):
            self.grid.append([])
        for i in range(n1-1):
            for j in range(n2-1):
                self.grid[i].append(FreeSquare())

    def CalculateSquare(self, n1i, n2i):
        if n1i == 0 and n2i == 0:
            grid[n1i][n2i].left = CalculateEdge(self.c2[n2i], self.c1[n1i], self.c2[n1i+1])

    def CalculateEdge(self, p, cp1, cp2):
        edge = Edge()

        xdiff = cp2.x - cp1.x
        ydiff = cp2.y - cp1.y

        b = 2 * ((cp1.x - p.x) * xdiff + (cp1.y - p.y) * ydiff)
        c = (cp1.x - p.x)**2 + (cp1.y - p.y)**2 -self.epsilon**2
        a = xdiff**2 + ydiff**2

        if a == 0:
            edge.start = -1
            edge.end = -1

        det = b**2 - 4*a*c

        if det < 0:
          print('Determinant is less than 0, edge not reachable')
          edge.start = -1
          edge.end = -1

        edge.end = (-b + sqrt(det))/(2*a)
        edge.start = (-b - sqrt(det))/(2*a)

        return edge


if __name__ == '__main__':
    # manual input
    # epsilon = float(input("Enter epsilon: "))
    # curve1 = []
    # curve2 = []
    #
    # curr = input("Enter a point for curve1 (x y): ")
    # while curr != "":
    #     curr = curr.split()
    #     curve1.append(Point(float(curr[0]), float(curr[1])))
    #     curr = input("Enter a point for curve1 (x y): ")
    #
    # curr = input("Enter a point for curve2 (x y): ")
    # while curr != "":
    #     curr = curr.split()
    #     curve2.append(Point(float(curr[0]), float(curr[1])))
    #     curr = input("Enter a point for curve2 (x y): ")
    #
    # print(epsilon)
    # print(curve1)
    # print(curve2)

    epsilon = 0
    curve1 = []
    curve2 = []

    path = input("Enter file path: ")
    with open(path, "r") as f:
        epsilon = float(f.readline())
        curr = f.readline()
        while curr != "@\n":
            curr = curr.split()
            curve1.append(Point(float(curr[0]), float(curr[1])))
            curr = f.readline()
        curr = f.readline()
        while curr != "@\n":
            curr = curr.split()
            curve2.append(Point(float(curr[0]), float(curr[1])))
            curr = f.readline()

    fs = FreeSpace(len(curve1), len(curve2), curve1, curve2, epsilon)
