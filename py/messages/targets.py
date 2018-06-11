
import numpy as np

class Targets:

	def __init__(self, nTargets):

		self.nTargets = nTargets

		self.xyz = np.zeros((nTargets, 3), dtype='float')
		self.tags = [''] * nTargets

	def toJSON(self):

		string = ''
		string += '{\n'
		string += '    "targets":\n'
		string += '        [\n'

		for iTarget in range(0, self.nTargets):

			string += '            {\n'
			string += '                "tag": ' + '"' + str(self.tags[iTarget]) + '"' + ',\n'
			string += '                "x": ' + str(self.xyz[iTarget,0]) + ',\n'
			string += '                "y": ' + str(self.xyz[iTarget,1]) + ',\n'
			string += '                "z": ' + str(self.xyz[iTarget,2]) + '\n'
			string += '            }'

			if (iTarget != (self.nTargets-1)):

				string += ','

			string += '            \n'

		string += '        ]\n'
		string += '}'

		return string