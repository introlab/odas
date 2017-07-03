
    #include "windowing.h"

    window_obj * windowing_hann(const unsigned int frameSize) {

        window_obj * obj;
        unsigned int iSample;

        obj = window_construct_zero(frameSize);

        if ( frameSize == 1 ) {

        	obj->array[0] = 1.0f;

        }
        else {

            for ( iSample = 0; iSample < frameSize; iSample++ ) {
                
                obj->array[iSample] = 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( frameSize - 1 ) ) ) );
                                
            }


        }

        return obj;

    }

    window_obj * windowing_roothann(const unsigned int frameSize) {

        window_obj * obj;
        unsigned int iSample;

        obj = window_construct_zero(frameSize);

        if ( frameSize == 1 ) {

            obj->array[0] = 1.0f;

        }
        else {

            for ( iSample = 0; iSample < frameSize; iSample++ ) {

                obj->array[iSample] = sqrtf( 0.5f * ( 1.0f - cosf( 2 * M_PI * ( (float) iSample ) / ( (float) ( frameSize - 1 ) ) ) ) );

            }

        }

        return obj;

    }
