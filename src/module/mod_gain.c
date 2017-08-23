    
    #include "mod_gain.h"

    mod_gain_obj * mod_gain_construct(const mod_gain_cfg * mod_gain_config, const msg_hops_cfg * msg_hops_config) {

        mod_gain_obj * obj;

        obj = (mod_gain_obj *) malloc(sizeof(mod_gain_obj));

        obj->hop2hop_gain = hop2hop_gain_construct_zero(msg_hops_config->hopSize, mod_gain_config->gain);

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

        return obj;

    }

    void mod_gain_destroy(mod_gain_obj * obj) {

        hop2hop_gain_destroy(obj->hop2hop_gain);
        free((void *) obj);

    }

    int mod_gain_process(mod_gain_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            hop2hop_gain_process(obj->hop2hop_gain, obj->in->hops, obj->out->hops);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_hops_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;        

    }

    void mod_gain_connect(mod_gain_obj * obj, msg_hops_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_gain_disconnect(mod_gain_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    mod_gain_cfg * mod_gain_cfg_construct(void) {

        mod_gain_cfg * cfg;

        cfg = (mod_gain_cfg *) malloc(sizeof(mod_gain_cfg));

        cfg->gain = 0.0f;

        return cfg;

    }

    void mod_gain_cfg_destroy(mod_gain_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_gain_cfg_printf(const mod_gain_cfg * cfg) {

    }