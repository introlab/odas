   
   /**
    * \file     pcm.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */

    #include <utils/pcm.h>

    float pcm_signedXXbits2normalized(const char * bytes, const unsigned int nBytes) {

        int sample32;
        float sampleFloat;

        switch(nBytes) {

            case 1:

                sample32 = 0;
                sample32 += ((((signed char) bytes[3]) << 0) & 0xFFFFFFFF);

                sampleFloat = (float) sample32;

                sampleFloat /= 128.0f;                

            break;

            case 2:

                sample32 = 0;
                sample32 += ((((signed char) bytes[2]) << 0) & 0x000000FF);
                sample32 += ((((signed char) bytes[3]) << 8) & 0xFFFFFF00);

                sampleFloat = (float) sample32;

                sampleFloat /= 32768.0f;

            break;

            case 3:

                sample32 = 0;
                sample32 += ((((signed char) bytes[1]) << 0) & 0x000000FF);
                sample32 += ((((signed char) bytes[2]) << 8) & 0x0000FF00);
                sample32 += ((((signed char) bytes[3]) << 16) & 0xFFFF0000);

                sampleFloat = (float) sample32;

                sampleFloat /= 8388608.0f;

            break;

            case 4:

                sample32 = 0;
                sample32 += ((((signed char) bytes[0]) << 0) & 0x000000FF);
                sample32 += ((((signed char) bytes[1]) << 8) & 0x0000FF00);
                sample32 += ((((signed char) bytes[2]) << 16) & 0x00FF0000);
                sample32 += ((((signed char) bytes[3]) << 24) & 0xFF000000);

                sampleFloat = (float) sample32;

                sampleFloat /= 2147483648.0f;

            break;

        }

        return sampleFloat;

    }

    void pcm_signedXXbits2json(const char * bytes, const unsigned int nBytes, char * json) {

        unsigned int iByte;
        char high;
        char low;

        char hex[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

        for (iByte = 0; iByte < nBytes; iByte++) {

            high = (bytes[iByte] >> 4) & 0x0F;
            low = (bytes[iByte]) & 0x0F;

            json[iByte*2+0] = hex[high];
            json[iByte*2+1] = hex[low];

        }

    }

    void pcm_normalized2signedXXbits(const float sample, const unsigned int nBytes, char * bytes) {

        int sample32;

        switch(nBytes) {

            case 1:

                sample32 = (signed int) (roundf(sample * 128.0f));

                bytes[0] = 0x00;
                bytes[1] = 0x00;
                bytes[2] = 0x00;
                bytes[3] = (signed char) ((sample32 & 0x000000FF) >> 0);    

            break;

            case 2:

                sample32 = (signed int) (roundf(sample * 32768.0f));

                bytes[0] = 0x00;
                bytes[1] = 0x00;
                bytes[2] = (signed char) ((sample32 & 0x000000FF) >> 0);  
                bytes[3] = (signed char) ((sample32 & 0x0000FF00) >> 8);  

            break;

            case 3:

                sample32 = (signed int) (roundf(sample * 8388608.0f));

                bytes[0] = 0x00;
                bytes[1] = (signed char) ((sample32 & 0x000000FF) >> 0);  
                bytes[2] = (signed char) ((sample32 & 0x0000FF00) >> 8);  
                bytes[3] = (signed char) ((sample32 & 0x00FF0000) >> 16); 

            break;

            case 4:

                sample32 = (signed int) (roundf(sample * 2147483648.0f));

                bytes[0] = (signed char) ((sample32 & 0x000000FF) >> 0);
                bytes[1] = (signed char) ((sample32 & 0x0000FF00) >> 8);  
                bytes[2] = (signed char) ((sample32 & 0x00FF0000) >> 16);  
                bytes[3] = (signed char) ((sample32 & 0xFF000000) >> 24); 

            break;

        }

    }
