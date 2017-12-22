#ifndef __ODAS_SIGNAL_WINDOW
#define __ODAS_SIGNAL_WINDOW

    #include <stdlib.h>
    #include <string.h>

    typedef struct window_obj {

        unsigned int frameSize;
        float * array;
        
    } window_obj;

    window_obj * window_construct_zero(const unsigned int frameSize);

    void window_destroy(window_obj * obj);

#endif