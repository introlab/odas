#ifndef __ODAS_MESSAGE_SPECTRA
#define __ODAS_MESSAGE_SPECTRA

    #include <stdlib.h>

    #include "../signal/freq.h"

    typedef struct msg_spectra_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        freqs_obj * freqs;

    } msg_spectra_obj;

    typedef struct msg_spectra_cfg {

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_spectra_cfg;

    msg_spectra_obj * msg_spectra_construct(const msg_spectra_cfg * msg_spectra_config);

    void msg_spectra_destroy(msg_spectra_obj * obj);

    void msg_spectra_copy(msg_spectra_obj * dest, const msg_spectra_obj * src);

    void msg_spectra_zero(msg_spectra_obj * obj);

    unsigned int msg_spectra_isZero(const msg_spectra_obj * obj);

    msg_spectra_cfg * msg_spectra_cfg_construct(void);

    void msg_spectra_cfg_destroy(msg_spectra_cfg * msg_spectra_config);

    void msg_spectra_cfg_printf(const msg_spectra_cfg * msg_spectra_config);

#endif