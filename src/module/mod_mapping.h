#ifndef __ODAS_MODULE_MAPPING
#define __ODAS_MODULE_MAPPING

    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    #include "../general/link.h"
    #include "../system/hop2hop.h"

    typedef struct mod_mapping_obj {

        hop2hop_multiplex_obj * hop2hop_multiplex;
        links_obj * links;

        msg_hops_obj * in;
        msg_hops_obj * out;

    } mod_mapping_obj;

    typedef struct mod_mapping_cfg {
        
        links_obj * links;

    } mod_mapping_cfg;

    mod_mapping_obj * mod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config);

    void mod_mapping_destroy(mod_mapping_obj * obj);

    int mod_mapping_process(mod_mapping_obj * obj);

    void mod_mapping_connect(mod_mapping_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_mapping_disconnect(mod_mapping_obj * obj);

    mod_mapping_cfg * mod_mapping_cfg_construct(void);

    void mod_mapping_cfg_destroy(mod_mapping_cfg * cfg);

    void mod_mapping_cfg_printf(const mod_mapping_cfg * cfg);

#endif