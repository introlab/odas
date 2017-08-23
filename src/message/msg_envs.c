    
    #include "msg_envs.h"

    msg_envs_obj * msg_envs_construct(const msg_envs_cfg * msg_envs_config) {

        msg_envs_obj * obj;

        obj = (msg_envs_obj *) malloc(sizeof(msg_envs_obj));

        obj->timeStamp = 0;
        obj->fS = msg_envs_config->fS;
        obj->envs = envs_construct_zero(msg_envs_config->nChannels, msg_envs_config->halfFrameSize);

        return obj;

    }

    void msg_envs_destroy(msg_envs_obj * obj) {

        free((void *) obj->envs);
        free((void *) obj);

    }

    void msg_envs_copy(msg_envs_obj * dest, const msg_envs_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        envs_copy(dest->envs, src->envs);

    }

    void msg_envs_zero(msg_envs_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        envs_zero(obj->envs);

    }

    unsigned int msg_envs_isZero(const msg_envs_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_envs_cfg * msg_envs_cfg_construct(void) {

        msg_envs_cfg * cfg;

        cfg = (msg_envs_cfg *) malloc(sizeof(msg_envs_cfg));

        cfg->halfFrameSize = 0;
        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_envs_cfg_destroy(msg_envs_cfg * msg_envs_config) {

        free((void *) msg_envs_config);

    }

    void msg_envs_cfg_printf(const msg_envs_cfg * msg_envs_config) {

        if (msg_envs_config != NULL) {

            printf("halfFrameSize = %u\n", msg_envs_config->halfFrameSize);
            printf("nChannels = %u\n", msg_envs_config->nChannels);
            printf("fS = %u\n", msg_envs_config->fS);

        }
        else {

            printf("(null)\n");

        }       

    }