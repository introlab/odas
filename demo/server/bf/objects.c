
	#include "objects.h"

    objects * objects_construct(const configs * cfgs) {

    	objects * objs;
        unsigned int nBytes = 65536;

    	objs = (objects *) malloc(sizeof(objects));

        objs->in1 = (char *) malloc(sizeof(char) * nBytes);
        memset(objs->in1, 0x00, sizeof(char) * nBytes);
        objs->in2 = (char *) malloc(sizeof(char) * nBytes);
        memset(objs->in2, 0x00, sizeof(char) * nBytes);

        objs->dsr_hops_in_object = dsr_hops_construct(cfgs->dsr_hops_in_config, cfgs->msg_hops_in_config);
        objs->dsr_targets_in_object = dsr_targets_construct(cfgs->dsr_targets_in_config, cfgs->msg_targets_in_config);

        objs->con_hops_in_object = con_hops_construct(1, cfgs->msg_hops_in_config);
        objs->mod_stft_in_object = mod_stft_construct(cfgs->mod_stft_in_config, cfgs->msg_hops_in_config, cfgs->msg_spectra_in_config);
        objs->con_spectra_in_object = con_spectra_construct(1, cfgs->msg_spectra_in_config);
        objs->con_targets_in_object = con_targets_construct(1, cfgs->msg_targets_in_config);

        objs->mod_tt_object = mod_tt_construct(cfgs->mod_tt_config, cfgs->msg_targets_in_config, cfgs->msg_tracks_out_config);
        objs->mod_bf_object = mod_bf_construct(cfgs->mod_bf_config, cfgs->msg_tracks_out_config, cfgs->msg_spectra_in_config);
        
        objs->con_tracks_out_object = con_tracks_construct(2, cfgs->msg_tracks_out_config);
        objs->con_spectra_out_object = con_spectra_construct(1, cfgs->msg_spectra_out_config);
        objs->mod_istft_out_object = mod_istft_construct(cfgs->mod_istft_out_config, cfgs->msg_spectra_out_config, cfgs->msg_hops_out_config);
        objs->con_hops_out_object = con_hops_construct(1, cfgs->msg_hops_out_config);

        objs->ser_hops_out_object = ser_hops_construct(cfgs->ser_hops_out_config, cfgs->msg_hops_out_config);
        objs->ser_tracks_out_object = ser_tracks_construct(cfgs->ser_tracks_out_config, cfgs->msg_tracks_out_config);

        objs->out1 = (char *) malloc(sizeof(char) * nBytes);
        memset(objs->out1, 0x00, sizeof(char) * nBytes);
        objs->out2 = (char *) malloc(sizeof(char) * nBytes);
        memset(objs->out2, 0x00, sizeof(char) * nBytes);

    	return objs;

    }

    void objects_destroy(objects * objs) {

        free((void *) objs->in1);
        free((void *) objs->in2);

        dsr_hops_destroy(objs->dsr_hops_in_object);
        dsr_targets_destroy(objs->dsr_targets_in_object);

        con_hops_destroy(objs->con_hops_in_object);
    	mod_stft_destroy(objs->mod_stft_in_object);
        con_spectra_destroy(objs->con_spectra_in_object);
        con_targets_destroy(objs->con_targets_in_object);

    	mod_tt_destroy(objs->mod_tt_object);
    	mod_bf_destroy(objs->mod_bf_object);

        con_tracks_destroy(objs->con_tracks_out_object);
        con_spectra_destroy(objs->con_spectra_out_object);
    	mod_istft_destroy(objs->mod_istft_out_object);
        con_hops_destroy(objs->con_hops_out_object);

        ser_hops_destroy(objs->ser_hops_out_object);
        ser_tracks_destroy(objs->ser_tracks_out_object);

        free((void *) objs->out1);
        free((void *) objs->out2);

    }

    void objects_link(objects * objs) {

        dsr_hops_connect(objs->dsr_hops_in_object,
                         objs->in1,
                         objs->con_hops_in_object->in);

        dsr_targets_connect(objs->dsr_targets_in_object,
                            objs->in2,
                            objs->con_targets_in_object->in);

        mod_stft_connect(objs->mod_stft_in_object,
                         objs->con_hops_in_object->outs[0],
                         objs->con_spectra_in_object->in);

        mod_stft_enable(objs->mod_stft_in_object);

        mod_tt_connect(objs->mod_tt_object,
                       objs->con_targets_in_object->outs[0],
                       objs->con_tracks_out_object->in);

        mod_tt_enable(objs->mod_tt_object);

        mod_bf_connect(objs->mod_bf_object,
                       objs->con_spectra_in_object->outs[0],
                       objs->con_tracks_out_object->outs[0],
                       objs->con_spectra_out_object->in);

        mod_bf_enable(objs->mod_bf_object);

        mod_istft_connect(objs->mod_istft_out_object,
                          objs->con_spectra_out_object->outs[0],
                          objs->con_hops_out_object->in);

        mod_istft_enable(objs->mod_istft_out_object);

        ser_hops_connect(objs->ser_hops_out_object,
                         objs->con_hops_out_object->outs[0],
                         objs->out1);

        ser_tracks_connect(objs->ser_tracks_out_object,
                           objs->con_tracks_out_object->outs[1],
                           objs->out2);

    }

    void objects_process(objects * objs) {

        dsr_hops_process(objs->dsr_hops_in_object);
        dsr_targets_process(objs->dsr_targets_in_object);

        con_hops_process(objs->con_hops_in_object);
        con_targets_process(objs->con_targets_in_object);

        mod_stft_process(objs->mod_stft_in_object);
        con_spectra_process(objs->con_spectra_in_object);

        mod_tt_process(objs->mod_tt_object);
        con_tracks_process(objs->con_tracks_out_object);

        mod_bf_process(objs->mod_bf_object);
        con_spectra_process(objs->con_spectra_out_object);

        mod_istft_process(objs->mod_istft_out_object);
        con_hops_process(objs->con_hops_out_object);

        ser_hops_process(objs->ser_hops_out_object);
        ser_tracks_process(objs->ser_tracks_out_object);

    }