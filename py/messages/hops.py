
import numpy as np

class Hops:

	def __init__(self, nChannels, hopSize, nBits):

		self.nChannels = nChannels
		self.hopSize = hopSize
		self.nBits = nBits

		self.array = np.zeros((nChannels, hopSize), dtype='float')

		self.bits = {8: 128.0, 16: 32768.0, 24: 8388608.0, 32: 2147483648.0}

	def load(self, array):

		self.array = np.transpose(np.reshape(array, (self.hopSize, self.nChannels)) / self.bits[self.nBits]);

	def toJSON(self):

		string = '{"hops":['

		for iChannel in range(0, self.nChannels):

			vector = self.array[iChannel,:]
			string += np.array2string(vector, separator=',', max_line_width = 100000, formatter={'float_kind':lambda vector: "%1.3e" % vector})

			if (iChannel != (self.nChannels-1)):
				string += ","

		string += ']}'

		return string