
   /**
    * \file     xcorr2xcorr.c
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
    
    #include <system/xcorr2xcorr.h>

    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize) {

        xcorr2xcorr_obj * obj;

        obj = (xcorr2xcorr_obj *) malloc(sizeof(xcorr2xcorr_obj));

        obj->frameSize = frameSize;

        return obj;

    }

    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj) {

        free((void *) obj);

    }

    void xcorr2xcorr_process_max(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoas_obj * tdoas, const deltas_obj * deltas, const pairs_obj * pairs, xcorrs_obj * xcorrsMax) {

        unsigned int iSignal;
        unsigned int iSampleMax;
        unsigned int iSampleMaxLeft;
        unsigned int iSampleMaxRight;
        unsigned int iSample;
        unsigned int delta;
        float maxValue;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            if (pairs->array[iSignal] == 0x01) {

                delta = deltas->array[iSignal];
                iSampleMaxLeft = tdoas->min[iSignal];
                iSampleMaxRight = tdoas->max[iSignal];

                for (iSampleMax = iSampleMaxLeft; iSampleMax <= iSampleMaxRight; iSampleMax++) {

                    maxValue = xcorrs->array[iSignal][iSampleMax];

                    for (iSample = (iSampleMax-delta); iSample <= (iSampleMax+delta); iSample++) {

                        if (xcorrs->array[iSignal][iSample] > maxValue) {

                            maxValue = xcorrs->array[iSignal][iSample];

                        }

                    }

                    xcorrsMax->array[iSignal][iSampleMax] = maxValue;

                }

            }

        }

    }

    void xcorr2xcorr_process_reset(xcorr2xcorr_obj * obj, const tdoas_obj * tdoas, const deltas_obj * deltas, const pairs_obj * pairs, const unsigned int iPoint, xcorrs_obj * xcorrs) {

        unsigned int iSignal;

        signed int iMiddle;
        float vMiddle;
        signed int iLeft;
        float vLeft;
        signed int iRight;
        float vRight;

        unsigned int iSample;
        unsigned int nSamples;
        unsigned int delta;

        for (iSignal = 0; iSignal < xcorrs->nSignals; iSignal++) {

            if (pairs->array[iSignal] == 0x01) {

                iMiddle = tdoas->array[iPoint * tdoas->nPairs + iSignal];
                vMiddle = xcorrs->array[iSignal][iMiddle];

                for (iLeft = (iMiddle-1); iLeft >= 0; iLeft--) {
                    
                    vLeft = xcorrs->array[iSignal][iLeft];

                    if (vLeft > vMiddle) {
                        break;
                    }

                    xcorrs->array[iSignal][iLeft] = 0.0f;

                }
                for (iRight = (iMiddle+1); iRight < obj->frameSize; iRight++) {

                    vRight = xcorrs->array[iSignal][iRight];

                    if (vRight > vMiddle) {
                        break;
                    }

                    xcorrs->array[iSignal][iRight] = 0.0f;

                }

                delta = deltas->array[iSignal];
                iSample = tdoas->array[iPoint * tdoas->nPairs + iSignal] - delta;
                nSamples = 2 * delta + 1;

                memset(&(xcorrs->array[iSignal][iSample]), 0x00, sizeof(float) * nSamples);

            }

        }

    }
