
import argparse
import json
import math
import numpy
import pyaudio
import socket
import time

parser = argparse.ArgumentParser()
parser.add_argument('--host', type = str, help='Host address where ODAS runs')
parser.add_argument('--portIn', type = int, help = 'Port number for input signal')
parser.add_argument('--portOut', type = int, help = 'Port number for output signal')
parser.add_argument('src', type = str, help='Input (file name or soundcard name)')
parser.add_argument('dest', type = str, help='Output (file name)')

args = parser.parse_args()

if (args.host == ""):
	raise ValueError("Missing host address")
if (args.portIn == 0):
	raise ValueError("Missing input port number");
if (args.portOut == 0):
	raise ValueError("Missing output port number");

socketIn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketIn.connect((args.host, args.portIn))

#socketOut = socketOut.socket(socket.AF_INET, socket.SOCK_STREAM)
#socketOut.connect((args.host, args.portOut))

fin = open(args.src, 'rb')
socketIn.send(fin.read())
fin.close()



#array = numpy.fromfile(args.src, numpy.dtype('int' + str(args.nBits)))
#socketIn.send(array);
#socketIn.close(array);

