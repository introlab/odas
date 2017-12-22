    
    #include "inj_targets.h"

    inj_targets_obj * inj_targets_construct(const inj_targets_cfg * inj_targets_config, const msg_hops_cfg * msg_hops_config, const msg_targets_cfg * msg_targets_config) {

        inj_targets_obj * obj;

        obj = (inj_targets_obj *) malloc(sizeof(inj_targets_obj));

        obj->nTargets = msg_targets_config->nTargets;
        obj->fS = msg_hops_config->fS;

        obj->timeStamp = 0;

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_targets_obj *) NULL;

        obj->targets = targets_clone(inj_targets_config->targets);

        return obj;

    }

    void inj_targets_destroy(inj_targets_obj * obj) {

        targets_destroy(obj->targets);
        free((void *) obj);

    }

    void inj_targets_connect(inj_targets_obj * obj, msg_hops_obj * in, msg_targets_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void inj_targets_disconnect(inj_targets_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_targets_obj *) NULL;

    }
    
    int inj_targets_process(inj_targets_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            targets_copy(obj->out->targets, obj->targets);
            obj->out->fS = obj->in->fS;
            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_targets_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;        

    }

    inj_targets_cfg * inj_targets_cfg_construct(void) {

        inj_targets_cfg * cfg;

        cfg = (inj_targets_cfg *) malloc(sizeof(inj_targets_cfg));

        cfg->nTargets = 0;
        cfg->targets = NULL;

        return cfg;

    }

    void inj_targets_cfg_destroy(inj_targets_cfg * cfg) {

        if (cfg->targets != NULL) {
            targets_destroy(cfg->targets);
        }

        free((void *) cfg);

    }

    void inj_targets_cfg_printf(const inj_targets_cfg * cfg) {

        printf("nTargets = %u\n", cfg->nTargets);        
        
        if (cfg->targets != NULL) {
            
            targets_printf(cfg->targets);

        }
        else {

            printf("targets: NULL\n");

        }

        

    }