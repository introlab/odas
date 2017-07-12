#ifndef __ODAS_CONNECTOR_SPECTRA
#define __ODAS_CONNECTOR_SPECTRA

    #include "../message/msg_spectra.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_spectra_obj {

        msg_spectra_obj * in;
        msg_spectra_obj ** outs;

        unsigned int nOuts;

    } con_spectra_obj;

    con_spectra_obj * con_spectra_construct(const unsigned int nOuts, const msg_spectra_cfg * msg_spectra_config);

    void con_spectra_destroy(con_spectra_obj * obj);

    int con_spectra_process(con_spectra_obj * obj);

#endif