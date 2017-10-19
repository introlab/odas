#ifndef __ODAS_SINK_CATEGORIES
#define __ODAS_SINK_CATEGORIES

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_categories.h"
    #include "../utils/pcm.h"

    typedef struct snk_categories_obj {

        unsigned long long timeStamp;

        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        //struct sockaddr_in sserver;
        //char * smessage;
        //int sid;

        msg_categories_obj * in;

    } snk_categories_obj;

    typedef struct snk_categories_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_categories_cfg;

    snk_categories_obj * snk_categories_construct(const snk_categories_cfg * snk_categories_config, const msg_categories_cfg * msg_categories_config);

    void snk_categories_destroy(snk_categories_obj * obj);

    void snk_categories_connect(snk_categories_obj * obj, msg_categories_obj * in);

    void snk_categories_disconnect(snk_categories_obj * obj);

    int snk_categories_open(snk_categories_obj * obj);

    int snk_categories_close(snk_categories_obj * obj);

    int snk_categories_process(snk_categories_obj * obj);

    int snk_categories_process_blackhole(snk_categories_obj * obj);

    int snk_categories_process_file(snk_categories_obj * obj);

    int snk_categories_process_socket(snk_categories_obj * obj);

    int snk_categories_process_terminal(snk_categories_obj * obj);

    snk_categories_cfg * snk_categories_cfg_construct(void);

    void snk_categories_cfg_destroy(snk_categories_cfg * snk_categories_config);

#endif