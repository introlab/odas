#ifndef __ODAS_DEMO_CORE_OBJECTS
#define __ODAS_DEMO_CORE_OBJECTS

    #include <odas/odas.h>
    #include <stdlib.h>

    #include "configs.h"

    typedef struct objects {

        asrc_hops_obj * asrc_hops;
        acon_hops_obj * acon_hops;
        asnk_hops_obj * asnk_hops;

        asrc_targets_obj * asrc_targets;
        acon_targets_obj * acon_targets;
        asnk_targets_obj * asnk_targets;

        amod_stft_obj * amod_stft;
        acon_spectra_obj * acon_spectra;

        amod_ssl_obj * amod_ssl;
        acon_pots_obj * acon_pots;
        asnk_pots_obj * asnk_pots;

        amod_sst_obj * amod_sst;
        acon_tracks_obj * acon_tracks;
        asnk_tracks_obj * asnk_tracks;

        amod_lag_obj * amod_lag;
        acon_spectra_obj * acon_spectra_delay;
        amod_noise_obj * amod_noise_delay;
        acon_powers_obj * acon_powers_delay;

        amod_sss_obj * amod_sss;

        acon_spectra_obj * acon_spectra_sep;
        amod_istft_obj * amod_istft_sep;
        acon_hops_obj * acon_hops_sep;
        asnk_hops_obj * asnk_hops_sep;
        asnk_hopstracks_obj * asnk_hopstracks_sep;

        acon_spectra_obj * acon_spectra_pf;
        amod_istft_obj * amod_istft_pf;
        acon_hops_obj * acon_hops_pf;
        asnk_hops_obj * asnk_hops_pf;
        asnk_hopstracks_obj * asnk_hopstracks_pf;

    } objects;

    objects * objects_construct(const configs * cfgs, const unsigned int nMessages);

    void objects_init_ssl(objects * objs, const configs * cfgs, const unsigned int nMessages);

    void objects_init_sslsst(objects * objs, const configs * cfgs, const unsigned int nMessages);

    void objects_init_sslsstsss(objects * objs, const configs * cfgs, const unsigned int nMessages);

    void objects_destroy(objects * objs);

    void objects_process(objects * objs);

#endif