
import numpy as np

class Targets:

	def __init__(self, nTargets):

		self.nTargets = nTargets

		self.xyz = np.zeros((nTargets, 3), dtype='float')
		self.tags = [''] * nTargets

	def toJSON(self):

		string = '{"targets":['

		for iTarget in range(0, self.nTargets):

			string += '{"tag":"' + str(self.tags[iTarget]) + '",'
			string += '"x":' + str(self.xyz[iTarget,0]) + ','
			string += '"y":' + str(self.xyz[iTarget,1]) + ','
			string += '"z":' + str(self.xyz[iTarget,2]) + '}'

			if (iTarget != (self.nTargets-1)):

				string += ','

		string += ']}'

		return string