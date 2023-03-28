
   /**
    * \file     beampattern.c
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
    
    #include <signal/beampattern.h>

    beampatterns_obj * beampatterns_construct_zero(const unsigned int nChannels, const unsigned int nThetas) {

        beampatterns_obj * obj;

        obj = (beampatterns_obj *) malloc(sizeof(beampatterns_obj));

        obj->nChannels = nChannels;
        obj->nThetas = nThetas;
        
        obj->minThetas = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->minThetas, 0x00, sizeof(float) * nChannels);

        obj->maxThetas = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->maxThetas, 0x00, sizeof(float) * nChannels);

        obj->deltaThetas = (float *) malloc(sizeof(float) * nChannels);
        memset(obj->deltaThetas, 0x00, sizeof(float) * nChannels);
        
        obj->gains = (float *) malloc(sizeof(float) * nThetas * nChannels);
        memset(obj->gains, 0x00, sizeof(float) * nThetas * nChannels);

        return obj;

    }

    void beampatterns_destroy(beampatterns_obj * obj) {

        free((void *) obj->minThetas);
        free((void *) obj->maxThetas);
        free((void *) obj->deltaThetas);
        free((void *) obj->gains);
        free((void *) obj);

    }

    void beampatterns_printf(const beampatterns_obj * obj) {

        unsigned int iChannel;
        unsigned int iTheta;

        for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            for (iTheta = 0; iTheta < obj->nThetas; iTheta++) {

                printf("(%02u,%04u): %1.3f\n", iChannel, iTheta, obj->gains[obj->nThetas * iChannel + iTheta]);

            }

        }

    }
