#ifndef __ODAS_MESSAGE_XCORRS
#define __ODAS_MESSAGE_XCORRS

    #include <stdlib.h>

    #include "../signal/xcorr.h"

    typedef struct msg_xcorrs_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        xcorrs_obj * xcorrs;

    } msg_xcorrs_obj;

    typedef struct msg_xcorrs_cfg {

        unsigned int frameSize;
        unsigned int nPairs;
        unsigned int fS;

    } msg_xcorrs_cfg;

    msg_xcorrs_obj * msg_xcorrs_construct(const msg_xcorrs_cfg * msg_xcorrs_config);

    void msg_xcorrs_destroy(msg_xcorrs_obj * obj);

    void msg_xcorrs_copy(msg_xcorrs_obj * dest, const msg_xcorrs_obj * src);

    void msg_xcorrs_zero(msg_xcorrs_obj * obj);

    unsigned int msg_xcorrs_isZero(const msg_xcorrs_obj * obj);

    msg_xcorrs_cfg * msg_xcorrs_cfg_construct(void);

    void msg_xcorrs_cfg_destroy(msg_xcorrs_cfg * msg_xcorrs_config);

    void msg_xcorrs_cfg_printf(const msg_xcorrs_cfg * msg_xcorrs_config);

#endif