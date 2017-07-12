#ifndef __ODAS_SOURCE_POTS
#define __ODAS_SOURCE_POTS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_pots.h"
    #include "../signal/pot.h"
    #include "../utils/pcm.h"

    typedef struct src_pots_obj {

        unsigned long long timeStamp;

        unsigned int nPots;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        float * buffer;

        msg_pots_obj * out;

    } src_pots_obj;

    typedef struct src_pots_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } src_pots_cfg;

    src_pots_obj * src_pots_construct(const src_pots_cfg * src_pots_config, const msg_pots_cfg * msg_pots_config);

    void src_pots_destroy(src_pots_obj * obj);

    void src_pots_connect(src_pots_obj * obj, msg_pots_obj * out);

    void src_pots_disconnect(src_pots_obj * obj);

    void src_pots_open(src_pots_obj * obj);

    void src_pots_open_file(src_pots_obj * obj);

    void src_pots_close(src_pots_obj * obj);

    void src_pots_close_file(src_pots_obj * obj);

    int src_pots_process(src_pots_obj * obj);

    int src_pots_process_file(src_pots_obj * obj);

    src_pots_cfg * src_pots_cfg_construct(void);

    void src_pots_cfg_destroy(src_pots_cfg * src_pots_config);

#endif