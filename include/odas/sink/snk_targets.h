#ifndef __ODAS_SINK_TARGETS
#define __ODAS_SINK_TARGETS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #include "../message/msg_targets.h"

    typedef struct snk_targets_obj {

        unsigned long long timeStamp;

        unsigned int nTargets;

        char * buffer;
        unsigned int bufferSize;

        int server_id;
        int connection_id;     
        unsigned int port;       
        
        msg_targets_obj * in;

    } snk_targets_obj;

    typedef struct snk_targets_cfg {

        unsigned int port;

    } snk_targets_cfg;

    snk_targets_obj * snk_targets_construct(const snk_targets_cfg * snk_targets_config, const msg_targets_cfg * msg_targets_config);

    void snk_targets_destroy(snk_targets_obj * obj);

    void snk_targets_connect(snk_targets_obj * obj, msg_targets_obj * in);

    void snk_targets_disconnect(snk_targets_obj * obj);

    void snk_targets_open(snk_targets_obj * obj);

    void snk_targets_close(snk_targets_obj * obj);

    int snk_targets_process(snk_targets_obj * obj);

    void snk_targets_process_interface(snk_targets_obj * obj);

    void snk_targets_process_format(snk_targets_obj * obj);

    snk_targets_cfg * snk_targets_cfg_construct(void);

    void snk_targets_cfg_destroy(snk_targets_cfg * snk_targets_config);

#endif