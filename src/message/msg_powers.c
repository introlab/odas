    
    #include "msg_powers.h"

    msg_powers_obj * msg_powers_construct(const msg_powers_cfg * msg_powers_config) {

        msg_powers_obj * obj;

        obj = (msg_powers_obj *) malloc(sizeof(msg_powers_obj));

        obj->timeStamp = 0;
        obj->fS = msg_powers_config->fS;
        obj->envs = envs_construct_zero(msg_powers_config->nChannels, msg_powers_config->halfFrameSize);

        return obj;

    }

    void msg_powers_destroy(msg_powers_obj * obj) {

        envs_destroy(obj->envs);
        free((void *) obj);

    }

    void msg_powers_copy(msg_powers_obj * dest, const msg_powers_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        envs_copy(dest->envs, src->envs);

    }

    void msg_powers_zero(msg_powers_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        envs_zero(obj->envs);

    }

    unsigned int msg_powers_isZero(const msg_powers_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;        

    }

    msg_powers_cfg * msg_powers_cfg_construct(void) {

        msg_powers_cfg * cfg;

        cfg = (msg_powers_cfg *) malloc(sizeof(msg_powers_cfg));

        cfg->halfFrameSize = 0;
        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_powers_cfg_destroy(msg_powers_cfg * msg_powers_config) {

        free((void *) msg_powers_config);

    }

    void msg_powers_cfg_printf(const msg_powers_cfg * msg_powers_config) {

        if (msg_powers_config != NULL) {

            printf("halfFrameSize = %u\n", msg_powers_config->halfFrameSize);
            printf("nChannels = %u\n", msg_powers_config->nChannels);
            printf("fS = %u\n", msg_powers_config->fS);

        }
        else {

            printf("(null)\n");

        }    

    }