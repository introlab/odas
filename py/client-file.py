
from messages.hops import Hops
from messages.targets import Targets

import argparse
import json
import math
import numpy
import socket
import time

parser = argparse.ArgumentParser()
parser.add_argument('--fS', type=int, default = 0, help='Sample rate')
parser.add_argument('--nChannels', type=int, default = 0, help='Number of channels')
parser.add_argument('--hopSize', type=int, default = 0, help='Number of samples per hop')
parser.add_argument('--nBits', type=int, default = 0, help='Number of bits per sample')
parser.add_argument('--x', type=float, default = 0.0, help='X direction for target')
parser.add_argument('--y', type=float, default = 0.0, help='Y direction for target')
parser.add_argument('--z', type=float, default = 1.0, help='Z direction for target')
parser.add_argument('src', type = str, help='Input (file name or soundcard name)')
parser.add_argument('host', type = str, help='Host address where ODAS runs')
parser.add_argument('dest', type = str, help='Output (file name)')

args = parser.parse_args()

if (args.fS == 0):
	raise ValueError("Missing sample rate")
if (args.nChannels == 0):
	raise ValueError("Missing number of channels")
if (args.hopSize == 0):
	raise ValueError("Missing hop size")
if (args.nBits == 0):
	raise ValueError("Missing number of bits per sample")

# Get server info

host_exprs = args.host.split(':')

host_name = host_exprs[0]
host_port = int(host_exprs[1])

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect((host_name, host_port))

# Instantiate messages

hops = Hops(args.nChannels, args.hopSize, args.nBits)
targets = Targets(1)

targets.tags[0] = 'target'
targets.xyz[0,0] = args.x
targets.xyz[0,1] = args.y
targets.xyz[0,2] = args.z

# Open raw data from file

array = numpy.fromfile(args.src, numpy.dtype('int' + str(args.nBits)))
blockSize = args.hopSize * args.nChannels
nFrames = math.floor(len(array) / blockSize)

fid = open(args.dest, 'wb')

for iFrame in range(0, nFrames):

	iFrameStart = iFrame * blockSize
	iFrameStop = iFrameStart + blockSize

	samples = array[range(iFrameStart,iFrameStop)]

	hops.load(samples)

	if (iFrame == 0):

		string = ''
		string += '{\n'
		string += '    "raw":'
		string += ('\n' + hops.toJSON()).replace('\n','\n    ')
		string += ',\n\n' 
		string += '    "aim":'
		string += ('\n' + targets.toJSON()).replace('\n','\n    ')
		string += '\n}';

	socket.send(string.encode('utf-8'))
	reply = socket.recv(65536);

	content = json.loads(reply.decode())

	separated = numpy.asarray(numpy.round(numpy.asarray(content['separated']['hops'][0]) * 32768.0), 'int16');

	fid.write(separated.tobytes())

fid.close()
	
socket.close()
