#ifndef __ODAS_SINK_HOPSTRACKS
#define __ODAS_SINK_HOPSTRACKS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include "../message/msg_hops.h"
    #include "../message/msg_tracks.h"
    #include "../utils/interleave.h"
    #include "../utils/pcm.h"

    typedef struct snk_hopstracks_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;

        unsigned int nBytes;
        unsigned int nSamples;
        unsigned int bufferSize;
        char * bufferInterleave;
        char * bufferPerChannel;
        float * buffer;   

        int server_id;
        int connection_id;
        unsigned int port;       

        msg_hops_obj * in1;
        msg_tracks_obj * in2;

    } snk_hopstracks_obj;

    typedef struct snk_hopstracks_cfg {

        unsigned int port;

    } snk_hopstracks_cfg;

    snk_hopstracks_obj * snk_hopstracks_construct(const snk_hopstracks_cfg * snk_hopstracks_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config);

    void snk_hopstracks_destroy(snk_hopstracks_obj * obj);

    void snk_hopstracks_connect(snk_hopstracks_obj * obj, msg_hops_obj * in1, msg_tracks_obj * in2);

    void snk_hopstracks_disconnect(snk_hopstracks_obj * obj);

    void snk_hopstracks_open(snk_hopstracks_obj * obj);

    void snk_hopstracks_close(snk_hopstracks_obj * obj);

    int snk_hopstracks_process(snk_hopstracks_obj * obj);

    void snk_hopstracks_process_interface(snk_hopstracks_obj * obj);

    void snk_hopstracks_process_format(snk_hopstracks_obj * obj);

    snk_hopstracks_cfg * snk_hopstracks_cfg_construct(void);

    void snk_hopstracks_cfg_destroy(snk_hopstracks_cfg * snk_hopstracks_config);

#endif