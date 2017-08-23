#ifndef __ODAS_MODULE_GAIN
#define __ODAS_MODULE_GAIN

    #include "../system/hop2hop.h"
    #include "../message/msg_hops.h"

    typedef struct mod_gain_obj {

        hop2hop_gain_obj * hop2hop_gain;

        msg_hops_obj * in;
        msg_hops_obj * out;        

    } mod_gain_obj;

    typedef struct mod_gain_cfg {
        
        float gain;

    } mod_gain_cfg;

    mod_gain_obj * mod_gain_construct(const mod_gain_cfg * mod_gain_config, const msg_hops_cfg * msg_hops_config);

    void mod_gain_destroy(mod_gain_obj * obj);

    int mod_gain_process(mod_gain_obj * obj);

    void mod_gain_connect(mod_gain_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_gain_disconnect(mod_gain_obj * obj);

    mod_gain_cfg * mod_gain_cfg_construct(void);

    void mod_gain_cfg_destroy(mod_gain_cfg * cfg);

    void mod_gain_cfg_printf(const mod_gain_cfg * cfg);

#endif