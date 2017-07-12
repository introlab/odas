#ifndef __ODAS_SINK_XCORRS
#define __ODAS_SINK_XCORRS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_xcorrs.h"

    typedef struct snk_xcorrs_obj {

        unsigned long long timeStamp;

        unsigned int frameSize;
        unsigned int nPairs;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        msg_xcorrs_obj * in;

    } snk_xcorrs_obj;

    typedef struct snk_xcorrs_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_xcorrs_cfg;

    snk_xcorrs_obj * snk_xcorrs_construct(const snk_xcorrs_cfg * snk_xcorrs_config, const msg_xcorrs_cfg * msg_xcorrs_config);

    void snk_xcorrs_destroy(snk_xcorrs_obj * obj);

    void snk_xcorrs_connect(snk_xcorrs_obj * obj, msg_xcorrs_obj * in);

    void snk_xcorrs_disconnect(snk_xcorrs_obj * obj);

    int snk_xcorrs_open(snk_xcorrs_obj * obj);

    int snk_xcorrs_close(snk_xcorrs_obj * obj);

    int snk_xcorrs_process(snk_xcorrs_obj * obj);

    int snk_xcorrs_process_file(snk_xcorrs_obj * obj);

    int snk_xcorrs_process_socket(snk_xcorrs_obj * obj);

    snk_xcorrs_cfg * snk_xcorrs_cfg_construct(void);

    void snk_xcorrs_cfg_destroy(snk_xcorrs_cfg * snk_xcorrs_config);

#endif