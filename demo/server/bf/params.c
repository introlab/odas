    
    #include "params.h"

    void params_process(const settings * sets, configs * cfgs) {

        params_dsr_hops_in(sets, cfgs->dsr_hops_in_config);
        params_dsr_targets_in(sets, cfgs->dsr_targets_in_config);

        params_msg_hops_in(sets, cfgs->msg_hops_in_config);
        params_mod_stft_in(sets, cfgs->mod_stft_in_config);
        params_msg_spectra_in(sets, cfgs->msg_spectra_in_config);
        params_msg_targets_in(sets, cfgs->msg_targets_in_config);

        params_mod_tt(sets, cfgs->mod_tt_config);
        params_mod_bf(sets, cfgs->mod_bf_config);

        params_msg_tracks_out(sets, cfgs->msg_tracks_out_config);
        params_msg_spectra_out(sets, cfgs->msg_spectra_out_config);
        params_mod_istft_out(sets, cfgs->mod_istft_out_config);
        params_msg_hops_out(sets, cfgs->msg_hops_out_config);

        params_ser_hops_out(sets, cfgs->ser_hops_out_config);
        params_ser_tracks_out(sets, cfgs->ser_tracks_out_config);

    }

    void params_dsr_hops_in(const settings * sets, dsr_hops_cfg * cfg) {

        // Nothing to do

    }

    void params_dsr_targets_in(const settings * sets, dsr_targets_cfg * cfg) {

        // Nothing to do

    }

    void params_msg_hops_in(const settings * sets, msg_hops_cfg * cfg) {

        cfg->hopSize = sets->general.size.hopSize;
        cfg->nChannels = sets->general.mics.N;
        cfg->fS = sets->general.samplerate.mu;

    }

    void params_mod_stft_in(const settings * sets, mod_stft_cfg * cfg) {       

        // Nothing to do

    }

    void params_msg_spectra_in(const settings * sets, msg_spectra_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->general.mics.N;
        cfg->fS = sets->general.samplerate.mu;

    }

    void params_msg_targets_in(const settings * sets, msg_targets_cfg * cfg) {

        cfg->nTargets = sets->bf.nSrcs;
        cfg->fS = sets->general.samplerate.mu;

    }

    void params_mod_tt(const settings * sets, mod_tt_cfg * cfg) {

        // Nothing to do

    }

    void params_mod_bf(const settings * sets, mod_bf_cfg * cfg) {

        unsigned int n;
        unsigned int d;

        if (strcmp(sets->bf.mode, "dds") == 0) {

            cfg->mode = 'd';

        }
        else {

            printf("Bf: Invalid mode");
            exit(EXIT_FAILURE);

        }

        cfg->nThetas = sets->general.nThetas;
        cfg->gainMin = sets->general.gainMin;
        cfg->epsilon = sets->general.epsilon;

        cfg->mics = mics_construct_zero(sets->general.mics.N);

        for (n = 0; n < sets->general.mics.N; n++) {

            for (d = 0; d < 3; d++) {
                cfg->mics->mu[n*3 + d] = sets->general.mics.array[n].mu[d];
            }

            for (d = 0; d < 9; d++) {
                cfg->mics->sigma2[n*9 + d] = sets->general.mics.array[n].sigma2[d];
            }

            for (d = 0; d < 3; d++) {
                cfg->mics->direction[n*3 + d] = sets->general.mics.array[n].direction[d];
            }

            cfg->mics->thetaAllPass[n] = sets->general.mics.array[n].angle[0];
            cfg->mics->thetaNoPass[n] = sets->general.mics.array[n].angle[1];

        }

        cfg->samplerate = samplerate_construct_zero();
        cfg->samplerate->mu = sets->general.samplerate.mu;
        cfg->samplerate->sigma2 = sets->general.samplerate.sigma2;

        cfg->soundspeed = soundspeed_construct_zero();
        cfg->soundspeed->mu = sets->general.speedofsound.mu;
        cfg->soundspeed->sigma2 = sets->general.speedofsound.sigma2;

    }

    void params_msg_tracks_out(const settings * sets, msg_tracks_cfg * cfg) {

        cfg->nTracks = sets->bf.nSrcs;
        cfg->fS = sets->general.samplerate.mu;

    }

    void params_msg_spectra_out(const settings * sets, msg_spectra_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->bf.nSrcs;
        cfg->fS = sets->general.samplerate.mu;

    }

    void params_mod_istft_out(const settings * sets, mod_istft_cfg * cfg) {

        // Nothing to do

    }

    void params_msg_hops_out(const settings * sets, msg_hops_cfg * cfg) {

        cfg->hopSize = sets->general.size.hopSize;
        cfg->nChannels = sets->bf.nSrcs;
        cfg->fS = sets->general.samplerate.mu;        

    }

    void params_ser_hops_out(const settings * sets, ser_hops_cfg * cfg) {

        // Nothing to do

    }

    void params_ser_tracks_out(const settings * sets, ser_tracks_cfg * cfg) {

        // Nothing to do

    }