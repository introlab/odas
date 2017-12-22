#ifndef __ODAS_SINK_SPECTRA
#define __ODAS_SINK_SPECTRA

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_spectra.h"

    typedef struct snk_spectra_obj {

        unsigned long long timeStamp;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        msg_spectra_obj * in;

    } snk_spectra_obj;

    typedef struct snk_spectra_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } snk_spectra_cfg;

    snk_spectra_obj * snk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config);

    void snk_spectra_destroy(snk_spectra_obj * obj);

    void snk_spectra_connect(snk_spectra_obj * obj, msg_spectra_obj * in);

    void snk_spectra_disconnect(snk_spectra_obj * obj);

    void snk_spectra_open(snk_spectra_obj * obj);

    void snk_spectra_open_interface_blackhole(snk_spectra_obj * obj);

    void snk_spectra_close(snk_spectra_obj * obj);

    void snk_spectra_close_interface_blackhole(snk_spectra_obj * obj);

    int snk_spectra_process(snk_spectra_obj * obj);

    void snk_spectra_process_interface_blackhole(snk_spectra_obj * obj);

    void snk_spectra_process_format_undefined(snk_spectra_obj * obj);

    snk_spectra_cfg * snk_spectra_cfg_construct(void);

    void snk_spectra_cfg_destroy(snk_spectra_cfg * snk_spectra_config);

#endif