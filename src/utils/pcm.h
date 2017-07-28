#ifndef __ODAS_UTILS_PCM
#define __ODAS_UTILS_PCM

    #include <math.h>
    #include <limits.h>

    float pcm_signedXXbits2normalized(const char * bytes, const unsigned int nBytes);

    void pcm_signedXXbits2json(const char * bytes, const unsigned int nBytes, char * json);

    void pcm_normalized2signedXXbits(const float sample, const unsigned int nBytes, char * bytes);

#endif