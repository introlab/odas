#ifndef __ODAS_UTILS_PCM
#define __ODAS_UTILS_PCM

    #include <math.h>
    #include <limits.h>

    float pcm_signed08bits2normalized(const char * bytes);

    float pcm_signed16bits2normalized(const char * bytes);

    float pcm_signed24bits2normalized(const char * bytes);

    float pcm_signed32bits2normalized(const char * bytes);

    void pcm_normalized2signed08bits(const float sample, char * bytes);

    void pcm_normalized2signed16bits(const float sample, char * bytes);

    void pcm_normalized2signed24bits(const float sample, char * bytes);

    void pcm_normalized2signed32bits(const float sample, char * bytes);

#endif