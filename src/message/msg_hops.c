
    #include "msg_hops.h"

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * msg_hops_config) {

        msg_hops_obj * obj;

        obj = (msg_hops_obj *) malloc(sizeof(msg_hops_obj));

        obj->timeStamp = 0;
        obj->fS = msg_hops_config->fS;
        obj->hops = hops_construct_zero(msg_hops_config->nChannels, msg_hops_config->hopSize);

        return obj;

    }

    void msg_hops_destroy(msg_hops_obj * obj) {

        hops_destroy(obj->hops);
        free((void *) obj);

    }

    void msg_hops_copy(msg_hops_obj * dest, const msg_hops_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        hops_copy(dest->hops, src->hops);

    }

    void msg_hops_zero(msg_hops_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        hops_zero(obj->hops);

    }

    unsigned int msg_hops_isZero(const msg_hops_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_hops_cfg * msg_hops_cfg_construct(void) {

        msg_hops_cfg * cfg;

        cfg = (msg_hops_cfg *) malloc(sizeof(msg_hops_cfg));

        cfg->hopSize = 0;
        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_hops_cfg_destroy(msg_hops_cfg * msg_hops_config) {

        free((void *) msg_hops_config);

    }

    void msg_hops_cfg_printf(const msg_hops_cfg * msg_hops_config) {
       
        printf("hopSize = %u\n", msg_hops_config->hopSize);
        printf("nChannels = %u\n", msg_hops_config->nChannels);        
        printf("fS = %u\n", msg_hops_config->fS);

    }
