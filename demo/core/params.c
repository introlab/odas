
	#include "params.h"

    void params_process(const settings * sets, const sockets * scks, configs * cfgs) {

    	params_process_src_hops(scks, cfgs->src_hops_config);
    	params_process_msg_hops(sets, cfgs->msg_hops_config);
        params_process_snk_hops(scks, cfgs->snk_hops_config);

    	params_process_src_targets(scks, cfgs->src_targets_config);
    	params_process_msg_targets(sets, cfgs->msg_targets_config);
        params_process_snk_targets(scks, cfgs->snk_targets_config);

        params_process_mod_stft(sets, cfgs->mod_stft_config);
        params_process_msg_spectra(sets, cfgs->msg_spectra_config);

        params_process_mod_ssl(sets, cfgs->mod_ssl_config);
        params_process_msg_pots(sets, cfgs->msg_pots_config);
        params_process_snk_pots(scks, cfgs->snk_pots_config);

        params_process_mod_sst(sets, cfgs->mod_sst_config);
        params_process_msg_tracks(sets, cfgs->msg_tracks_config);
        params_process_snk_tracks(scks, cfgs->snk_tracks_config);

        params_process_mod_lag(sets, cfgs->mod_lag_config);
        params_process_msg_spectra_delay(sets, cfgs->msg_spectra_delay_config);
        params_process_mod_noise_delay(sets, cfgs->mod_noise_delay_config);
        params_process_msg_powers_delay(sets, cfgs->msg_powers_delay_config);

        params_process_mod_sss(sets, cfgs->mod_sss_config);
        
        params_process_msg_spectra_sep(sets, cfgs->msg_spectra_sep_config);
        params_process_mod_istft_sep(sets, cfgs->mod_istft_sep_config);
        params_process_msg_hops_sep(sets, cfgs->msg_hops_sep_config);
        params_process_snk_hops_sep(scks, cfgs->snk_hops_sep_config);

        params_process_msg_spectra_pf(sets, cfgs->msg_spectra_pf_config);
        params_process_mod_istft_pf(sets, cfgs->mod_istft_pf_config);
        params_process_msg_hops_pf(sets, cfgs->msg_hops_pf_config);
        params_process_snk_hops_pf(scks, cfgs->snk_hops_pf_config);

    }

    void params_process_src_hops(const sockets * scks, src_hops_cfg * cfg) {

        cfg->port = scks->raw;

    }

    void params_process_msg_hops(const settings * sets, msg_hops_cfg * cfg) {

        cfg->hopSize = sets->general.size.hopSize;
        cfg->nChannels = sets->general.mics.N;

    }
    
    void params_process_snk_hops(const sockets * scks, snk_hops_cfg * cfg) {

        cfg->port = 0;

    }

    void params_process_src_targets(const sockets * scks, src_targets_cfg * cfg) {

        cfg->port = scks->targets;

    }

    void params_process_msg_targets(const settings * sets, msg_targets_cfg * cfg) {

        cfg->nTargets = sets->sst.levels.lInactive.N;

    }

    void params_process_snk_targets(const sockets * scks, snk_targets_cfg * cfg) {

        cfg->port = 0;

    }

    void params_process_mod_stft(const settings * sets, mod_stft_cfg * cfg) {

        // Nothing to do here

    }

    void params_process_msg_spectra(const settings * sets, msg_spectra_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->general.mics.N;

    }

    void params_process_mod_ssl(const settings * sets, mod_ssl_cfg * cfg) {

        unsigned int iChannel;
        unsigned int iDim;
        unsigned int iSpatialFilter;
        unsigned int iLevel;

        cfg->mics = mics_construct_zero(sets->general.mics.N);

        for (iChannel = 0; iChannel < sets->general.mics.N; iChannel++) {

            for (iDim = 0; iDim < 3; iDim++) {
                cfg->mics->mu[iChannel * 3 + iDim] = sets->general.mics.array[iChannel].mu[iDim];
            }

            for (iDim = 0; iDim < 9; iDim++) {
                cfg->mics->sigma2[iChannel * 9 + iDim] = sets->general.mics.array[iChannel].sigma2[iDim];
            }

            for (iDim = 0; iDim < 3; iDim++) {
                cfg->mics->direction[iChannel * 3 + iDim] = sets->general.mics.array[iChannel].direction[iDim];
            }

            cfg->mics->thetaAllPass[iChannel] = sets->general.mics.array[iChannel].angle[0];
            cfg->mics->thetaNoPass[iChannel] = sets->general.mics.array[iChannel].angle[1];

        }

        cfg->samplerate = samplerate_construct_zero();
        cfg->samplerate->mu = sets->general.samplerate.mu;
        cfg->samplerate->sigma2 = sets->general.samplerate.sigma2;

        cfg->soundspeed = soundspeed_construct_zero();
        cfg->soundspeed->mu = sets->general.speedofsound.mu;
        cfg->soundspeed->sigma2 = sets->general.speedofsound.sigma2;

        cfg->spatialfilters = spatialfilters_construct_zero(sets->general.spatialfilters.N);

        for (iSpatialFilter = 0; iSpatialFilter < sets->general.spatialfilters.N; iSpatialFilter++) {

            for (iDim = 0; iDim < 3; iDim++) {

                cfg->spatialfilters->direction[iSpatialFilter * 3 + iDim] = sets->general.spatialfilters.array[iSpatialFilter].direction[iDim];

            }

            cfg->spatialfilters->thetaAllPass[iSpatialFilter] = sets->general.spatialfilters.array[iSpatialFilter].angle[0];
            cfg->spatialfilters->thetaNoPass[iSpatialFilter] = sets->general.spatialfilters.array[iSpatialFilter].angle[1];

        }

        cfg->interpRate = sets->ssl.interpRate;
        cfg->epsilon = sets->general.epsilon;
        cfg->nLevels = sets->ssl.scans.N;

        cfg->levels = (unsigned int *) malloc(sizeof(unsigned int) * sets->ssl.scans.N);
        cfg->deltas = (signed int *) malloc(sizeof(signed int) * sets->ssl.scans.N);

        for (iLevel = 0; iLevel < sets->ssl.scans.N; iLevel++) {

            cfg->levels[iLevel] = sets->ssl.scans.array[iLevel].level;
            cfg->deltas[iLevel] = sets->ssl.scans.array[iLevel].delta;

        }

        cfg->nMatches = sets->ssl.nMatches;
        cfg->probMin = sets->ssl.probMin;
        cfg->nRefinedLevels = sets->ssl.nRefinedLevels;
        cfg->nThetas = sets->general.nThetas;
        cfg->gainMin = sets->general.gainMin;

    }

    void params_process_msg_pots(const settings * sets, msg_pots_cfg * cfg) {

        cfg->nPots = sets->ssl.nPots;

    }

    void params_process_snk_pots(const sockets * scks, snk_pots_cfg * cfg) {

        cfg->port = scks->pots;

    }

    void params_process_mod_sst(const settings * sets, mod_sst_cfg * cfg) {

        unsigned int iGaussian;
        unsigned int iLevel;

        if (strcmp(sets->sst.mode, "kalman") == 0) {
            cfg->mode = 'k';
        }
        else if (strcmp(sets->sst.mode, "particle") == 0) {
            cfg->mode = 'p';
        }
        else {
            printf("Invalid SST mode\n");
            exit(EXIT_FAILURE);
        }

        if (strcmp(sets->sst.add, "static") == 0) {
            cfg->add = 's';
        }
        else if (strcmp(sets->sst.add, "dynamic") == 0) {
            cfg->add = 'd';
        }
        else {
            printf("Invalid SST add\n");
            exit(EXIT_FAILURE);
        }

        cfg->hopSize = sets->general.size.hopSize;
        cfg->sigmaQ = sets->sst.kalman.sigmaQ;

        cfg->samplerate = samplerate_construct_zero();
        cfg->samplerate->mu = sets->general.samplerate.mu;
        cfg->samplerate->sigma2 = sets->general.samplerate.sigma2;

	    cfg->nParticles = sets->sst.particle.nParticles;
	    cfg->st_alpha = sets->sst.particle.stationary.alpha;
	    cfg->st_beta = sets->sst.particle.stationary.beta;
	    cfg->st_ratio = sets->sst.particle.stationary.ratio;
	    cfg->ve_alpha = sets->sst.particle.velocity.alpha;
	    cfg->ve_beta = sets->sst.particle.velocity.beta;
	    cfg->ve_ratio = sets->sst.particle.velocity.ratio;
	    cfg->ac_alpha = sets->sst.particle.acceleration.alpha;
	    cfg->ac_beta = sets->sst.particle.acceleration.beta;
	    cfg->ac_ratio = sets->sst.particle.acceleration.ratio;
	    cfg->Nmin = sets->sst.particle.Nmin;

	    cfg->epsilon = sets->general.epsilon;
	    cfg->sigmaR_prob = sqrtf(sets->sst.sigmaR2.prob);
	    cfg->sigmaR_active = sqrtf(sets->sst.sigmaR2.active);
        cfg->sigmaR_target = sqrtf(sets->sst.sigmaR2.target);

        cfg->active_gmm = gaussians_1d_construct_null(sets->sst.active.N);

        for (iGaussian = 0; iGaussian < sets->sst.active.N; iGaussian++) {
            
            cfg->active_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(sets->sst.active.array[iGaussian].weight,
                                                                                    sets->sst.active.array[iGaussian].mu,
                                                                                    sqrtf(sets->sst.active.array[iGaussian].sigma2));

        }

        cfg->inactive_gmm = gaussians_1d_construct_null(sets->sst.inactive.N);

        for (iGaussian = 0; iGaussian < sets->sst.inactive.N; iGaussian++) {
            
            cfg->inactive_gmm->array[iGaussian] = gaussian_1d_construct_weightmusigma(sets->sst.inactive.array[iGaussian].weight,
                                                                                      sets->sst.inactive.array[iGaussian].mu,
                                                                                      sqrtf(sets->sst.inactive.array[iGaussian].sigma2));
            
        }

        cfg->Pfalse = sets->sst.P.pFalse;
        cfg->Pnew = sets->sst.P.pNew;
        cfg->Ptrack = sets->sst.P.pTrack;

        cfg->theta_new = sets->sst.levels.lNew.theta;;
        
        cfg->theta_prob = sets->sst.levels.lProb.theta;
        cfg->N_prob = sets->sst.levels.lProb.Ns[0];
        
        cfg->theta_inactive = sets->sst.levels.lInactive.theta;        
        cfg->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * sets->sst.levels.lInactive.N);

        for (iLevel = 0; iLevel < sets->sst.levels.lInactive.N; iLevel++) {
            cfg->N_inactive[iLevel] = sets->sst.levels.lInactive.Ns[iLevel];
        }       

    }

    void params_process_msg_tracks(const settings * sets, msg_tracks_cfg * cfg) {

        cfg->nTracks = sets->sst.levels.lInactive.N;

    }

    void params_process_snk_tracks(const sockets * scks, snk_tracks_cfg * cfg) {

        cfg->port = scks->tracks;

    }

    void params_process_mod_lag(const settings * sets, mod_lag_cfg * cfg) {

        cfg->nElements = sets->sss.offset;

    }

    void params_process_msg_spectra_delay(const settings * sets, msg_spectra_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->general.mics.N;

    }

    void params_process_mod_noise_delay(const settings * sets, mod_noise_cfg * cfg) {

        cfg->bSize = sets->sne.b;
        cfg->alphaS = sets->sne.alphaS;
        cfg->L = sets->sne.L;
        cfg->delta = sets->sne.delta;
        cfg->alphaD = sets->sne.alphaD;

    }

    void params_process_msg_powers_delay(const settings * sets, msg_powers_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->general.mics.N;

    }


    void params_process_mod_sss(const settings * sets, mod_sss_cfg * cfg) {

        unsigned int iChannel;
        unsigned int iDim;

        if (strcmp(sets->sss.separation.mode, "dds") == 0) {
            cfg->mode_sep = 'd';
        }
        else if (strcmp(sets->sss.separation.mode, "dgss") == 0) {
            cfg->mode_sep = 'g';
        }
        else if (strcmp(sets->sss.separation.mode, "dmvdr") == 0) {
            cfg->mode_sep = 'm';
        }
        else {
            cfg->mode_sep = 0x00;
        }

        if (strcmp(sets->sss.postfiltering.mode, "ms") == 0) {
            cfg->mode_pf = 'm';
        }
        else if (strcmp(sets->sss.postfiltering.mode, "ss") == 0) {
            cfg->mode_pf = 's';
        }
        else {
            cfg->mode_pf = 0x00;
        }

        cfg->nThetas = sets->general.nThetas;
        cfg->gainMin = sets->general.gainMin;

        cfg->epsilon = sets->general.epsilon;

        cfg->mics = mics_construct_zero(sets->general.mics.N);

        for (iChannel = 0; iChannel < sets->general.mics.N; iChannel++) {

            for (iDim = 0; iDim < 3; iDim++) {
                cfg->mics->mu[iChannel * 3 + iDim] = sets->general.mics.array[iChannel].mu[iDim];
            }

            for (iDim = 0; iDim < 9; iDim++) {
                cfg->mics->sigma2[iChannel * 9 + iDim] = sets->general.mics.array[iChannel].sigma2[iDim];
            }

            for (iDim = 0; iDim < 3; iDim++) {
                cfg->mics->direction[iChannel * 3 + iDim] = sets->general.mics.array[iChannel].direction[iDim];
            }

            cfg->mics->thetaAllPass[iChannel] = sets->general.mics.array[iChannel].angle[0];
            cfg->mics->thetaNoPass[iChannel] = sets->general.mics.array[iChannel].angle[1];

        }

        cfg->samplerate = samplerate_construct_zero();
        cfg->samplerate->mu = sets->general.samplerate.mu;
        cfg->samplerate->sigma2 = sets->general.samplerate.sigma2;

        cfg->soundspeed = soundspeed_construct_zero();
        cfg->soundspeed->mu = sets->general.speedofsound.mu;
        cfg->soundspeed->sigma2 = sets->general.speedofsound.sigma2;

        cfg->sep_gss_lambda = sets->sss.separation.techniques.dgss.lambda;
        cfg->sep_gss_mu = sets->sss.separation.techniques.dgss.mu;

        cfg->pf_ms_bSize = sets->sne.b;
        cfg->pf_ms_alphaS = sets->sne.alphaS;
        cfg->pf_ms_L = sets->sne.L;
        cfg->pf_ms_delta = sets->sne.delta;
        cfg->pf_ms_alphaD = sets->sne.alphaD;

        cfg->pf_ms_eta = sets->sss.postfiltering.techniques.ms.eta;
        cfg->pf_ms_alphaZ = sets->sss.postfiltering.techniques.ms.alphaZ;
        cfg->pf_ms_alphaPmin = sets->sss.postfiltering.techniques.ms.alphaPmin;
        cfg->pf_ms_thetaWin = sets->sss.postfiltering.techniques.ms.thetaWin;
        cfg->pf_ms_alphaWin = sets->sss.postfiltering.techniques.ms.alphaWin;
        cfg->pf_ms_maxAbsenceProb = sets->sss.postfiltering.techniques.ms.maxAbsenceProb;
        cfg->pf_ms_Gmin = sets->sss.postfiltering.techniques.ms.Gmin;
        cfg->pf_ms_winSizeLocal = sets->sss.postfiltering.techniques.ms.winSizeLocal;
        cfg->pf_ms_winSizeGlobal = sets->sss.postfiltering.techniques.ms.winSizeGlobal;
        cfg->pf_ms_winSizeFrame = sets->sss.postfiltering.techniques.ms.winSizeFrame;

        cfg->pf_ss_Gmin = sets->sss.postfiltering.techniques.ss.Gmin;
        cfg->pf_ss_Gmid = sets->sss.postfiltering.techniques.ss.Gmid;
        cfg->pf_ss_Gslope = sets->sss.postfiltering.techniques.ss.Gslope;

    }

    void params_process_msg_spectra_sep(const settings * sets, msg_spectra_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->sst.levels.lInactive.N;

    }

    void params_process_mod_istft_sep(const settings * sets, mod_istft_cfg * cfg) {

        // Nothing to do here

    }

    void params_process_msg_hops_sep(const settings * sets, msg_hops_cfg * cfg) {

        cfg->hopSize = sets->general.size.hopSize;
        cfg->nChannels = sets->sst.levels.lInactive.N;

    }

    void params_process_snk_hops_sep(const sockets * scks, snk_hops_cfg * cfg) {
     
        cfg->port = scks->seps;

    }

    void params_process_snk_hopstracks_sep(const sockets * scks, snk_hopstracks_cfg * cfg) {

        cfg->port = scks->iseps;

    }

    void params_process_msg_spectra_pf(const settings * sets, msg_spectra_cfg * cfg) {

        cfg->halfFrameSize = sets->general.size.frameSize / 2 + 1;
        cfg->nChannels = sets->sst.levels.lInactive.N;

    }

    void params_process_mod_istft_pf(const settings * sets, mod_istft_cfg * cfg) {

        // Nothing to do here

    }

    void params_process_msg_hops_pf(const settings * sets, msg_hops_cfg * cfg) {

        cfg->hopSize = sets->general.size.hopSize;
        cfg->nChannels = sets->sst.levels.lInactive.N;

    }

    void params_process_snk_hops_pf(const sockets * scks, snk_hops_cfg * cfg) {
        
        cfg->port = scks->pfs;

    }

    void params_process_snk_hopstracks_pf(const sockets * scks, snk_hopstracks_cfg * cfg) {

        cfg->port = scks->ipfs;

    }

