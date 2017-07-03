#ifndef __ODAS_SINK_HOPS
#define __ODAS_SINK_HOPS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    typedef struct snk_hops_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        char bytes[4];

        msg_hops_obj * in;

    } snk_hops_obj;

    typedef struct snk_hops_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_hops_cfg;

    snk_hops_obj * snk_hops_construct(const snk_hops_cfg * snk_hops_config, const msg_hops_cfg * msg_hops_config);

    void snk_hops_destroy(snk_hops_obj * obj);

    void snk_hops_connect(snk_hops_obj * obj, msg_hops_obj * in);

    void snk_hops_disconnect(snk_hops_obj * obj);

    int snk_hops_open(snk_hops_obj * obj);

    int snk_hops_close(snk_hops_obj * obj);

    int snk_hops_process(snk_hops_obj * obj);

    int snk_hops_process_file(snk_hops_obj * obj);

    int snk_hops_process_socket(snk_hops_obj * obj);

    int snk_hops_process_soundcard(snk_hops_obj * obj);

    snk_hops_cfg * snk_hops_cfg_construct(void);

    void snk_hops_cfg_destroy(snk_hops_cfg * snk_hops_config);

#endif