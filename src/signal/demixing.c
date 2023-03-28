
   /**
    * \file     demixing.c
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

    #include <signal/demixing.h>
    
    demixings_obj * demixings_construct_zero(const unsigned int halfFrameSize, const unsigned int nSeps, const unsigned int nChannels) {

        demixings_obj * obj;
        unsigned int iSep;

        obj = (demixings_obj *) malloc(sizeof(demixings_obj));
        
        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        obj->array = (float **) malloc(sizeof(float *) * obj->nSeps);
        
        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            obj->array[iSep] = (float *) malloc(sizeof(float) * obj->halfFrameSize * obj->nChannels * 2);
            memset(obj->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize * obj->nChannels * 2);

        }

        return obj;

    }

    void demixings_destroy(demixings_obj * obj) {

        unsigned int iSep;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            free((void *) obj->array[iSep]);

        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void demixings_copy(demixings_obj * dest, const demixings_obj * src) {

        unsigned int iSep;

        for (iSep = 0; iSep < src->nSeps; iSep++) {
            memcpy(dest->array[iSep], src->array[iSep], src->halfFrameSize * src->nChannels * 2 * sizeof(float));
        }  

    }

    void demixings_zero(demixings_obj * obj) {

        unsigned int iSep;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {
            memset(obj->array[iSep], 0x00, obj->halfFrameSize * obj->nChannels * 2 * sizeof(float));
        }

    }

    void demixings_printf(const demixings_obj * obj) {

        unsigned int iBin;
        unsigned int iSep;
        unsigned int iChannel;

        float real;
        float imag;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("\nSource index: %u\n",iSep);

            for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                printf("(%03u): ",iBin);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    real = obj->array[iSep][iBin * obj->nChannels * 2 + iChannel * 2 + 0];
                    imag = obj->array[iSep][iBin * obj->nChannels * 2 + iChannel * 2 + 1];

                    printf("(%+1.2f + %1.2fi) ", real, imag);

                }

                printf("\n");

            }

        }

    }
