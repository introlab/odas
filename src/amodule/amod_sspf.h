#ifndef __ODAS_AMODULE_SSPF
#define __ODAS_AMODULE_SSPF

    #include "../module/mod_sspf.h"
    #include "../amessage/amsg_envs.h"
    #include "../amessage/amsg_tracks.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_sspf_obj {

        mod_sspf_obj * mod_sspf;
        amsg_spectra_obj * in1;
        amsg_envs_obj * in2;
        amsg_tracks_obj * in3;
        amsg_spectra_obj * out;
        thread_obj * thread;    

    } amod_sspf_obj;

    amod_sspf_obj * amod_sspf_construct(const mod_sspf_cfg * mod_sspf_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config, const msg_envs_cfg * msg_envs_config);

    void amod_sspf_destroy(amod_sspf_obj * obj);

    void amod_sspf_connect(amod_sspf_obj * obj, amsg_spectra_obj * in1, amsg_envs_obj * in2, amsg_tracks_obj * in3, amsg_spectra_obj * out);

    void amod_sspf_disconnect(amod_sspf_obj * obj);

    void * amod_sspf_thread(void * ptr);        

#endif