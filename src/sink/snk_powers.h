#ifndef __ODAS_SINK_POWERS
#define __ODAS_SINK_POWERS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_powers.h"

    typedef struct snk_powers_obj {

        unsigned long long timeStamp;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        char * buffer;
        unsigned int bufferSize;

        FILE * fp;

        msg_powers_obj * in;

    } snk_powers_obj;

    typedef struct snk_powers_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_powers_cfg;

    snk_powers_obj * snk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config);

    void snk_powers_destroy(snk_powers_obj * obj);

    void snk_powers_connect(snk_powers_obj * obj, msg_powers_obj * in);

    void snk_powers_disconnect(snk_powers_obj * obj);

    void snk_powers_open(snk_powers_obj * obj);

    void snk_powers_open_interface_blackhole(snk_powers_obj * obj);

    void snk_powers_close(snk_powers_obj * obj);

    void snk_powers_close_interface_blackhole(snk_powers_obj * obj);

    int snk_powers_process(snk_powers_obj * obj);

    void snk_powers_process_interface_blackhole(snk_powers_obj * obj);

    void snk_powers_process_format_undefined(snk_powers_obj * obj);

    snk_powers_cfg * snk_powers_cfg_construct(void);

    void snk_powers_cfg_destroy(snk_powers_cfg * snk_powers_config);

#endif