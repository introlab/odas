#ifndef __ODAS_SYSTEM_FRAME2FREQ
#define __ODAS_SYSTEM_FRAME2FREQ

    #include <stdlib.h>

    #include "../init/windowing.h"
    #include "../signal/frame.h"
    #include "../signal/freq.h"
    #include "../signal/window.h"
    #include "../utils/fft.h"

    typedef struct frame2freq_obj {

        unsigned int frameSize;
        unsigned int halfFrameSize;

        window_obj * win;
        float * frame;

        fft_obj * fft;

    } frame2freq_obj;

    frame2freq_obj * frame2freq_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    void frame2freq_destroy(frame2freq_obj * obj);

    void frame2freq_process(frame2freq_obj * obj, const frames_obj * frames, freqs_obj * freqs);

#endif