
	#include "objects.h"

    objects * objects_construct(configs * cfgs) {

    	objects * objs;

        // Define all connections

        msg_hops_obj * src_hops_in_raw_output;
        msg_hops_obj * mod_mapping_in_input;
        msg_hops_obj * snk_hops_in_raw_input;

        msg_targets_obj * src_targets_in_raw_output;
        msg_targets_obj * mod_align_in_input1;

        msg_hops_obj * mod_mapping_in_output;
        msg_hops_obj * mod_resample_in_input;

        msg_hops_obj * mod_resample_in_output;
        msg_hops_obj * mod_align_in_input2;
        msg_hops_obj * mod_stft_in_input;

        msg_targets_obj * mod_align_in_output;
        msg_targets_obj * mod_sst_input2;

        msg_spectra_obj * mod_stft_in_output;
        msg_spectra_obj * mod_noise_in_input;
        msg_spectra_obj * mod_ssl_input;
        msg_spectra_obj * mod_lag_input;

        msg_powers_obj * mod_noise_in_output;
        msg_powers_obj * mod_sss_input2;

        msg_pots_obj * mod_ssl_output;
        msg_pots_obj * mod_sst_input1;
        msg_pots_obj * snk_pots_input;

        msg_tracks_obj * mod_sst_output;
        msg_tracks_obj * mod_sss_input3;
        msg_tracks_obj * snk_tracks_input;

        msg_spectra_obj * mod_lag_output;
        msg_spectra_obj * mod_sss_input1;

        msg_spectra_obj * mod_sss_output1;
        msg_spectra_obj * mod_sss_output2;
        msg_spectra_obj * mod_istft_out_sep_input;
        msg_spectra_obj * mod_istft_out_pf_input;

        msg_hops_obj * mod_istft_out_sep_output;
        msg_hops_obj * mod_resample_out_seprs_input;
        msg_hops_obj * mod_resample_out_seprs_output;
        msg_hops_obj * snk_hops_out_seprs_input;

        msg_hops_obj * mod_istft_out_pf_output;
        msg_hops_obj * mod_resample_out_pfrs_input;
        msg_hops_obj * mod_resample_out_pfrs_output;
        msg_hops_obj * snk_hops_out_pfrs_input;

        // Create objects

    	objs = (objects *) malloc(sizeof(objects));

    	objs->src_hops_in_raw = src_hops_construct(cfgs->src_hops_in_raw_config, cfgs->msg_hops_in_raw_config);
    	objs->con_hops_in_raw = con_hops_construct(2, cfgs->msg_hops_in_raw_config);
    	objs->snk_hops_in_raw = snk_hops_construct(cfgs->snk_hops_in_raw_config, cfgs->msg_hops_in_raw_config);

            src_hops_in_raw_output = objs->con_hops_in_raw->in;
            mod_mapping_in_input = objs->con_hops_in_raw->outs[0];
            snk_hops_in_raw_input = objs->con_hops_in_raw->outs[1];

    	objs->src_targets_in_raw = src_targets_construct(cfgs->src_targets_in_raw_config, cfgs->msg_targets_in_raw_config);
    	objs->con_targets_in_raw = con_targets_construct(1, cfgs->msg_targets_in_raw_config);

            src_targets_in_raw_output = objs->con_targets_in_raw->in;
            mod_align_in_input1 = objs->con_targets_in_raw->outs[0];

    	objs->mod_mapping_in = mod_mapping_construct(cfgs->mod_mapping_in_config, cfgs->msg_hops_in_raw_config);
    	objs->con_hops_in_map = con_hops_construct(1, cfgs->msg_hops_in_map_config);

            mod_mapping_in_output = objs->con_hops_in_map->in;
            mod_resample_in_input = objs->con_hops_in_map->outs[0];

    	objs->mod_resample_in = mod_resample_construct(cfgs->mod_resample_in_config, cfgs->msg_hops_in_raw_config, cfgs->msg_hops_in_rs_config);
    	objs->con_hops_in_rs = con_hops_construct(2, cfgs->msg_hops_in_rs_config);

            mod_resample_in_output = objs->con_hops_in_rs->in;
            mod_align_in_input2 = objs->con_hops_in_rs->outs[0];
            mod_stft_in_input = objs->con_hops_in_rs->outs[1];

    	objs->mod_align_in = mod_align_construct(cfgs->mod_align_in_config, cfgs->msg_targets_in_raw_config, cfgs->msg_hops_in_raw_config, cfgs->msg_targets_in_rs_config);
    	objs->con_targets_in_rs = con_targets_construct(1, cfgs->msg_targets_in_rs_config);

            mod_align_in_output = objs->con_targets_in_rs->in;
            mod_sst_input2 = objs->con_targets_in_rs->outs[0];

    	objs->mod_stft_in = mod_stft_construct(cfgs->mod_stft_in_config, cfgs->msg_hops_in_rs_config, cfgs->msg_spectra_in_config);
    	objs->con_spectra_in = con_spectra_construct(3, cfgs->msg_spectra_in_config);

            mod_stft_in_output = objs->con_spectra_in->in;
            mod_noise_in_input = objs->con_spectra_in->outs[0];
            mod_ssl_input = objs->con_spectra_in->outs[1];
            mod_lag_input = objs->con_spectra_in->outs[2];

    	objs->mod_noise_in = mod_noise_construct(cfgs->mod_noise_in_config, cfgs->msg_spectra_in_config, cfgs->msg_powers_in_config);
    	objs->con_powers_in = con_powers_construct(1, cfgs->msg_powers_in_config);

            mod_noise_in_output = objs->con_powers_in->in;
            mod_sss_input2 = objs->con_powers_in->outs[0];

    	objs->mod_ssl = mod_ssl_construct(cfgs->mod_ssl_config, cfgs->msg_spectra_in_config, cfgs->msg_pots_config);
    	objs->con_pots = con_pots_construct(2, cfgs->msg_pots_config);
    	objs->snk_pots = snk_pots_construct(cfgs->snk_pots_config, cfgs->msg_pots_config);

            mod_ssl_output = objs->con_pots->in;
            mod_sst_input1 = objs->con_pots->outs[0];
            snk_pots_input = objs->con_pots->outs[1];

    	objs->mod_sst = mod_sst_construct(cfgs->mod_sst_config, cfgs->mod_ssl_config, cfgs->msg_pots_config, cfgs->msg_targets_in_rs_config, cfgs->msg_tracks_config);
    	objs->con_tracks = con_tracks_construct(2, cfgs->msg_tracks_config);
    	objs->snk_tracks = snk_tracks_construct(cfgs->snk_tracks_config, cfgs->msg_tracks_config);

            mod_sst_output = objs->con_tracks->in;
            mod_sss_input3 = objs->con_tracks->outs[0];
            snk_tracks_input = objs->con_tracks->outs[1];

        objs->mod_lag = mod_lag_construct(cfgs->mod_lag_config, cfgs->msg_spectra_lag_config);
        objs->con_spectra_lag = con_spectra_construct(1, cfgs->msg_spectra_lag_config);

            mod_lag_output = objs->con_spectra_lag->in;
            mod_sss_input1 = objs->con_spectra_lag->outs[0];

    	objs->mod_sss = mod_sss_construct(cfgs->mod_sss_config, cfgs->msg_tracks_config, cfgs->msg_spectra_in_config, cfgs->msg_powers_in_config);
    	objs->con_spectra_out_sep = con_spectra_construct(1, cfgs->msg_spectra_out_sep_config);
    	objs->con_spectra_out_pf = con_spectra_construct(1, cfgs->msg_spectra_out_pf_config);

            mod_sss_output1 = objs->con_spectra_out_sep->in;
            mod_sss_output2 = objs->con_spectra_out_pf->in;
            mod_istft_out_sep_input = objs->con_spectra_out_sep->outs[0];
            mod_istft_out_pf_input = objs->con_spectra_out_pf->outs[1];

    	objs->mod_istft_out_sep = mod_istft_construct(cfgs->mod_istft_out_sep_config, cfgs->msg_spectra_out_sep_config, cfgs->msg_hops_out_sep_config);
    	objs->con_hops_out_sep = con_hops_construct(1, cfgs->msg_hops_out_sep_config);
    	objs->mod_resample_out_seprs = mod_resample_construct(cfgs->mod_resample_out_seprs_config, cfgs->msg_hops_out_sep_config, cfgs->msg_hops_out_seprs_config);
    	objs->con_hops_out_seprs = con_hops_construct(1, cfgs->msg_hops_out_seprs_config);
    	objs->snk_hops_out_seprs = snk_hops_construct(cfgs->snk_hops_out_seprs_config, cfgs->msg_hops_out_seprs_config);

            mod_istft_out_sep_output = objs->con_hops_out_sep->in;
            mod_resample_out_seprs_input = objs->con_hops_out_sep->outs[0];
            mod_resample_out_seprs_output = objs->con_hops_out_seprs->in;
            snk_hops_out_seprs_input = objs->con_hops_out_seprs->outs[0];        

		objs->mod_istft_out_pf = mod_istft_construct(cfgs->mod_istft_out_pf_config, cfgs->msg_spectra_out_pf_config, cfgs->msg_hops_out_pf_config);
		objs->con_hops_out_pf = con_hops_construct(1, cfgs->msg_hops_out_pf_config);
		objs->mod_resample_out_pfrs = mod_resample_construct(cfgs->mod_resample_out_pfrs_config, cfgs->msg_hops_out_pf_config, cfgs->msg_hops_out_pfrs_config);
		objs->con_hops_out_pfrs = con_hops_construct(1, cfgs->msg_hops_out_pfrs_config);
		objs->snk_hops_out_pfrs = snk_hops_construct(cfgs->snk_hops_out_pfrs_config, cfgs->msg_hops_out_pfrs_config);

            mod_istft_out_pf_output = objs->con_hops_out_pf->in;
            mod_resample_out_pfrs_input = objs->con_hops_out_pf->outs[0];
            mod_resample_out_pfrs_output = objs->con_hops_out_pfrs->in;
            snk_hops_out_pfrs_input = objs->con_hops_out_pfrs->outs[0];

        // Connect

        src_hops_connect(objs->src_hops_in_raw, src_hops_in_raw_output);
        src_targets_connect(objs->src_targets_in_raw, src_targets_in_raw_output);
        snk_hops_connect(objs->snk_hops_in_raw, snk_hops_in_raw_input);

        mod_mapping_connect(objs->mod_mapping_in, mod_mapping_in_input, mod_mapping_in_output);
                
        mod_resample_connect(objs->mod_resample_in, mod_resample_in_input, mod_resample_in_output);

        mod_align_connect(objs->mod_align_in, mod_align_in_input1, mod_align_in_input2, mod_align_in_output);
        mod_stft_connect(objs->mod_stft_in, mod_stft_in_input, mod_stft_in_output);
        mod_noise_connect(objs->mod_noise_in, mod_noise_in_input, mod_noise_in_output);

        mod_ssl_connect(objs->mod_ssl, mod_ssl_input, mod_ssl_output);
        snk_pots_connect(objs->snk_pots, snk_pots_input);
        mod_sst_connect(objs->mod_sst, mod_sst_input1, mod_sst_input2, mod_sst_output);
        snk_tracks_connect(objs->snk_tracks, snk_tracks_input);
        mod_lag_connect(objs->mod_lag, mod_lag_input, mod_lag_output);
        mod_sss_connect(objs->mod_sss, mod_sss_input1, mod_sss_input2, mod_sss_input3, mod_sss_output1, mod_sss_output2);
        
        mod_istft_connect(objs->mod_istft_out_sep, mod_istft_out_sep_input, mod_istft_out_sep_output);
        mod_resample_connect(objs->mod_resample_out_seprs, mod_resample_out_seprs_input, mod_resample_out_seprs_output);
        snk_hops_connect(objs->snk_hops_out_seprs, snk_hops_out_seprs_input);

        mod_istft_connect(objs->mod_istft_out_pf, mod_istft_out_pf_input, mod_istft_out_pf_output);
        mod_resample_connect(objs->mod_resample_out_pfrs, mod_resample_out_pfrs_input, mod_resample_out_pfrs_output);
        snk_hops_connect(objs->snk_hops_out_pfrs, snk_hops_out_pfrs_input);

        // Enable

        if (objs->snk_hops_in_raw->interface->type != interface_blackhole) {

            // Nothing to do

        }

        if (objs->snk_pots->interface->type != interface_blackhole) {

            mod_ssl_enable(objs->mod_ssl);

            mod_stft_enable(objs->mod_stft_in);
            mod_align_enable(objs->mod_align_in);
            mod_resample_enable(objs->mod_resample_in);

            mod_mapping_enable(objs->mod_mapping_in);                        

        }

        if (objs->snk_tracks->interface->type != interface_blackhole) {

            mod_sst_enable(objs->mod_sst);
            mod_ssl_enable(objs->mod_ssl);

            mod_stft_enable(objs->mod_stft_in);
            mod_align_enable(objs->mod_align_in);
            mod_resample_enable(objs->mod_resample_in);

            mod_mapping_enable(objs->mod_mapping_in);                        

        }

        if (objs->snk_hops_out_seprs->interface->type != interface_blackhole) {

            mod_istft_enable(objs->mod_istft_out_sep);
            mod_resample_enable(objs->mod_resample_out_seprs);

            mod_sss_enable(objs->mod_sss);
            mod_lag_enable(objs->mod_lag);
            mod_sst_enable(objs->mod_sst);
            mod_ssl_enable(objs->mod_ssl);

            mod_noise_enable(objs->mod_noise_in);
            mod_stft_enable(objs->mod_stft_in);
            mod_align_enable(objs->mod_align_in);
            mod_resample_enable(objs->mod_resample_in);

            mod_mapping_enable(objs->mod_mapping_in);

        }

        if (objs->snk_hops_out_pfrs->interface->type != interface_blackhole) {

            mod_istft_enable(objs->mod_istft_out_pf);
            mod_resample_enable(objs->mod_resample_out_pfrs);

            mod_sss_enable(objs->mod_sss);
            mod_lag_enable(objs->mod_lag);
            mod_sst_enable(objs->mod_sst);
            mod_ssl_enable(objs->mod_ssl);

            mod_noise_enable(objs->mod_noise_in);
            mod_stft_enable(objs->mod_stft_in);
            mod_align_enable(objs->mod_align_in);
            mod_resample_enable(objs->mod_resample_in);

            mod_mapping_enable(objs->mod_mapping_in);

        }

    	return objs;

    }

    void objects_destroy(objects * objs) {

    	src_hops_destroy(objs->src_hops_in_raw);
    	con_hops_destroy(objs->con_hops_in_raw);
    	snk_hops_destroy(objs->snk_hops_in_raw);

    	src_targets_destroy(objs->src_targets_in_raw);
    	con_targets_destroy(objs->con_targets_in_raw);

    	mod_mapping_destroy(objs->mod_mapping_in);
    	con_hops_destroy(objs->con_hops_in_map);

    	mod_resample_destroy(objs->mod_resample_in);
    	con_hops_destroy(objs->con_hops_in_rs);

    	mod_align_destroy(objs->mod_align_in);
    	con_targets_destroy(objs->con_targets_in_rs);

    	mod_stft_destroy(objs->mod_stft_in);
    	con_spectra_destroy(objs->con_spectra_in);

    	mod_noise_destroy(objs->mod_noise_in);
    	con_powers_destroy(objs->con_powers_in);

    	mod_ssl_destroy(objs->mod_ssl);
    	con_pots_destroy(objs->con_pots);
    	snk_pots_destroy(objs->snk_pots);

    	mod_sst_destroy(objs->mod_sst);
    	con_tracks_destroy(objs->con_tracks);
    	snk_tracks_destroy(objs->snk_tracks);

        mod_lag_destroy(objs->mod_lag);
        con_spectra_destroy(objs->con_spectra_lag);

    	mod_sss_destroy(objs->mod_sss);
    	con_spectra_destroy(objs->con_spectra_out_sep);
    	con_spectra_destroy(objs->con_spectra_out_pf);

    	mod_istft_destroy(objs->mod_istft_out_sep);
    	con_hops_destroy(objs->con_hops_out_sep);
    	mod_resample_destroy(objs->mod_resample_out_seprs);
    	con_hops_destroy(objs->con_hops_out_seprs);
    	snk_hops_destroy(objs->snk_hops_out_seprs);

    	mod_istft_destroy(objs->mod_istft_out_pf);
    	con_hops_destroy(objs->con_hops_out_pf);
    	mod_resample_destroy(objs->mod_resample_out_pfrs);
    	con_hops_destroy(objs->con_hops_out_pfrs);
    	snk_hops_destroy(objs->snk_hops_out_pfrs);

    	free((void *) objs);

    }

    void objects_process(objects * objs) {

        int rtnValueHops;
        int rtnValueTargets;
        int rtnValueResampleIn;
        int rtnValueResampleOutSep;
        int rtnValueResampleOutPf;
        int rtnValueAlign;

        // Open Sources & Sinks

        src_hops_open(objs->src_hops_in_raw);
        src_targets_open(objs->src_targets_in_raw);
        snk_hops_open(objs->snk_hops_in_raw);
        
        snk_pots_open(objs->snk_pots);
        snk_tracks_open(objs->snk_tracks);
        snk_hops_open(objs->snk_hops_out_seprs);
        snk_hops_open(objs->snk_hops_out_pfrs);       

        // Process

        while(1) {

            rtnValueHops = src_hops_process(objs->src_hops_in_raw);
            if (rtnValueHops == -1) { break; }            
            con_hops_process(objs->con_hops_in_raw);
            snk_hops_process(objs->snk_hops_in_raw);

            rtnValueTargets = src_targets_process(objs->src_targets_in_raw);
            if (rtnValueTargets == -1) { break; }
            con_targets_process(objs->con_targets_in_raw);

            mod_mapping_process(objs->mod_mapping_in);
            con_hops_process(objs->con_hops_in_map);

            mod_resample_process_push(objs->mod_resample_in);
            mod_align_process_push(objs->mod_align_in);

            while(1) {

                rtnValueResampleIn = mod_resample_process_pop(objs->mod_resample_in);

                if (rtnValueResampleIn == -1) { break; }
                con_hops_process(objs->con_hops_in_rs);

                rtnValueAlign = mod_align_process_pop(objs->mod_align_in);
                con_targets_process(objs->con_targets_in_rs);

                mod_stft_process(objs->mod_stft_in);
                con_spectra_process(objs->con_spectra_in);

                mod_noise_process(objs->mod_noise_in);
                con_powers_process(objs->con_powers_in);

                mod_ssl_process(objs->mod_ssl);
                con_pots_process(objs->con_pots);
                snk_pots_process(objs->snk_pots);

                mod_sst_process(objs->mod_sst);
                con_tracks_process(objs->con_tracks);
                snk_tracks_process(objs->snk_tracks);

                mod_lag_process(objs->mod_lag);
                con_spectra_process(objs->con_spectra_lag);

                mod_sss_process(objs->mod_sss);
                con_spectra_process(objs->con_spectra_out_sep);
                con_spectra_process(objs->con_spectra_out_pf);

                mod_istft_process(objs->mod_istft_out_sep);
                con_hops_process(objs->con_hops_out_sep);
                mod_resample_process_push(objs->mod_resample_out_seprs);

                while(1) {

                    rtnValueResampleOutSep = mod_resample_process_pop(objs->mod_resample_out_seprs);

                    if (rtnValueResampleOutSep == -1) { break; }
                    con_hops_process(objs->con_hops_out_seprs);

                    snk_hops_process(objs->snk_hops_out_seprs);

                }

                while(1) {

                    rtnValueResampleOutPf = mod_resample_process_pop(objs->mod_resample_out_pfrs);

                    if (rtnValueResampleOutPf == -1) { break; }
                    con_hops_process(objs->con_hops_out_pfrs);

                    snk_hops_process(objs->snk_hops_out_pfrs);

                }

            }       

        }

        // Close Sources & Sinks

        src_hops_close(objs->src_hops_in_raw);
        src_targets_close(objs->src_targets_in_raw);
        snk_hops_close(objs->snk_hops_in_raw);
        
        snk_pots_close(objs->snk_pots);
        snk_tracks_close(objs->snk_tracks);
        snk_hops_close(objs->snk_hops_out_seprs);
        snk_hops_close(objs->snk_hops_out_pfrs);

    }

    aobjects * aobjects_construct(configs * cfgs) {
/*
        aobjects * objs;

        unsigned int nMessages = 100;

        // Define all connections

        amsg_hops_obj * asrc_hops_in_raw_output;
        amsg_hops_obj * amod_mapping_in_input;
        amsg_hops_obj * asnk_hops_in_raw_input;

        amsg_targets_obj * asrc_targets_in_raw_output;
        amsg_targets_obj * amod_align_in_input1;

        amsg_hops_obj * amod_mapping_in_output;
        amsg_hops_obj * amod_resample_in_input;

        amsg_hops_obj * amod_resample_in_output;
        amsg_hops_obj * amod_align_in_input2;
        amsg_hops_obj * amod_stft_in_input;

        amsg_targets_obj * amod_align_in_output;
        amsg_targets_obj * amod_sst_input2;

        amsg_spectra_obj * amod_stft_in_output;
        amsg_spectra_obj * amod_noise_in_input;
        amsg_spectra_obj * amod_ssl_input;
        amsg_spectra_obj * amod_lag_input;

        amsg_powers_obj * amod_noise_in_output;
        amsg_powers_obj * amod_sss_input2;

        amsg_pots_obj * amod_ssl_output;
        amsg_pots_obj * amod_sst_input1;
        amsg_pots_obj * asnk_pots_input;

        amsg_tracks_obj * amod_sst_output;
        amsg_tracks_obj * amod_sss_input3;
        amsg_tracks_obj * asnk_tracks_input;

        amsg_spectra_obj * amod_lag_output;
        amsg_spectra_obj * amod_sss_input1;

        amsg_spectra_obj * amod_sss_output1;
        amsg_spectra_obj * amod_sss_output2;
        amsg_spectra_obj * amod_istft_out_sep_input;
        amsg_spectra_obj * amod_istft_out_pf_input;

        amsg_hops_obj * amod_istft_out_sep_output;
        amsg_hops_obj * amod_resample_out_seprs_input;
        amsg_hops_obj * amod_resample_out_seprs_output;
        amsg_hops_obj * asnk_hops_out_seprs_input;

        amsg_hops_obj * amod_istft_out_pf_output;
        amsg_hops_obj * amod_resample_out_pfrs_input;
        amsg_hops_obj * amod_resample_out_pfrs_output;
        amsg_hops_obj * asnk_hops_out_pfrs_input;

        // Create objects

        objs = (aobjects *) malloc(sizeof(aobjects));

        objs->asrc_hops_in_raw = asrc_hops_construct(cfgs->src_hops_in_raw_config, cfgs->msg_hops_in_raw_config);
        objs->acon_hops_in_raw = acon_hops_construct(2, nMessages, cfgs->msg_hops_in_raw_config);
        objs->asnk_hops_in_raw = asnk_hops_construct(cfgs->snk_hops_in_raw_config, cfgs->msg_hops_in_raw_config);

            asrc_hops_in_raw_output = objs->acon_hops_in_raw->in;
            amod_mapping_in_input = objs->acon_hops_in_raw->outs[0];
            asnk_hops_in_raw_input = objs->acon_hops_in_raw->outs[1];

        objs->asrc_targets_in_raw = asrc_targets_construct(cfgs->src_targets_in_raw_config, cfgs->msg_targets_in_raw_config);
        objs->acon_targets_in_raw = acon_targets_construct(1, nMessages, cfgs->msg_targets_in_raw_config);

            asrc_targets_in_raw_output = objs->acon_targets_in_raw->in;
            amod_align_in_input1 = objs->acon_targets_in_raw->outs[0];

        objs->amod_mapping_in = amod_mapping_construct(cfgs->mod_mapping_in_config, cfgs->msg_hops_in_raw_config);
        objs->acon_hops_in_map = acon_hops_construct(1, nMessages, cfgs->msg_hops_in_map_config);

            amod_mapping_in_output = objs->acon_hops_in_map->in;
            amod_resample_in_input = objs->acon_hops_in_map->outs[0];

        objs->amod_resample_in = amod_resample_construct(cfgs->mod_resample_in_config, cfgs->msg_hops_in_raw_config, cfgs->msg_hops_in_rs_config);
        objs->acon_hops_in_rs = acon_hops_construct(2, nMessages, cfgs->msg_hops_in_rs_config);

            amod_resample_in_output = objs->acon_hops_in_rs->in;
            amod_align_in_input2 = objs->acon_hops_in_rs->outs[0];
            amod_stft_in_input = objs->acon_hops_in_rs->outs[1];

        objs->amod_align_in = amod_align_construct(cfgs->mod_align_in_config, cfgs->msg_targets_in_raw_config, cfgs->msg_hops_in_raw_config, cfgs->msg_targets_in_rs_config);
        objs->acon_targets_in_rs = acon_targets_construct(1, nMessages, cfgs->msg_targets_in_rs_config);

            amod_align_in_output = objs->acon_targets_in_rs->in;
            amod_sst_input2 = objs->acon_targets_in_rs->outs[0];

        objs->amod_stft_in = amod_stft_construct(cfgs->mod_stft_in_config, cfgs->msg_hops_in_rs_config, cfgs->msg_spectra_in_config);
        objs->acon_spectra_in = acon_spectra_construct(3, nMessages, cfgs->msg_spectra_in_config);

            amod_stft_in_output = objs->acon_spectra_in->in;
            amod_noise_in_input = objs->acon_spectra_in->outs[0];
            amod_ssl_input = objs->acon_spectra_in->outs[1];
            amod_lag_input = objs->acon_spectra_in->outs[2];

        objs->amod_noise_in = amod_noise_construct(cfgs->mod_noise_in_config, cfgs->msg_spectra_in_config, cfgs->msg_powers_in_config);
        objs->acon_powers_in = acon_powers_construct(1, nMessages, cfgs->msg_powers_in_config);

            amod_noise_in_output = objs->acon_powers_in->in;
            amod_sss_input2 = objs->acon_powers_in->outs[0];

        objs->amod_ssl = amod_ssl_construct(cfgs->mod_ssl_config, cfgs->msg_spectra_in_config, cfgs->msg_pots_config);
        objs->acon_pots = acon_pots_construct(2, nMessages, cfgs->msg_pots_config);
        objs->asnk_pots = asnk_pots_construct(cfgs->snk_pots_config, cfgs->msg_pots_config);

            amod_ssl_output = objs->acon_pots->in;
            amod_sst_input1 = objs->acon_pots->outs[0];
            asnk_pots_input = objs->acon_pots->outs[1];

        objs->amod_sst = amod_sst_construct(cfgs->mod_sst_config, cfgs->mod_ssl_config, cfgs->msg_pots_config, cfgs->msg_targets_in_rs_config, cfgs->msg_tracks_config);
        objs->acon_tracks = acon_tracks_construct(2, nMessages, cfgs->msg_tracks_config);
        objs->asnk_tracks = asnk_tracks_construct(cfgs->snk_tracks_config, cfgs->msg_tracks_config);

            amod_sst_output = objs->acon_tracks->in;
            amod_sss_input3 = objs->acon_tracks->outs[0];
            asnk_tracks_input = objs->acon_tracks->outs[1];

        objs->amod_lag = amod_lag_construct(cfgs->mod_lag_config, cfgs->msg_spectra_lag_config);
        objs->acon_spectra_lag = acon_spectra_construct(1, nMessages, cfgs->msg_spectra_lag_config);

            amod_lag_output = objs->acon_spectra_lag->in;
            amod_sss_input1 = objs->acon_spectra_lag->outs[0];

        objs->amod_sss = amod_sss_construct(cfgs->mod_sss_config, cfgs->msg_tracks_config, cfgs->msg_spectra_in_config, cfgs->msg_powers_in_config);
        objs->acon_spectra_out_sep = acon_spectra_construct(1, nMessages, cfgs->msg_spectra_out_sep_config);
        objs->acon_spectra_out_pf = acon_spectra_construct(1, nMessages, cfgs->msg_spectra_out_pf_config);

            amod_sss_output1 = objs->acon_spectra_out_sep->in;
            amod_sss_output2 = objs->acon_spectra_out_pf->in;
            amod_istft_out_sep_input = objs->acon_spectra_out_sep->outs[0];
            amod_istft_out_pf_input = objs->acon_spectra_out_pf->outs[1];

        objs->amod_istft_out_sep = amod_istft_construct(cfgs->mod_istft_out_sep_config, cfgs->msg_spectra_out_sep_config, cfgs->msg_hops_out_sep_config);
        objs->acon_hops_out_sep = acon_hops_construct(1, nMessages, cfgs->msg_hops_out_sep_config);
        objs->amod_resample_out_seprs = amod_resample_construct(cfgs->mod_resample_out_seprs_config, cfgs->msg_hops_out_sep_config, cfgs->msg_hops_out_seprs_config);
        objs->acon_hops_out_seprs = acon_hops_construct(1, nMessages, cfgs->msg_hops_out_seprs_config);
        objs->asnk_hops_out_seprs = asnk_hops_construct(cfgs->snk_hops_out_seprs_config, cfgs->msg_hops_out_seprs_config);

            amod_istft_out_sep_output = objs->acon_hops_out_sep->in;
            amod_resample_out_seprs_input = objs->acon_hops_out_sep->outs[0];
            amod_resample_out_seprs_output = objs->acon_hops_out_seprs->in;
            asnk_hops_out_seprs_input = objs->acon_hops_out_seprs->outs[0];        

        objs->amod_istft_out_pf = amod_istft_construct(cfgs->mod_istft_out_pf_config, cfgs->msg_spectra_out_pf_config, cfgs->msg_hops_out_pf_config);
        objs->acon_hops_out_pf = acon_hops_construct(1, nMessages, cfgs->msg_hops_out_pf_config);
        objs->amod_resample_out_pfrs = amod_resample_construct(cfgs->mod_resample_out_pfrs_config, cfgs->msg_hops_out_pf_config, cfgs->msg_hops_out_pfrs_config);
        objs->acon_hops_out_pfrs = acon_hops_construct(1, nMessages, cfgs->msg_hops_out_pfrs_config);
        objs->asnk_hops_out_pfrs = asnk_hops_construct(cfgs->snk_hops_out_pfrs_config, cfgs->msg_hops_out_pfrs_config);

            amod_istft_out_pf_output = objs->acon_hops_out_pf->in;
            amod_resample_out_pfrs_input = objs->acon_hops_out_pf->outs[0];
            amod_resample_out_pfrs_output = objs->acon_hops_out_pfrs->in;
            asnk_hops_out_pfrs_input = objs->acon_hops_out_pfrs->outs[0];

        // Connect

        asrc_hops_connect(objs->asrc_hops_in_raw, asrc_hops_in_raw_output);
        asrc_targets_connect(objs->asrc_targets_in_raw, asrc_targets_in_raw_output);
        asnk_hops_connect(objs->asnk_hops_in_raw, asnk_hops_in_raw_input);

        amod_mapping_connect(objs->amod_mapping_in, amod_mapping_in_input, amod_mapping_in_output);
                
        amod_resample_connect(objs->amod_resample_in, amod_resample_in_input, amod_resample_in_output);
        amod_align_connect(objs->amod_align_in, amod_align_in_input1, amod_align_in_input2, amod_align_in_output);
        amod_stft_connect(objs->amod_stft_in, amod_stft_in_input, amod_stft_in_output);
        amod_noise_connect(objs->amod_noise_in, amod_noise_in_input, amod_noise_in_output);

        amod_ssl_connect(objs->amod_ssl, amod_ssl_input, amod_ssl_output);
        asnk_pots_connect(objs->asnk_pots, asnk_pots_input);
        amod_sst_connect(objs->amod_sst, amod_sst_input1, amod_sst_input2, amod_sst_output);
        asnk_tracks_connect(objs->asnk_tracks, asnk_tracks_input);
        amod_lag_connect(objs->amod_lag, amod_lag_input, amod_lag_output);
        amod_sss_connect(objs->amod_sss, amod_sss_input1, amod_sss_input2, amod_sss_input3, amod_sss_output1, amod_sss_output2);
        
        amod_istft_connect(objs->amod_istft_out_sep, amod_istft_out_sep_input, amod_istft_out_sep_output);
        amod_resample_connect(objs->amod_resample_out_seprs, amod_resample_out_seprs_input, amod_resample_out_seprs_output);
        asnk_hops_connect(objs->asnk_hops_out_seprs, asnk_hops_out_seprs_input);

        amod_istft_connect(objs->amod_istft_out_pf, amod_istft_out_pf_input, amod_istft_out_pf_output);
        amod_resample_connect(objs->amod_resample_out_pfrs, amod_resample_out_pfrs_input, amod_resample_out_pfrs_output);
        asnk_hops_connect(objs->asnk_hops_out_pfrs, asnk_hops_out_pfrs_input);

        // Enable

        if (objs->asnk_hops_in_raw->snk_hops->interface->type != interface_blackhole) {

            // Nothing to do

        }

        if (objs->asnk_pots->snk_pots->interface->type != interface_blackhole) {

            amod_ssl_enable(objs->amod_ssl);

            amod_stft_enable(objs->amod_stft_in);
            amod_align_enable(objs->amod_align_in);
            amod_resample_enable(objs->amod_resample_in);

            amod_mapping_enable(objs->amod_mapping_in);                        

        }

        if (objs->asnk_tracks->snk_tracks->interface->type != interface_blackhole) {

            amod_sst_enable(objs->amod_sst);
            amod_ssl_enable(objs->amod_ssl);

            amod_stft_enable(objs->amod_stft_in);
            amod_align_enable(objs->amod_align_in);
            amod_resample_enable(objs->amod_resample_in);

            amod_mapping_enable(objs->amod_mapping_in);                        

        }

        if (objs->asnk_hops_out_seprs->snk_hops->interface->type != interface_blackhole) {

            amod_istft_enable(objs->amod_istft_out_sep);
            amod_resample_enable(objs->amod_resample_out_seprs);

            amod_sss_enable(objs->amod_sss);
            amod_lag_enable(objs->amod_lag);
            amod_sst_enable(objs->amod_sst);
            amod_ssl_enable(objs->amod_ssl);

            amod_noise_enable(objs->amod_noise_in);
            amod_stft_enable(objs->amod_stft_in);
            amod_align_enable(objs->amod_align_in);
            amod_resample_enable(objs->amod_resample_in);

            amod_mapping_enable(objs->amod_mapping_in);

        }

        if (objs->asnk_hops_out_pfrs->snk_hops->interface->type != interface_blackhole) {

            amod_istft_enable(objs->amod_istft_out_pf);
            amod_resample_enable(objs->amod_resample_out_pfrs);

            amod_sss_enable(objs->amod_sss);
            amod_lag_enable(objs->amod_lag);
            amod_sst_enable(objs->amod_sst);
            amod_ssl_enable(objs->amod_ssl);

            amod_noise_enable(objs->amod_noise_in);
            amod_stft_enable(objs->amod_stft_in);
            amod_align_enable(objs->amod_align_in);
            amod_resample_enable(objs->amod_resample_in);

            amod_mapping_enable(objs->amod_mapping_in);

        }

        return objs;        
*/
    }

    void aobjects_destroy(aobjects * objs) {
/*
        asrc_hops_destroy(objs->asrc_hops_in_raw);
        acon_hops_destroy(objs->acon_hops_in_raw);
        asnk_hops_destroy(objs->asnk_hops_in_raw);

        asrc_targets_destroy(objs->asrc_targets_in_raw);
        acon_targets_destroy(objs->acon_targets_in_raw);

        amod_mapping_destroy(objs->amod_mapping_in);
        acon_hops_destroy(objs->acon_hops_in_map);

        amod_resample_destroy(objs->amod_resample_in);
        acon_hops_destroy(objs->acon_hops_in_rs);

        amod_align_destroy(objs->amod_align_in);
        acon_targets_destroy(objs->acon_targets_in_rs);

        amod_stft_destroy(objs->amod_stft_in);
        acon_spectra_destroy(objs->acon_spectra_in);

        amod_noise_destroy(objs->amod_noise_in);
        acon_powers_destroy(objs->acon_powers_in);

        amod_ssl_destroy(objs->amod_ssl);
        acon_pots_destroy(objs->acon_pots);
        asnk_pots_destroy(objs->asnk_pots);

        amod_sst_destroy(objs->amod_sst);
        acon_tracks_destroy(objs->acon_tracks);
        asnk_tracks_destroy(objs->asnk_tracks);

        amod_lag_destroy(objs->amod_lag);
        acon_spectra_destroy(objs->acon_spectra_lag);

        amod_sss_destroy(objs->amod_sss);
        acon_spectra_destroy(objs->acon_spectra_out_sep);
        acon_spectra_destroy(objs->acon_spectra_out_pf);

        amod_istft_destroy(objs->amod_istft_out_sep);
        acon_hops_destroy(objs->acon_hops_out_sep);
        amod_resample_destroy(objs->amod_resample_out_seprs);
        acon_hops_destroy(objs->acon_hops_out_seprs);
        asnk_hops_destroy(objs->asnk_hops_out_seprs);

        amod_istft_destroy(objs->amod_istft_out_pf);
        acon_hops_destroy(objs->acon_hops_out_pf);
        amod_resample_destroy(objs->amod_resample_out_pfrs);
        acon_hops_destroy(objs->acon_hops_out_pfrs);
        asnk_hops_destroy(objs->asnk_hops_out_pfrs);

        free((void *) objs);
*/
    }

    void aobjects_process(aobjects * objs) {
/*
        thread_start(objs->asrc_hops_in_raw->thread);
        thread_start(objs->acon_hops_in_raw->thread);
        thread_start(objs->asnk_hops_in_raw->thread);

        thread_start(objs->asrc_targets_in_raw->thread);
        thread_start(objs->acon_targets_in_raw->thread);

        thread_start(objs->amod_mapping_in->thread);
        thread_start(objs->acon_hops_in_map->thread);

        thread_start(objs->amod_resample_in->thread);
        thread_start(objs->acon_hops_in_rs->thread);

        thread_start(objs->amod_align_in->thread);
        thread_start(objs->acon_targets_in_rs->thread);

        thread_start(objs->amod_stft_in->thread);
        thread_start(objs->acon_spectra_in->thread);

        thread_start(objs->amod_noise_in->thread);
        thread_start(objs->acon_powers_in->thread);

        thread_start(objs->amod_ssl->thread);
        thread_start(objs->acon_pots->thread);
        thread_start(objs->asnk_pots->thread);

        thread_start(objs->amod_sst->thread);
        thread_start(objs->acon_tracks->thread);
        thread_start(objs->asnk_tracks->thread);

        thread_start(objs->amod_lag->thread);
        thread_start(objs->acon_spectra_lag->thread);

        thread_start(objs->amod_sss->thread);
        thread_start(objs->acon_spectra_out_sep->thread);
        thread_start(objs->acon_spectra_out_pf->thread);

        thread_start(objs->amod_istft_out_sep->thread);
        thread_start(objs->acon_hops_out_sep->thread);
        thread_start(objs->amod_resample_out_seprs->thread);
        thread_start(objs->acon_hops_out_seprs->thread);
        thread_start(objs->asnk_hops_out_seprs->thread);

        thread_start(objs->amod_istft_out_pf->thread);
        thread_start(objs->acon_hops_out_pf->thread);
        thread_start(objs->amod_resample_out_pfrs->thread);
        thread_start(objs->acon_hops_out_pfrs->thread);
        thread_start(objs->asnk_hops_out_pfrs->thread);


        thread_stop(objs->asrc_hops_in_raw->thread);
        thread_stop(objs->acon_hops_in_raw->thread);
        thread_stop(objs->asnk_hops_in_raw->thread);

        thread_stop(objs->asrc_targets_in_raw->thread);
        thread_stop(objs->acon_targets_in_raw->thread);

        thread_stop(objs->amod_mapping_in->thread);
        thread_stop(objs->acon_hops_in_map->thread);

        thread_stop(objs->amod_resample_in->thread);
        thread_stop(objs->acon_hops_in_rs->thread);

        thread_stop(objs->amod_align_in->thread);
        thread_stop(objs->acon_targets_in_rs->thread);

        thread_stop(objs->amod_stft_in->thread);
        thread_stop(objs->acon_spectra_in->thread);

        thread_stop(objs->amod_noise_in->thread);
        thread_stop(objs->acon_powers_in->thread);

        thread_stop(objs->amod_ssl->thread);
        thread_stop(objs->acon_pots->thread);
        thread_stop(objs->asnk_pots->thread);

        thread_stop(objs->amod_sst->thread);
        thread_stop(objs->acon_tracks->thread);
        thread_stop(objs->asnk_tracks->thread);

        thread_stop(objs->amod_lag->thread);
        thread_stop(objs->acon_spectra_lag->thread);

        thread_stop(objs->amod_sss->thread);
        thread_stop(objs->acon_spectra_out_sep->thread);
        thread_stop(objs->acon_spectra_out_pf->thread);

        thread_stop(objs->amod_istft_out_sep->thread);
        thread_stop(objs->acon_hops_out_sep->thread);
        thread_stop(objs->amod_resample_out_seprs->thread);
        thread_stop(objs->acon_hops_out_seprs->thread);
        thread_stop(objs->asnk_hops_out_seprs->thread);

        thread_stop(objs->amod_istft_out_pf->thread);
        thread_stop(objs->acon_hops_out_pf->thread);
        thread_stop(objs->amod_resample_out_pfrs->thread);
        thread_stop(objs->acon_hops_out_pfrs->thread);
        thread_stop(objs->asnk_hops_out_pfrs->thread);        
*/
    }
