	
	#include <utils/stringify.h>

	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>

	void stringify_float2string(const float * array, const unsigned int nElements, char * string) {

		unsigned int iElement;
		unsigned int sample;
		char word[9];

		string[0] = 0x00;

		for (iElement = 0; iElement < nElements; iElement++) {

			memcpy(&sample, &(array[iElement]), sizeof(float));

			word[0] = 0x00;
			sprintf(word, "%x", sample);

			strcat(string, word);

		}

	}

	void stringify_short2string(const short * array, const unsigned int nElements, char * string) {

		unsigned int iElement;
		unsigned short sample;
		char word[5];

		string[0] = 0x00;

		for (iElement = 0; iElement < nElements; iElement++) {

			memcpy(&sample, &(array[iElement]), sizeof(short));

			word[0] = 0x00;
			sprintf(word, "%x", sample);

			strcat(string, word);

		}		

	}

	void stringify_string2float(const char * string, float * array, const unsigned int nElements) {

		unsigned int nChars;

		unsigned int iElement;
		char sample[9];
		unsigned int number;

		nChars = strlen(string);

		if (nElements != (nChars / 8)) {
			
			printf("Invalid string size.\n");
			exit(EXIT_FAILURE);

		}

		for (iElement = 0; iElement < nElements; iElement++) {

			memset(sample, 0x00, sizeof(char) * 9);
			memcpy(sample, &(string[iElement * 8]), sizeof(char) * 8);

			number = strtol(sample, NULL, 16);
			memcpy(&(array[iElement]), &number, sizeof(float));

		}

	}

	void stringify_string2short(const char * string, short * array, const unsigned int nElements) {

		unsigned int nChars;

		unsigned int iElement;
		char sample[5];
		unsigned int number;

		nChars = strlen(string);

		nChars = strlen(string);

		if (nElements != (nChars / 4)) {
			
			printf("Invalid string size.\n");
			exit(EXIT_FAILURE);

		}

		for (iElement = 0; iElement < nElements; iElement++) {

			memset(sample, 0x00, sizeof(char) * 5);
			memcpy(sample, &(string[iElement * 4]), sizeof(char) * 4);

			number = strtol(sample, NULL, 16);
			memcpy(&(array[iElement]), &number, sizeof(float));

		}

	}	