#ifndef __ODAS_AMODULE_SSS
#define __ODAS_AMODULE_SSS

    #include "../module/mod_sss.h"
    #include "../amessage/amsg_tracks.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_sss_obj {

        mod_sss_obj * mod_sss;
        amsg_spectra_obj * in1;
        amsg_tracks_obj * in2;
        amsg_spectra_obj * out;
        thread_obj * thread;    

    } amod_sss_obj;

    amod_sss_obj * amod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_spectra_cfg * msg_spectra_config, const msg_tracks_cfg * msg_tracks_config);

    void amod_sss_destroy(amod_sss_obj * obj);

    void amod_sss_connect(amod_sss_obj * obj, amsg_spectra_obj * in1, amsg_tracks_obj * in2, amsg_spectra_obj * out);

    void amod_sss_disconnect(amod_sss_obj * obj);

    void * amod_sss_thread(void * ptr);        

#endif