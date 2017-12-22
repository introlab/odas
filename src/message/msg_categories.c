
    #include "msg_categories.h"

    msg_categories_obj * msg_categories_construct(const msg_categories_cfg * msg_categories_config) {

        msg_categories_obj * obj;

        obj = (msg_categories_obj *) malloc(sizeof(msg_categories_obj));

        obj->timeStamp = 0;
        obj->fS = msg_categories_config->fS;
        obj->categories = categories_construct_zero(msg_categories_config->nChannels);

        return obj;

    }

    void msg_categories_destroy(msg_categories_obj * obj) {

        categories_destroy(obj->categories);
        free((void *) obj);

    }

    void msg_categories_copy(msg_categories_obj * dest, const msg_categories_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;

        categories_copy(dest->categories, src->categories);

    }

    void msg_categories_zero(msg_categories_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        categories_zero(obj->categories);

    }

    unsigned int msg_categories_isZero(const msg_categories_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_categories_cfg * msg_categories_cfg_construct(void) {

        msg_categories_cfg * cfg;

        cfg = (msg_categories_cfg *) malloc(sizeof(msg_categories_cfg));

        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_categories_cfg_destroy(msg_categories_cfg * msg_categories_config) {

        free((void *) msg_categories_config);

    }

    void msg_categories_cfg_printf(const msg_categories_cfg * msg_categories_config) {

        printf("nChannels = %u\n", msg_categories_config->nChannels);        
        printf("fS = %u\n", msg_categories_config->fS);

    }
