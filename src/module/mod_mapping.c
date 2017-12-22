    
    #include "mod_mapping.h"

    mod_mapping_obj * mod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config) {

        mod_mapping_obj * obj;
        unsigned int iLink;

        obj = (mod_mapping_obj *) malloc(sizeof(mod_mapping_obj));

        obj->hop2hop_multiplex = hop2hop_multiplex_construct_zero(msg_hops_config->hopSize);
        obj->links = links_clone(mod_mapping_config->links);

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

        return obj;

    }

    void mod_mapping_destroy(mod_mapping_obj * obj) {

        links_destroy(obj->links);
        hop2hop_multiplex_destroy(obj->hop2hop_multiplex);
        free((void *) obj);

    }

    int mod_mapping_process(mod_mapping_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            hop2hop_multiplex_process(obj->hop2hop_multiplex, 
                                      obj->links, 
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

    void mod_mapping_connect(mod_mapping_obj * obj, msg_hops_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_mapping_disconnect(mod_mapping_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    mod_mapping_cfg * mod_mapping_cfg_construct(void) {

        mod_mapping_cfg * cfg;

        cfg = (mod_mapping_cfg *) malloc(sizeof(mod_mapping_cfg));

        cfg->links = (links_obj *) NULL;

        return cfg;

    }

    void mod_mapping_cfg_destroy(mod_mapping_cfg * cfg) {

        if (cfg->links != NULL) {
            links_destroy(cfg->links);
        }

        free((void *) cfg);

    }

    void mod_mapping_cfg_printf(const mod_mapping_cfg * cfg) {

        printf("links:"); links_printf(cfg->links);

    }