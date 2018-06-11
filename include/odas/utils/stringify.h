#ifndef __ODAS_UTILS_STRINGIFY
#define __ODAS_UTILS_STRINGIFY

	void stringify_float2string(const float * array, const unsigned int nElements, char * string);

	void stringify_short2string(const short * array, const unsigned int nElements, char * string);

	void stringify_string2float(const char * string, float * array, const unsigned int nElements);

	void stringify_string2short(const char * string, short * array, const unsigned int nElements);

#endif