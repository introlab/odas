#ifndef __ODAS_AMESSAGE_SPECTRA
#define __ODAS_AMESSAGE_SPECTRA

    #include <stdlib.h>

    #include "../message/msg_spectra.h"
    #include "../utils/fifo.h"

    typedef struct amsg_spectra_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_spectra_obj;

    amsg_spectra_obj * amsg_spectra_construct(const unsigned int nMessages, const msg_spectra_cfg * msg_spectra_config);

    void amsg_spectra_destroy(amsg_spectra_obj * obj);

    msg_spectra_obj * amsg_spectra_filled_pop(amsg_spectra_obj * obj);

    void amsg_spectra_filled_push(amsg_spectra_obj * obj, msg_spectra_obj * msg_spectra);

    msg_spectra_obj * amsg_spectra_empty_pop(amsg_spectra_obj * obj);

    void amsg_spectra_empty_push(amsg_spectra_obj * obj, msg_spectra_obj * msg_spectra);

#endif