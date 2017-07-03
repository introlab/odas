#ifndef __ODAS_MODULE_STFT
#define __ODAS_MODULE_STFT

    #include "../system/hop2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2freq.h"
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    typedef struct mod_stft_obj {

        hop2frame_obj * hop2frame;
        frames_obj * frames;
        frame2freq_obj * frame2freq;

        msg_hops_obj * in;
        msg_spectra_obj * out;        

    } mod_stft_obj;

    typedef struct mod_stft_cfg {
        
    } mod_stft_cfg;

    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_stft_destroy(mod_stft_obj * obj);

    int mod_stft_process(mod_stft_obj * obj);

    void mod_stft_connect(mod_stft_obj * obj, msg_hops_obj * in, msg_spectra_obj * out);

    void mod_stft_disconnect(mod_stft_obj * obj);

    mod_stft_cfg * mod_stft_cfg_construct(void);

    void mod_stft_cfg_destroy(mod_stft_cfg * cfg);

    void mod_stft_cfg_printf(const mod_stft_cfg * cfg);

#endif