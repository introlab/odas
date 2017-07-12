    
    #include "msg_xcorrs.h"

    msg_xcorrs_obj * msg_xcorrs_construct(const msg_xcorrs_cfg * msg_xcorrs_config) {

        msg_xcorrs_obj * obj;

        obj = (msg_xcorrs_obj *) malloc(sizeof(msg_xcorrs_obj));

        obj->timeStamp = 0;
        obj->fS = 0;
        obj->xcorrs = xcorrs_construct_zero(msg_xcorrs_config->nPairs, msg_xcorrs_config->frameSize);

        return obj;

    }

    void msg_xcorrs_destroy(msg_xcorrs_obj * obj) {

        xcorrs_destroy(obj->xcorrs);
        free((void *) obj);

    }

    void msg_xcorrs_copy(msg_xcorrs_obj * dest, const msg_xcorrs_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        xcorrs_copy(dest->xcorrs, src->xcorrs);

    }

    void msg_xcorrs_zero(msg_xcorrs_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        xcorrs_zero(obj->xcorrs);

    }

    unsigned int msg_xcorrs_isZero(const msg_xcorrs_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_xcorrs_cfg * msg_xcorrs_cfg_construct(void) {

        msg_xcorrs_cfg * cfg;

        cfg = (msg_xcorrs_cfg *) malloc(sizeof(msg_xcorrs_cfg));

        cfg->frameSize = 0;
        cfg->nPairs = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_xcorrs_cfg_destroy(msg_xcorrs_cfg * msg_xcorrs_config) {

        free((void *) msg_xcorrs_config);

    }

    void msg_xcorrs_cfg_printf(const msg_xcorrs_cfg * msg_xcorrs_config) {

        if (msg_xcorrs_config != NULL) {

            printf("frameSize = %u\n", msg_xcorrs_config->frameSize);
            printf("nPairs = %u\n", msg_xcorrs_config->nPairs);
            printf("fS = %u\n", msg_xcorrs_config->fS);

        }
        else {

            printf("(null)\n");

        }       

    }