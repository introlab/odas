#ifndef __ODAS_MODULE_ISTFT
#define __ODAS_MODULE_ISTFT

    #include "../system/freq2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2hop.h"
        
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    typedef struct mod_istft_obj {

        freq2frame_obj * freq2frame;
        frames_obj * frames;
        frame2hop_obj * frame2hop;

        msg_spectra_obj * in;        
        msg_hops_obj * out;

    } mod_istft_obj;

    typedef struct mod_istft_cfg {
        
    } mod_istft_cfg;

    mod_istft_obj * mod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config);

    void mod_istft_destroy(mod_istft_obj * obj);

    int mod_istft_process(mod_istft_obj * obj);

    void mod_istft_connect(mod_istft_obj * obj, msg_spectra_obj * in, msg_hops_obj * out);

    void mod_istft_disconnect(mod_istft_obj * obj);

    mod_istft_cfg * mod_istft_cfg_construct(void);

    void mod_istft_cfg_destroy(mod_istft_cfg * cfg);

    void mod_istft_cfg_printf(const mod_istft_cfg * cfg);

#endif