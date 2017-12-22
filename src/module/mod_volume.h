#ifndef __ODAS_MODULE_VOLUME
#define __ODAS_MODULE_VOLUME

    #include "../system/hop2hop.h"
    #include "../message/msg_hops.h"

    typedef struct mod_volume_obj {

        hop2hop_gain_obj * hop2hop_gain;

        msg_hops_obj * in;
        msg_hops_obj * out;        

    } mod_volume_obj;

    typedef struct mod_volume_cfg {
        
        float gain;

    } mod_volume_cfg;

    mod_volume_obj * mod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config);

    void mod_volume_destroy(mod_volume_obj * obj);

    int mod_volume_process(mod_volume_obj * obj);

    void mod_volume_connect(mod_volume_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_volume_disconnect(mod_volume_obj * obj);

    mod_volume_cfg * mod_volume_cfg_construct(void);

    void mod_volume_cfg_destroy(mod_volume_cfg * cfg);

    void mod_volume_cfg_printf(const mod_volume_cfg * cfg);

#endif