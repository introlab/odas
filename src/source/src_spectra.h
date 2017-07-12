#ifndef __ODAS_SOURCE_SPECTRA
#define __ODAS_SOURCE_SPECTRA

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../general/thread.h"
    #include "../message/msg_spectra.h"
    #include "../signal/freq.h"
    #include "../utils/pcm.h"

    typedef struct src_spectra_obj {

        unsigned long long timeStamp;

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;

        float * buffer;

        msg_spectra_obj * out;

    } src_spectra_obj;

    typedef struct src_spectra_cfg {

        unsigned int fS;
        format_obj * format;
        interface_obj * interface;

    } src_spectra_cfg;

    src_spectra_obj * src_spectra_construct(const src_spectra_cfg * src_spectra_config, const msg_spectra_cfg * msg_spectra_config);

    void src_spectra_destroy(src_spectra_obj * obj);

    void src_spectra_connect(src_spectra_obj * obj, msg_spectra_obj * out);

    void src_spectra_disconnect(src_spectra_obj * obj);

    void src_spectra_open(src_spectra_obj * obj);

    void src_spectra_open_file(src_spectra_obj * obj);

    void src_spectra_close(src_spectra_obj * obj);

    void src_spectra_close_file(src_spectra_obj * obj);

    int src_spectra_process(src_spectra_obj * obj);

    int src_spectra_process_file(src_spectra_obj * obj);

    src_spectra_cfg * src_spectra_cfg_construct(void);

    void src_spectra_cfg_destroy(src_spectra_cfg * src_spectra_config);

#endif