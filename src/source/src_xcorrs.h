#ifndef __ODAS_SOURCE_XCORRS
#define __ODAS_SOURCE_XCORRS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../general/thread.h"
    #include "../message/msg_xcorrs.h"
    #include "../signal/xcorr.h"
    #include "../utils/pcm.h"

    typedef struct src_xcorrs_obj {

        unsigned long long timeStamp;

        unsigned int frameSize;
        unsigned int nPairs;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        float * buffer;

        msg_xcorrs_obj * out;

    } src_xcorrs_obj;

    typedef struct src_xcorrs_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } src_xcorrs_cfg;

    src_xcorrs_obj * src_xcorrs_construct(const src_xcorrs_cfg * src_xcorrs_config, const msg_xcorrs_cfg * msg_xcorrs_config);

    void src_xcorrs_destroy(src_xcorrs_obj * obj);

    void src_xcorrs_connect(src_xcorrs_obj * obj, msg_xcorrs_obj * out);

    void src_xcorrs_disconnect(src_xcorrs_obj * obj);

    void src_xcorrs_open(src_xcorrs_obj * obj);

    void src_xcorrs_open_file(src_xcorrs_obj * obj);

    void src_xcorrs_close(src_xcorrs_obj * obj);

    void src_xcorrs_close_file(src_xcorrs_obj * obj);

    int src_xcorrs_process(src_xcorrs_obj * obj);

    int src_xcorrs_process_file(src_xcorrs_obj * obj);

    src_xcorrs_cfg * src_xcorrs_cfg_construct(void);

    void src_xcorrs_cfg_destroy(src_xcorrs_cfg * src_xcorrs_config);

#endif