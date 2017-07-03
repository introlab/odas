#ifndef __ODAS_SYSTEM_FREQ2FRAME
#define __ODAS_SYSTEM_FREQ2FRAME

    #include <stdlib.h>

    #include "../init/windowing.h"
    #include "../signal/frame.h"
    #include "../signal/freq.h"
    #include "../signal/window.h"
    #include "../utils/fft.h"

    typedef struct freq2frame_obj {

        unsigned int frameSize;
        unsigned int halfFrameSize;

        window_obj * win;
        float * frame;

        fft_obj * fft;

    } freq2frame_obj;

    freq2frame_obj * freq2frame_construct_zero(const unsigned int frameSize, const unsigned int halfFrameSize);

    void freq2frame_destroy(freq2frame_obj * obj);

    void freq2frame_process(freq2frame_obj * obj, const freqs_obj * freqs, frames_obj * frames);

#endif