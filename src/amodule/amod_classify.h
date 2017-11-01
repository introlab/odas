#ifndef __ODAS_AMODULE_CLASSIFY
#define __ODAS_AMODULE_CLASSIFY

    #include "../module/mod_classify.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_tracks.h"
    #include "../amessage/amsg_categories.h"
    #include "../general/thread.h"

    typedef struct amod_classify_obj {

        mod_classify_obj * mod_classify;
        amsg_hops_obj * in1;
        amsg_tracks_obj * in2;
        amsg_categories_obj * out;
        thread_obj * thread;    

    } amod_classify_obj;

    amod_classify_obj * amod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config, const msg_categories_cfg * msg_categories_config);

    void amod_classify_destroy(amod_classify_obj * obj);

    void amod_classify_connect(amod_classify_obj * obj, amsg_hops_obj * in1, amsg_tracks_obj * in2, amsg_categories_obj * out);

    void amod_classify_disconnect(amod_classify_obj * obj);

    void * amod_classify_thread(void * ptr);    

#endif