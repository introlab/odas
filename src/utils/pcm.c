    #include "pcm.h"

    float pcm_signed08bits2normalized(const char * bytes) {

        int sample32;
        float sampleFloat;

        sample32 = 0;
        sample32 += ((((signed int) bytes[3]) << 0) & 0xFFFFFFFF);

        sampleFloat = (float) sample32;

        sampleFloat /= 128.0f;

        return sampleFloat;

    }

    float pcm_signed16bits2normalized(const char * bytes) {

        int sample32;
        float sampleFloat;

        sample32 = 0;
        sample32 += ((((signed int) bytes[2]) << 0) & 0x000000FF);
        sample32 += ((((signed int) bytes[3]) << 8) & 0xFFFFFF00);

        sampleFloat = (float) sample32;

        sampleFloat /= 32768.0f;

        return sampleFloat;

    }

    float pcm_signed24bits2normalized(const char * bytes) {

        int sample32;
        float sampleFloat;

        sample32 = 0;
        sample32 += ((((signed int) bytes[1]) << 0) & 0x000000FF);
        sample32 += ((((signed int) bytes[2]) << 8) & 0x0000FF00);
        sample32 += ((((signed int) bytes[3]) << 16) & 0xFFFF0000);

        sampleFloat = (float) sample32;

        sampleFloat /= 8388608.0f;

        return sampleFloat;

    }

    float pcm_signed32bits2normalized(const char * bytes) {

        int sample32;
        float sampleFloat;

        sample32 = 0;
        sample32 += ((((signed int) bytes[0]) << 0) & 0x000000FF);
        sample32 += ((((signed int) bytes[1]) << 8) & 0x0000FF00);
        sample32 += ((((signed int) bytes[2]) << 16) & 0x00FF0000);
        sample32 += ((((signed int) bytes[3]) << 24) & 0xFF000000);

        sampleFloat = (float) sample32;

        sampleFloat /= 2147483648.0f;

        return sampleFloat;

    }

    void pcm_normalized2signed08bits(const float sample, char * bytes) {

        int sample32;

        sample32 = (signed int) (roundf(sample * 128.0f));

        bytes[0] = 0x00;
        bytes[1] = 0x00;
        bytes[2] = 0x00;
        bytes[3] = (signed char) ((sample32 & 0x000000FF) >> 0);       

    }

    void pcm_normalized2signed16bits(const float sample, char * bytes) {

        int sample32;

        sample32 = (signed int) (roundf(sample * 32768.0f));

        bytes[0] = 0x00;
        bytes[1] = 0x00;
        bytes[2] = (signed char) ((sample32 & 0x000000FF) >> 0);  
        bytes[3] = (signed char) ((sample32 & 0x0000FF00) >> 8);  

    }

    void pcm_normalized2signed24bits(const float sample, char * bytes) {

        int sample32;

        sample32 = (signed int) (roundf(sample * 8388608.0f));

        bytes[0] = 0x00;
        bytes[1] = (signed char) ((sample32 & 0x000000FF) >> 0);  
        bytes[2] = (signed char) ((sample32 & 0x0000FF00) >> 8);  
        bytes[3] = (signed char) ((sample32 & 0x00FF0000) >> 16); 

    }

    void pcm_normalized2signed32bits(const float sample, char * bytes) {

        int sample32;

        sample32 = (signed int) (roundf(sample * 2147483648.0f));

        bytes[0] = (signed char) ((sample32 & 0x000000FF) >> 0);
        bytes[1] = (signed char) ((sample32 & 0x0000FF00) >> 8);  
        bytes[2] = (signed char) ((sample32 & 0x00FF0000) >> 16);  
        bytes[3] = (signed char) ((sample32 & 0xFF000000) >> 24); 

    }
