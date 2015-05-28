#This is the runnable file for frechet
from plugins import cs1graphics as cs1
import argparse

#Function Definitions

#Main
if __name__ == '__main__':
  parser = argparse.ArgumnetParser(description='Python implementation of strong frechet calculation.')
  parser.add_argument('-f', type=str, nargs=2 , help='path to segment data (should be two files)')
