#ifndef __ODAS_ASINK_SPECTRA
#define __ODAS_ASINK_SPECTRA

    #include "../amessage/amsg_spectra.h"
    #include "../sink/snk_spectra.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_spectra_obj {

        snk_spectra_obj * snk_spectra;
        amsg_spectra_obj * in;
        thread_obj * thread;

    } asnk_spectra_obj;

    asnk_spectra_obj * asnk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config);

    void asnk_spectra_destroy(asnk_spectra_obj * obj);

    void asnk_spectra_connect(asnk_spectra_obj * obj, amsg_spectra_obj * in);

    void asnk_spectra_disconnect(asnk_spectra_obj * obj);

    void * asnk_spectra_thread(void * ptr);

#endif