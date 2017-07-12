#ifndef __ODAS_ASOURCE_SPECTRA
#define __ODAS_ASOURCE_SPECTRA

    #include "../amessage/amsg_spectra.h"
    #include "../source/src_spectra.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asrc_spectra_obj {

        src_spectra_obj * src_spectra;
        amsg_spectra_obj * out;
        thread_obj * thread;

    } asrc_spectra_obj;

    asrc_spectra_obj * asrc_spectra_construct(const src_spectra_cfg * src_spectra_config, const msg_spectra_cfg * msg_spectra_config);

    void asrc_spectra_destroy(asrc_spectra_obj * obj);

    void asrc_spectra_connect(asrc_spectra_obj * obj, amsg_spectra_obj * out);

    void asrc_spectra_disconnect(asrc_spectra_obj * obj);

    void * asrc_spectra_thread(void * ptr);

#endif