#ifndef __ODAS_ACONNECTOR_SPECTRA
#define __ODAS_ACONNECTOR_SPECTRA

    #include "../connector/con_spectra.h"
    #include "../amessage/amsg_spectra.h"
    #include "../message/msg_spectra.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_spectra_obj {

        amsg_spectra_obj * in;
        amsg_spectra_obj ** outs;
        con_spectra_obj * con_spectra;
        thread_obj * thread;

    } acon_spectra_obj;

    acon_spectra_obj * acon_spectra_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_spectra_cfg * msg_spectra_config);

    void acon_spectra_destroy(acon_spectra_obj * obj);

    void * acon_spectra_thread(void * ptr);

#endif