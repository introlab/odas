
	#include "objects.h"

    objects * objects_construct(const configs * cfgs, const unsigned int nMessages) {

        objects * objs;

        char src_raw = 0;
        char src_targets = 0;
        char snk_raw = 0;
        char snk_pots = 0;
        char snk_tracks = 0;
        char snk_sep = 0;
        char snk_pf = 0;

        objs = (objects *) malloc(sizeof(objects));

        objs->asrc_hops = (asrc_hops_obj *) NULL;
        objs->acon_hops = (acon_hops_obj *) NULL;
        objs->asnk_hops = (asnk_hops_obj *) NULL;

        objs->asrc_targets = (asrc_targets_obj *) NULL;
        objs->acon_targets = (acon_targets_obj *) NULL;
        objs->asnk_targets = (asnk_targets_obj *) NULL;

        objs->amod_stft = (amod_stft_obj *) NULL;
        objs->acon_spectra = (acon_spectra_obj *) NULL;

        objs->amod_ssl = (amod_ssl_obj *) NULL;
        objs->acon_pots = (acon_pots_obj *) NULL;
        objs->asnk_pots = (asnk_pots_obj *) NULL;

        objs->amod_sst = (amod_sst_obj *) NULL;
        objs->acon_tracks = (acon_tracks_obj *) NULL;
        objs->asnk_tracks = (asnk_tracks_obj *) NULL;

        objs->amod_lag = (amod_lag_obj *) NULL;
        objs->acon_spectra_delay = (acon_spectra_obj *) NULL;
        objs->amod_noise_delay = (amod_noise_obj *) NULL;
        objs->acon_powers_delay = (acon_powers_obj *) NULL;

        objs->amod_sss = (amod_sss_obj *) NULL;
        
        objs->acon_spectra_sep = (acon_spectra_obj *) NULL;
        objs->amod_istft_sep = (amod_istft_obj *) NULL;
        objs->acon_hops_sep = (acon_hops_obj *) NULL;
        objs->asnk_hops_sep = (asnk_hops_obj *) NULL;
        
        objs->acon_spectra_pf = (acon_spectra_obj *) NULL;
        objs->amod_istft_pf = (amod_istft_obj *) NULL;
        objs->acon_hops_pf = (acon_hops_obj *) NULL;
        objs->asnk_hops_pf = (asnk_hops_obj *) NULL;

        if (cfgs->src_hops_config->port != 0) { src_raw = 1; }
        if (cfgs->src_targets_config->port != 0) { src_targets = 1; }
        if (cfgs->snk_pots_config->port != 0) { snk_pots = 1; }
        if (cfgs->snk_tracks_config->port != 0) { snk_tracks = 1; }
        if (cfgs->snk_hops_sep_config->port != 0) { snk_sep = 1; }
        if (cfgs->snk_hops_pf_config->port != 0) { snk_pf = 1; }

        if (src_raw == 0) {

            printf("Need to provide an input for the raw signals\n");
            exit(EXIT_FAILURE);

        }

        if ((snk_sep == 1) || (snk_pf == 1)) { 

            objects_init_sslsstsss(objs, cfgs, nMessages);

        }
        else if (snk_tracks == 1) {

            objects_init_sslsst(objs, cfgs, nMessages);

        }
        else if (snk_pots == 1) {

            objects_init_ssl(objs, cfgs, nMessages);

        }

        return objs;        

    }

    void objects_init_ssl(objects * objs, const configs * cfgs, const unsigned int nMessages) {

        objs->asrc_hops = asrc_hops_construct(cfgs->src_hops_config, cfgs->msg_hops_config);
        objs->acon_hops = acon_hops_construct(nMessages, 3, cfgs->msg_hops_config);      
        objs->asnk_hops = asnk_hops_construct(cfgs->snk_hops_config, cfgs->msg_hops_config);

        objs->asrc_targets = asrc_targets_construct(cfgs->src_targets_config, cfgs->msg_targets_config);
        objs->acon_targets = acon_targets_construct(nMessages, 1, cfgs->msg_targets_config);
        objs->asnk_targets = asnk_targets_construct(cfgs->snk_targets_config, cfgs->msg_targets_config);

        objs->amod_stft = amod_stft_construct(cfgs->mod_stft_config, cfgs->msg_hops_config, cfgs->msg_spectra_config);
        objs->acon_spectra = acon_spectra_construct(nMessages, 1, cfgs->msg_spectra_config);

        objs->amod_ssl = amod_ssl_construct(cfgs->mod_ssl_config, cfgs->msg_spectra_config, cfgs->msg_pots_config);
        objs->acon_pots = acon_pots_construct(nMessages, 1, cfgs->msg_pots_config);
        objs->asnk_pots = asnk_pots_construct(cfgs->snk_pots_config, cfgs->msg_pots_config);

        asrc_hops_connect(objs->asrc_hops, objs->acon_hops->in);
        asnk_hops_connect(objs->asnk_hops, objs->acon_hops->outs[0]);

        asrc_targets_connect(objs->asrc_targets, objs->acon_hops->outs[1], objs->acon_targets->in);
        asnk_targets_connect(objs->asnk_targets, objs->acon_targets->outs[0]);

        amod_stft_connect(objs->amod_stft, objs->acon_hops->outs[2], objs->acon_spectra->in);

        amod_ssl_connect(objs->amod_ssl, objs->acon_spectra->outs[0], objs->acon_pots->in);
        asnk_pots_connect(objs->asnk_pots, objs->acon_pots->outs[0]);

    }

    void objects_init_sslsst(objects * objs, const configs * cfgs, const unsigned int nMessages) {

        objs->asrc_hops = asrc_hops_construct(cfgs->src_hops_config, cfgs->msg_hops_config);
        objs->acon_hops = acon_hops_construct(nMessages, 3, cfgs->msg_hops_config);      
        objs->asnk_hops = asnk_hops_construct(cfgs->snk_hops_config, cfgs->msg_hops_config);

        objs->asrc_targets = asrc_targets_construct(cfgs->src_targets_config, cfgs->msg_targets_config);
        objs->acon_targets = acon_targets_construct(nMessages, 2, cfgs->msg_targets_config);
        objs->asnk_targets = asnk_targets_construct(cfgs->snk_targets_config, cfgs->msg_targets_config);
        
        objs->amod_stft = amod_stft_construct(cfgs->mod_stft_config, cfgs->msg_hops_config, cfgs->msg_spectra_config);
        objs->acon_spectra = acon_spectra_construct(nMessages, 1, cfgs->msg_spectra_config);

        objs->amod_ssl = amod_ssl_construct(cfgs->mod_ssl_config, cfgs->msg_spectra_config, cfgs->msg_pots_config);
        objs->acon_pots = acon_pots_construct(nMessages, 2, cfgs->msg_pots_config);
        objs->asnk_pots = asnk_pots_construct(cfgs->snk_pots_config, cfgs->msg_pots_config);
        
        objs->amod_sst = amod_sst_construct(cfgs->mod_sst_config, cfgs->mod_ssl_config, cfgs->msg_pots_config, cfgs->msg_targets_config, cfgs->msg_tracks_config);
        objs->acon_tracks = acon_tracks_construct(nMessages, 1, cfgs->msg_tracks_config);
        objs->asnk_tracks = asnk_tracks_construct(cfgs->snk_tracks_config, cfgs->msg_tracks_config);

        asrc_hops_connect(objs->asrc_hops, objs->acon_hops->in);
        asnk_hops_connect(objs->asnk_hops, objs->acon_hops->outs[0]);

        asrc_targets_connect(objs->asrc_targets, objs->acon_hops->outs[1], objs->acon_targets->in);
        asnk_targets_connect(objs->asnk_targets, objs->acon_targets->outs[0]);

        amod_stft_connect(objs->amod_stft, objs->acon_hops->outs[2], objs->acon_spectra->in);

        amod_ssl_connect(objs->amod_ssl, objs->acon_spectra->outs[0], objs->acon_pots->in);
        asnk_pots_connect(objs->asnk_pots, objs->acon_pots->outs[0]);
        
        amod_sst_connect(objs->amod_sst, objs->acon_pots->outs[1], objs->acon_targets->outs[1], objs->acon_tracks->in);
        asnk_tracks_connect(objs->asnk_tracks, objs->acon_tracks->outs[0]);

    }

    void objects_init_sslsstsss(objects * objs, const configs * cfgs, const unsigned int nMessages) {

        objs->asrc_hops = asrc_hops_construct(cfgs->src_hops_config, cfgs->msg_hops_config);
        objs->acon_hops = acon_hops_construct(nMessages, 3, cfgs->msg_hops_config);      
        objs->asnk_hops = asnk_hops_construct(cfgs->snk_hops_config, cfgs->msg_hops_config);

        objs->asrc_targets = asrc_targets_construct(cfgs->src_targets_config, cfgs->msg_targets_config);
        objs->acon_targets = acon_targets_construct(nMessages, 2, cfgs->msg_targets_config);
        objs->asnk_targets = asnk_targets_construct(cfgs->snk_targets_config, cfgs->msg_targets_config);
        
        objs->amod_stft = amod_stft_construct(cfgs->mod_stft_config, cfgs->msg_hops_config, cfgs->msg_spectra_config);
        objs->acon_spectra = acon_spectra_construct(nMessages, 2, cfgs->msg_spectra_config);

        objs->amod_ssl = amod_ssl_construct(cfgs->mod_ssl_config, cfgs->msg_spectra_config, cfgs->msg_pots_config);
        objs->acon_pots = acon_pots_construct(nMessages, 2, cfgs->msg_pots_config);
        objs->asnk_pots = asnk_pots_construct(cfgs->snk_pots_config, cfgs->msg_pots_config);

        objs->amod_sst = amod_sst_construct(cfgs->mod_sst_config, cfgs->mod_ssl_config, cfgs->msg_pots_config, cfgs->msg_targets_config, cfgs->msg_tracks_config);
        objs->acon_tracks = acon_tracks_construct(nMessages, 2, cfgs->msg_tracks_config);
        objs->asnk_tracks = asnk_tracks_construct(cfgs->snk_tracks_config, cfgs->msg_tracks_config);

        objs->amod_lag = amod_lag_construct(cfgs->mod_lag_config, cfgs->msg_spectra_config);
        objs->acon_spectra_delay = acon_spectra_construct(nMessages, 2, cfgs->msg_spectra_delay_config);
        objs->amod_noise_delay = amod_noise_construct(cfgs->mod_noise_delay_config, cfgs->msg_spectra_delay_config, cfgs->msg_powers_delay_config);
        objs->acon_powers_delay = acon_powers_construct(nMessages, 1, cfgs->msg_powers_delay_config);

        objs->amod_sss = amod_sss_construct(cfgs->mod_sss_config, cfgs->msg_tracks_config, cfgs->msg_spectra_delay_config, cfgs->msg_powers_delay_config);

        objs->acon_spectra_sep = acon_spectra_construct(nMessages, 1, cfgs->msg_spectra_sep_config);
        objs->amod_istft_sep = amod_istft_construct(cfgs->mod_istft_sep_config, cfgs->msg_spectra_sep_config, cfgs->msg_hops_sep_config);
        objs->acon_hops_sep = acon_hops_construct(nMessages, 1, cfgs->msg_hops_sep_config);
        objs->asnk_hops_sep = asnk_hops_construct(cfgs->snk_hops_sep_config, cfgs->msg_hops_sep_config);

        objs->acon_spectra_pf = acon_spectra_construct(nMessages, 1, cfgs->msg_spectra_pf_config);
        objs->amod_istft_pf = amod_istft_construct(cfgs->mod_istft_pf_config, cfgs->msg_spectra_pf_config, cfgs->msg_hops_pf_config);
        objs->acon_hops_pf = acon_hops_construct(nMessages, 1, cfgs->msg_hops_pf_config);
        objs->asnk_hops_pf = asnk_hops_construct(cfgs->snk_hops_pf_config, cfgs->msg_hops_pf_config);

        asrc_hops_connect(objs->asrc_hops, objs->acon_hops->in);
        asnk_hops_connect(objs->asnk_hops, objs->acon_hops->outs[0]);

        asrc_targets_connect(objs->asrc_targets, objs->acon_hops->outs[1], objs->acon_targets->in);
        asnk_targets_connect(objs->asnk_targets, objs->acon_targets->outs[0]);

        amod_stft_connect(objs->amod_stft, objs->acon_hops->outs[2], objs->acon_spectra->in);

        amod_ssl_connect(objs->amod_ssl, objs->acon_spectra->outs[0], objs->acon_pots->in);
        asnk_pots_connect(objs->asnk_pots, objs->acon_pots->outs[0]);

        amod_sst_connect(objs->amod_sst, objs->acon_pots->outs[1], objs->acon_targets->outs[1], objs->acon_tracks->in);
        asnk_tracks_connect(objs->asnk_tracks, objs->acon_tracks->outs[0]);

        amod_lag_connect(objs->amod_lag, objs->acon_spectra->outs[1], objs->acon_spectra_delay->in);
        amod_noise_connect(objs->amod_noise_delay, objs->acon_spectra_delay->outs[0], objs->acon_powers_delay->in);

        amod_sss_connect(objs->amod_sss, objs->acon_spectra_delay->outs[1], objs->acon_powers_delay->outs[0], objs->acon_tracks->outs[1], objs->acon_spectra_sep->in, objs->acon_spectra_pf->in);
        
        amod_istft_connect(objs->amod_istft_sep, objs->acon_spectra_sep->outs[0], objs->acon_hops_sep->in);
        asnk_hops_connect(objs->asnk_hops_sep, objs->acon_hops_sep->outs[0]);

        amod_istft_connect(objs->amod_istft_pf, objs->acon_spectra_pf->outs[0], objs->acon_hops_pf->in);
        asnk_hops_connect(objs->asnk_hops_pf, objs->acon_hops_pf->outs[0]);

    }

    void objects_destroy(objects * objs) {

        if (objs->asrc_hops != NULL) { asrc_hops_destroy(objs->asrc_hops); }
        if (objs->acon_hops != NULL) { acon_hops_destroy(objs->acon_hops); }
        if (objs->asnk_hops != NULL) { asnk_hops_destroy(objs->asnk_hops); }

        if (objs->asrc_targets != NULL) { asrc_targets_destroy(objs->asrc_targets); }
        if (objs->acon_targets != NULL) { acon_targets_destroy(objs->acon_targets); }
        if (objs->asnk_targets != NULL) { asnk_targets_destroy(objs->asnk_targets); }

        if (objs->amod_stft != NULL) { amod_stft_destroy(objs->amod_stft); }
        if (objs->acon_spectra != NULL) { acon_spectra_destroy(objs->acon_spectra); }

        if (objs->amod_ssl != NULL) { amod_ssl_destroy(objs->amod_ssl); }
        if (objs->acon_pots != NULL) { acon_pots_destroy(objs->acon_pots); }
        if (objs->asnk_pots != NULL) { asnk_pots_destroy(objs->asnk_pots); }

        if (objs->amod_sst != NULL) { amod_sst_destroy(objs->amod_sst); } 
        if (objs->acon_tracks != NULL) { acon_tracks_destroy(objs->acon_tracks); }
        if (objs->asnk_tracks != NULL) { asnk_tracks_destroy(objs->asnk_tracks); }

        if (objs->amod_lag != NULL) { amod_lag_destroy(objs->amod_lag); }
        if (objs->acon_spectra_delay != NULL) { acon_spectra_destroy(objs->acon_spectra_delay); }
        if (objs->amod_noise_delay != NULL) { amod_noise_destroy(objs->amod_noise_delay); }
        if (objs->acon_powers_delay != NULL) { acon_powers_destroy(objs->acon_powers_delay); }

        if (objs->amod_sss != NULL) { amod_sss_destroy(objs->amod_sss); }

        if (objs->acon_spectra_sep != NULL) { acon_spectra_destroy(objs->acon_spectra_sep); }
        if (objs->amod_istft_sep != NULL) { amod_istft_destroy(objs->amod_istft_sep); }
        if (objs->acon_hops_sep != NULL) { acon_hops_destroy(objs->acon_hops_sep); }
        if (objs->asnk_hops_sep != NULL) { asnk_hops_destroy(objs->asnk_hops_sep); }
        
        if (objs->acon_spectra_pf != NULL) { acon_spectra_destroy(objs->acon_spectra_pf); }
        if (objs->amod_istft_pf != NULL) { amod_istft_destroy(objs->amod_istft_pf); }
        if (objs->acon_hops_pf != NULL) { acon_hops_destroy(objs->acon_hops_pf); }
        if (objs->asnk_hops_pf != NULL) { asnk_hops_destroy(objs->asnk_hops_pf); }

        free((void *) objs);

    }

    void objects_process(objects * objs) {

        // Start threads

        if (objs->asrc_hops != NULL) { thread_start(objs->asrc_hops->thread); }
        if (objs->acon_hops != NULL) { thread_start(objs->acon_hops->thread); }
        if (objs->asnk_hops != NULL) { thread_start(objs->asnk_hops->thread); }

        if (objs->asrc_targets != NULL) { thread_start(objs->asrc_targets->thread); }
        if (objs->acon_targets != NULL) { thread_start(objs->acon_targets->thread); }
        if (objs->asnk_targets != NULL) { thread_start(objs->asnk_targets->thread); }        

        if (objs->amod_stft != NULL) { thread_start(objs->amod_stft->thread); }
        if (objs->acon_spectra != NULL) { thread_start(objs->acon_spectra->thread); }

        if (objs->amod_ssl != NULL) { thread_start(objs->amod_ssl->thread); }
        if (objs->acon_pots != NULL) { thread_start(objs->acon_pots->thread); }
        if (objs->asnk_pots != NULL) { thread_start(objs->asnk_pots->thread); }

        if (objs->amod_sst != NULL) { thread_start(objs->amod_sst->thread); }
        if (objs->acon_tracks != NULL) { thread_start(objs->acon_tracks->thread); }
        if (objs->asnk_tracks != NULL) { thread_start(objs->asnk_tracks->thread); }

        if (objs->amod_lag != NULL) { thread_start(objs->amod_lag->thread); }
        if (objs->acon_spectra_delay != NULL) { thread_start(objs->acon_spectra_delay->thread); }
        if (objs->amod_noise_delay != NULL) { thread_start(objs->amod_noise_delay->thread); }
        if (objs->acon_powers_delay != NULL) { thread_start(objs->acon_powers_delay->thread); }

        if (objs->amod_sss != NULL) { thread_start(objs->amod_sss->thread); }
        
        if (objs->acon_spectra_sep != NULL) { thread_start(objs->acon_spectra_sep->thread); }
        if (objs->amod_istft_sep != NULL) { thread_start(objs->amod_istft_sep->thread); }
        if (objs->acon_hops_sep != NULL) { thread_start(objs->acon_hops_sep->thread); }
        if (objs->asnk_hops_sep != NULL) { thread_start(objs->asnk_hops_sep->thread); }
        
        if (objs->acon_spectra_pf != NULL) { thread_start(objs->acon_spectra_pf->thread); }
        if (objs->amod_istft_pf != NULL) { thread_start(objs->amod_istft_pf->thread); }
        if (objs->acon_hops_pf != NULL) { thread_start(objs->acon_hops_pf->thread); }
        if (objs->asnk_hops_pf != NULL) { thread_start(objs->asnk_hops_pf->thread); }

        // Join threads

        if (objs->asrc_hops != NULL) { thread_join(objs->asrc_hops->thread); }
        if (objs->acon_hops != NULL) { thread_join(objs->acon_hops->thread); }
        if (objs->asnk_hops != NULL) { thread_join(objs->asnk_hops->thread); }

        if (objs->asrc_targets != NULL) { thread_join(objs->asrc_targets->thread); }
        if (objs->acon_targets != NULL) { thread_join(objs->acon_targets->thread); }
        if (objs->asnk_targets != NULL) { thread_join(objs->asnk_targets->thread); }

        if (objs->amod_stft != NULL) { thread_join(objs->amod_stft->thread); }
        if (objs->acon_spectra != NULL) { thread_join(objs->acon_spectra->thread); }

        if (objs->amod_ssl != NULL) { thread_join(objs->amod_ssl->thread); }
        if (objs->acon_pots != NULL) { thread_join(objs->acon_pots->thread); }
        if (objs->asnk_pots != NULL) { thread_join(objs->asnk_pots->thread); }

        if (objs->amod_sst != NULL) { thread_join(objs->amod_sst->thread); }
        if (objs->acon_tracks != NULL) { thread_join(objs->acon_tracks->thread); }
        if (objs->asnk_tracks != NULL) { thread_join(objs->asnk_tracks->thread); }

        if (objs->amod_lag != NULL) { thread_join(objs->amod_lag->thread); }
        if (objs->acon_spectra_delay != NULL) { thread_join(objs->acon_spectra_delay->thread); }
        if (objs->amod_noise_delay != NULL) { thread_join(objs->amod_noise_delay->thread); }
        if (objs->acon_powers_delay != NULL) { thread_join(objs->acon_powers_delay->thread); }

        if (objs->amod_sss != NULL) { thread_join(objs->amod_sss->thread); }
        
        if (objs->acon_spectra_sep != NULL) { thread_join(objs->acon_spectra_sep->thread); }
        if (objs->amod_istft_sep != NULL) { thread_join(objs->amod_istft_sep->thread); }
        if (objs->acon_hops_sep != NULL) { thread_join(objs->acon_hops_sep->thread); }
        if (objs->asnk_hops_sep != NULL) { thread_join(objs->asnk_hops_sep->thread); }
        
        if (objs->acon_spectra_pf != NULL) { thread_join(objs->acon_spectra_pf->thread); }
        if (objs->amod_istft_pf != NULL) { thread_join(objs->amod_istft_pf->thread); }
        if (objs->acon_hops_pf != NULL) { thread_join(objs->acon_hops_pf->thread); }
        if (objs->asnk_hops_pf != NULL) { thread_join(objs->asnk_hops_pf->thread); }

    }