    
    #include "acorr2pitch.h"

    acorr2pitch_obj * acorr2pitch_construct_zero(const unsigned int nSignals, const unsigned int halfFrameSize, const unsigned int winSize) {

        acorr2pitch_obj * obj;

        obj = (acorr2pitch_obj *) malloc(sizeof(acorr2pitch_obj));

        obj->nSignals = nSignals;
        obj->halfFrameSize = halfFrameSize;
        obj->winSize = winSize;

        return obj;

    }

    void acorr2pitch_destroy(acorr2pitch_obj * obj) {

        free((void *) obj);

    }

    void acorr2pitch_process(acorr2pitch_obj * obj, const acorrs_obj * acorrs, pitches_obj * pitches) {

        unsigned int iSignal;

        signed int iBin;
        signed int iWin;
        signed int iSample;

        float peakValue;
        float nextValue;
        
        float maxValue;
        unsigned int maxIndex;
        char isPeak;
        char peakFound;

        unsigned int peakPrev;
        unsigned int peakNow;
        unsigned int peakNext;
        float RPrev;
        float RNow;
        float RNext;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            maxValue = -INFINITY;
            peakFound = 0x00;

            for (iBin = obj->winSize; iBin < (obj->halfFrameSize - obj->winSize); iBin++) {

                peakValue = acorrs->array[iSignal][iBin];
                isPeak = 0x01;

                for (iWin = -1 * ((signed int) (obj->winSize)); iWin <= ((signed int) (obj->winSize)); iWin++) {

                    iSample = iBin + iWin;
                    nextValue = acorrs->array[iSignal][iSample];

                    if ((iWin != 0) && (peakValue <= nextValue)) {

                        isPeak = 0x00;
                        break;

                    }

                }

                if (isPeak == 0x01) {

                    if (peakValue > maxValue) {

                        maxValue = peakValue;
                        maxIndex = iBin;

                        peakFound = 0x01;

                    }

                }

            }

            if (peakFound == 0x01) {

                peakPrev = maxIndex - 1;
                peakNow = maxIndex;
                peakNext = maxIndex + 1;
                RPrev = acorrs->array[iSignal][peakPrev];
                RNow = acorrs->array[iSignal][peakNow];
                RNext = acorrs->array[iSignal][peakNext];

                pitches->array[iSignal] = ((float) peakNow) + ((RPrev - RNext) / (2*RPrev - 4*RNow + 2*RNext));

            }
            else {

                pitches->array[iSignal] = 0.0f;

            }

        }

    }