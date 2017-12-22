#ifndef __ODAS_SYSTEM_FRAME2HOP
#define __ODAS_SYSTEM_FRAME2HOP

    #include <stdlib.h>
    #include <string.h>

    #include "../signal/hop.h"
    #include "../signal/frame.h"

    typedef struct frame2hop_obj {

        unsigned int hopSize;
        unsigned int frameSize;
        unsigned int nSignals;

        float ** array;

    } frame2hop_obj;

    frame2hop_obj * frame2hop_construct_zero(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nSignals);

    void frame2hop_destroy(frame2hop_obj * obj);

    void frame2hop_process(frame2hop_obj * obj, const frames_obj * frames, hops_obj * hops);

#endif