
   /**
    * \file     demixing2env.c
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
    
    #include <system/demixing2env.h>

    demixing2env_obj * demixing2env_construct_zero(const unsigned int nSeps, const unsigned int nChannels, const unsigned int halfFrameSize) {

        demixing2env_obj * obj;

        obj = (demixing2env_obj *) malloc(sizeof(demixing2env_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        obj->halfFrameSize = halfFrameSize;

        return obj;

    }

    void demixing2env_destroy(demixing2env_obj * obj) {

        free((void *) obj);

    }

    void demixing2env_process(demixing2env_obj * obj, const tracks_obj * tracks, const demixings_obj * demixings, const masks_obj * masks, const envs_obj * envsChannel, envs_obj * envsSeparated) {

        unsigned int iSep;
        unsigned int iChannel;
        unsigned int iBin;
        
        unsigned int iSampleSC;
        unsigned int iSampleBC;
        unsigned int iSampleB;

        float X2;
        float Wreal;
        float Wimag;
        float W2;
        float Y2;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            if (tracks->ids[iSep] != 0) {

                memset(envsSeparated->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize);

                for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                    iSampleSC = iSep * obj->nChannels + iChannel;

                    if (masks->array[iSampleSC] == 1) {                       

                        for (iBin = 0; iBin < obj->halfFrameSize; iBin++) {

                            iSampleBC = iBin * obj->nChannels + iChannel;
                            iSampleB = iBin;

                            X2 = envsChannel->array[iChannel][iSampleB];

                            Wreal = demixings->array[iSep][iSampleBC * 2 + 0];
                            Wimag = demixings->array[iSep][iSampleBC * 2 + 1];
                            W2 = Wreal * Wreal + Wimag * Wimag;

                            Y2 = W2 * X2;

                            envsSeparated->array[iSep][iSampleB] += Y2;

                        }
                        
                    }

                }

            }
            else {

                memset(envsSeparated->array[iSep], 0x00, sizeof(float) * obj->halfFrameSize);

            }

        }

    }
