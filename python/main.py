#This is the runnable file for frechet
#from plugins.cs1graphics import cs1graphics as cs1
from classes.point import Point2D
from classes.curve import Curve
import argparse

#Function Definitions
def simpleFileParser(self, filepath):
  #A parser for a generic segment file
  with open(filepath, 'r') as f:
    pass

#Main
if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Python implementation of strong frechet calculation.')
  parser.add_argument('-f', type=str, nargs=2 , help='path to segment data (should be two files)')
