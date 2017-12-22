    
    #include "mod_volume.h"

    mod_volume_obj * mod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config) {

        mod_volume_obj * obj;

        obj = (mod_volume_obj *) malloc(sizeof(mod_volume_obj));

        obj->hop2hop_gain = hop2hop_gain_construct_zero(msg_hops_config->hopSize, mod_volume_config->gain);

        return obj;

    }

    void mod_volume_destroy(mod_volume_obj * obj) {

        hop2hop_gain_destroy(obj->hop2hop_gain);

    }

    int mod_volume_process(mod_volume_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            hop2hop_gain_process(obj->hop2hop_gain, 
                                 obj->in->hops, 
                                 obj->out->hops);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_hops_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;       

    }

    void mod_volume_connect(mod_volume_obj * obj, msg_hops_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_volume_disconnect(mod_volume_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    mod_volume_cfg * mod_volume_cfg_construct(void) {

        mod_volume_cfg * cfg;

        cfg = (mod_volume_cfg *) malloc(sizeof(mod_volume_cfg));

        return cfg;

    }

    void mod_volume_cfg_destroy(mod_volume_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_volume_cfg_printf(const mod_volume_cfg * cfg) {

    }