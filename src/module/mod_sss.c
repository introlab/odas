
   /**
    * \file     mod_sss.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <module/mod_sss.h>

    #include <stdio.h>

    FILE * fidTmp1;
    FILE * fidTmp2;

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_sss_obj * obj;
        
        obj = (mod_sss_obj *) malloc(sizeof(mod_sss_obj));

        obj->nSeps = msg_tracks_config->nTracks;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->mode_sep = mod_sss_config->mode_sep;
        obj->mode_pf = mod_sss_config->mode_pf;

        obj->sep_ds_beampatterns_mics = (beampatterns_obj *) NULL;
        obj->sep_ds_steers = (steers_obj *) NULL;
        obj->sep_ds_gains = (gains_obj *) NULL;
        obj->sep_ds_masks = (masks_obj *) NULL;
        obj->sep_ds_tracksPrev = (tracks_obj *) NULL;
        obj->sep_ds_tracksNow = (tracks_obj *) NULL;
        obj->sep_ds_track2gain = (track2gain_obj *) NULL;
        obj->sep_ds_gain2mask = (gain2mask_obj *) NULL;
        obj->sep_ds_track2steer = (track2steer_obj *) NULL;
        obj->sep_ds_steer2demixing = (steer2demixing_ds_obj *) NULL;
        obj->sep_ds_demixingsPrev = (demixings_obj *) NULL;
        obj->sep_ds_demixingsNow = (demixings_obj *) NULL;
        obj->sep_ds_demixing2freq = (demixing2freq_obj *) NULL;

        obj->sep_gss_beampatterns_mics = (beampatterns_obj *) NULL;
        obj->sep_gss_steers = (steers_obj *) NULL;
        obj->sep_gss_gains = (gains_obj *) NULL;
        obj->sep_gss_masks = (masks_obj *) NULL;
        obj->sep_gss_tracksPrev = (tracks_obj *) NULL;
        obj->sep_gss_tracksNow = (tracks_obj *) NULL;
        obj->sep_gss_track2gain = (track2gain_obj *) NULL;
        obj->sep_gss_gain2mask = (gain2mask_obj *) NULL;
        obj->sep_gss_track2steer = (track2steer_obj *) NULL;
        obj->sep_gss_steer2demixing = (steer2demixing_gss_obj *) NULL;
        obj->sep_gss_demixingsPrev = (demixings_obj *) NULL;
        obj->sep_gss_demixingsNow = (demixings_obj *) NULL;
        obj->sep_gss_demixing2freq = (demixing2freq_obj *) NULL;        

        switch(obj->mode_sep) {

            case 'd':

                obj->sep_ds_beampatterns_mics = directivity_beampattern_mics(mod_sss_config->mics, 
                                                                             mod_sss_config->nThetas);

                obj->sep_ds_steers = steers_construct_zero(msg_spectra_config->halfFrameSize, 
                                                           msg_tracks_config->nTracks, 
                                                           msg_spectra_config->nChannels);

                obj->sep_ds_gains = gains_construct_zero(msg_tracks_config->nTracks,
                                                         msg_spectra_config->nChannels);

                obj->sep_ds_masks = masks_construct_zero(msg_tracks_config->nTracks, 
                                                         msg_spectra_config->nChannels);

                obj->sep_ds_tracksPrev = tracks_construct_zero(msg_tracks_config->nTracks);

                obj->sep_ds_tracksNow = tracks_construct_zero(msg_tracks_config->nTracks);

                obj->sep_ds_track2gain = track2gain_construct_zero(msg_tracks_config->nTracks,
                                                                   msg_spectra_config->nChannels,
                                                                   mod_sss_config->mics->direction);

                obj->sep_ds_gain2mask = gain2mask_construct_zero(msg_tracks_config->nTracks,
                                                                 msg_spectra_config->nChannels,
                                                                 mod_sss_config->gainMin);

                obj->sep_ds_track2steer = track2steer_construct_zero(msg_tracks_config->nTracks, 
                                                                     msg_spectra_config->nChannels, 
                                                                     msg_spectra_config->halfFrameSize, 
                                                                     mod_sss_config->soundspeed->mu,
                                                                     mod_sss_config->samplerate->mu,
                                                                     mod_sss_config->mics->mu);

                obj->sep_ds_steer2demixing = steer2demixing_ds_construct_zero(msg_tracks_config->nTracks, 
                                                                              msg_spectra_config->nChannels, 
                                                                              msg_spectra_config->halfFrameSize, 
                                                                              mod_sss_config->epsilon);

                obj->sep_ds_demixingsPrev = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                                     msg_tracks_config->nTracks, 
                                                                     msg_spectra_config->nChannels);

                obj->sep_ds_demixingsNow = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                                    msg_tracks_config->nTracks, 
                                                                    msg_spectra_config->nChannels);

                obj->sep_ds_demixing2freq = demixing2freq_construct_zero(msg_tracks_config->nTracks,
                                                                         msg_spectra_config->nChannels,
                                                                         msg_spectra_config->halfFrameSize);

            break;

            case 'g':

                obj->sep_gss_beampatterns_mics = directivity_beampattern_mics(mod_sss_config->mics, 
                                                                              mod_sss_config->nThetas);

                obj->sep_gss_steers = steers_construct_zero(msg_spectra_config->halfFrameSize, 
                                                            msg_tracks_config->nTracks, 
                                                            msg_spectra_config->nChannels);

                obj->sep_gss_gains = gains_construct_zero(msg_tracks_config->nTracks,
                                                          msg_spectra_config->nChannels);

                obj->sep_gss_masks = masks_construct_zero(msg_tracks_config->nTracks, 
                                                          msg_spectra_config->nChannels);

                obj->sep_gss_tracksPrev = tracks_construct_zero(msg_tracks_config->nTracks);

                obj->sep_gss_tracksNow = tracks_construct_zero(msg_tracks_config->nTracks);

                obj->sep_gss_track2gain = track2gain_construct_zero(msg_tracks_config->nTracks,
                                                                    msg_spectra_config->nChannels,
                                                                    mod_sss_config->mics->direction);

                obj->sep_gss_gain2mask = gain2mask_construct_zero(msg_tracks_config->nTracks,
                                                                  msg_spectra_config->nChannels,
                                                                  mod_sss_config->gainMin);

                obj->sep_gss_track2steer = track2steer_construct_zero(msg_tracks_config->nTracks, 
                                                                      msg_spectra_config->nChannels, 
                                                                      msg_spectra_config->halfFrameSize, 
                                                                      mod_sss_config->soundspeed->mu,
                                                                      mod_sss_config->samplerate->mu,
                                                                      mod_sss_config->mics->mu);

                obj->sep_gss_steer2demixing = steer2demixing_gss_construct_zero(msg_tracks_config->nTracks, 
                                                                                msg_spectra_config->nChannels, 
                                                                                msg_spectra_config->halfFrameSize, 
                                                                                mod_sss_config->sep_gss_mu, 
                                                                                mod_sss_config->sep_gss_lambda,
                                                                                mod_sss_config->epsilon);

                obj->sep_gss_demixingsPrev = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                                      msg_tracks_config->nTracks, 
                                                                      msg_spectra_config->nChannels);

                obj->sep_gss_demixingsNow = demixings_construct_zero(msg_spectra_config->halfFrameSize, 
                                                                     msg_tracks_config->nTracks, 
                                                                     msg_spectra_config->nChannels);

                obj->sep_gss_demixing2freq = demixing2freq_construct_zero(msg_tracks_config->nTracks,
                                                                          msg_spectra_config->nChannels,
                                                                          msg_spectra_config->halfFrameSize);                

            break;

            default:

                printf("Invalid separation method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->sep_demixings = demixings_construct_zero(msg_spectra_config->halfFrameSize,
                                                      msg_tracks_config->nTracks,
                                                      msg_spectra_config->nChannels);

        obj->sep_masks = masks_construct_zero(msg_tracks_config->nTracks, 
                                              msg_spectra_config->nChannels);

        obj->pf_ms_freq2env = (freq2env_obj *) NULL;
        obj->pf_ms_noisys = (envs_obj *) NULL;
        obj->pf_ms_demixing2env = (demixing2env_obj *) NULL;
        obj->pf_ms_noisesEst = (envs_obj *) NULL;
        obj->pf_ms_env2env_mcra = (env2env_mcra_obj *) NULL;
        obj->pf_ms_noisesSep = (envs_obj *) NULL;
        obj->pf_ms_env2env_interf = (env2env_interf_obj *) NULL;
        obj->pf_ms_interfs = (envs_obj *) NULL;
        obj->pf_ms_env2env_gainspeech = (env2env_gainspeech_obj *) NULL;
        obj->pf_ms_gainspeeches = (envs_obj *) NULL;
        obj->pf_ms_snrs = (envs_obj *) NULL;
        obj->pf_ms_vs = (envs_obj *) NULL;
        obj->pf_ms_env2env_probspeech = (env2env_probspeech_obj *) NULL;
        obj->pf_ms_probspeeches = (envs_obj *) NULL;
        obj->pf_ms_env2env_gainall = (env2env_gainall_obj *) NULL;
        obj->pf_ms_gainalls = (envs_obj *) NULL;
        obj->pf_ms_freq2freq_gain = (freq2freq_gain_obj *) NULL;

        obj->pf_ss_freq2env_channels = (freq2env_obj *) NULL;
        obj->pf_ss_env_channels = (envs_obj *) NULL;
        obj->pf_ss_demixing2env = (demixing2env_obj *) NULL;
        obj->pf_ss_env_channelseps = (envs_obj *) NULL;
        obj->pf_ss_freq2env_seps = (freq2env_obj *) NULL;
        obj->pf_ss_env_seps = (envs_obj *) NULL;
        obj->pf_ss_env2env_gainratio = (env2env_gainratio_obj *) NULL;
        obj->pf_ss_gainratio = (envs_obj *) NULL;
        obj->pf_ss_freq2freq_gain = (freq2freq_gain_obj *) NULL;

        switch(obj->mode_pf) {

            case 'm':

                obj->pf_ms_freq2env = freq2env_construct_zero(msg_spectra_config->halfFrameSize);

                obj->pf_ms_noisys = envs_construct_zero(msg_tracks_config->nTracks,
                                                        msg_spectra_config->halfFrameSize);

                obj->pf_ms_demixing2env = demixing2env_construct_zero(msg_tracks_config->nTracks, 
                                                                      msg_spectra_config->nChannels, 
                                                                      msg_spectra_config->halfFrameSize);

                obj->pf_ms_noisesEst = envs_construct_zero(msg_tracks_config->nTracks, 
                                                           msg_spectra_config->halfFrameSize);

                obj->pf_ms_env2env_mcra = env2env_mcra_construct_zero(msg_tracks_config->nTracks, 
                                                                      msg_spectra_config->halfFrameSize,
                                                                      mod_sss_config->pf_ms_bSize, 
                                                                      mod_sss_config->pf_ms_alphaS, 
                                                                      mod_sss_config->pf_ms_L, 
                                                                      mod_sss_config->pf_ms_delta, 
                                                                      mod_sss_config->pf_ms_alphaD);

                obj->pf_ms_noisesSep = envs_construct_zero(msg_tracks_config->nTracks, 
                                                           msg_spectra_config->halfFrameSize);

                obj->pf_ms_env2env_interf = env2env_interf_construct_zero(msg_tracks_config->nTracks, 
                                                                          msg_spectra_config->halfFrameSize, 
                                                                          mod_sss_config->pf_ms_eta,
                                                                          mod_sss_config->pf_ms_alphaZ);

                obj->pf_ms_interfs = envs_construct_zero(msg_tracks_config->nTracks,
                                                         msg_spectra_config->halfFrameSize);

                obj->pf_ms_env2env_gainspeech = env2env_gainspeech_construct_zero(msg_tracks_config->nTracks,
                                                                                  msg_spectra_config->halfFrameSize,
                                                                                  mod_sss_config->pf_ms_alphaPmin,
                                                                                  mod_sss_config->epsilon);

                obj->pf_ms_gainspeeches = envs_construct_zero(msg_tracks_config->nTracks,
                                                              msg_spectra_config->halfFrameSize);

                obj->pf_ms_snrs = envs_construct_zero(msg_tracks_config->nTracks,
                                                      msg_spectra_config->halfFrameSize);

                obj->pf_ms_vs = envs_construct_zero(msg_tracks_config->nTracks,
                                                    msg_spectra_config->halfFrameSize);

                obj->pf_ms_env2env_probspeech = env2env_probspeech_construct_zero(msg_tracks_config->nTracks,
                                                                                  msg_spectra_config->halfFrameSize, 
                                                                                  mod_sss_config->pf_ms_thetaWin, 
                                                                                  mod_sss_config->pf_ms_alphaWin,
                                                                                  mod_sss_config->pf_ms_maxAbsenceProb, 
                                                                                  mod_sss_config->pf_ms_Gmin, 
                                                                                  mod_sss_config->pf_ms_winSizeLocal, 
                                                                                  mod_sss_config->pf_ms_winSizeGlobal, 
                                                                                  mod_sss_config->pf_ms_winSizeFrame);

                obj->pf_ms_probspeeches = envs_construct_zero(msg_tracks_config->nTracks,
                                                              msg_spectra_config->halfFrameSize);

                obj->pf_ms_env2env_gainall = env2env_gainall_construct_zero(msg_tracks_config->nTracks,
                                                                            msg_spectra_config->halfFrameSize,
                                                                            mod_sss_config->pf_ms_Gmin);

                obj->pf_ms_gainalls = envs_construct_zero(msg_tracks_config->nTracks,
                                                          msg_spectra_config->halfFrameSize);

                obj->pf_ms_freq2freq_gain = freq2freq_gain_construct_zero(msg_spectra_config->halfFrameSize);

            break;

            case 's':

                obj->pf_ss_freq2env_channels = freq2env_construct_zero(msg_spectra_config->halfFrameSize);
                
                obj->pf_ss_env_channels = envs_construct_zero(msg_spectra_config->nChannels,
                                                              msg_spectra_config->halfFrameSize);

                obj->pf_ss_demixing2env = demixing2env_construct_zero(msg_tracks_config->nTracks, 
                                                                      msg_spectra_config->nChannels, 
                                                                      msg_spectra_config->halfFrameSize);

                obj->pf_ss_env_channelseps = envs_construct_zero(msg_tracks_config->nTracks, 
                                                                 msg_spectra_config->halfFrameSize);

                obj->pf_ss_freq2env_seps = freq2env_construct_zero(msg_spectra_config->halfFrameSize);

                obj->pf_ss_env_seps = envs_construct_zero(msg_tracks_config->nTracks,
                                                          msg_spectra_config->halfFrameSize);

                obj->pf_ss_env2env_gainratio = env2env_gainratio_construct_zero(msg_spectra_config->nChannels,
                                                                                msg_tracks_config->nTracks, 
                                                                                msg_spectra_config->halfFrameSize, 
                                                                                mod_sss_config->pf_ss_Gmin, 
                                                                                mod_sss_config->pf_ss_Gmid, 
                                                                                mod_sss_config->pf_ss_Gslope,
                                                                                mod_sss_config->epsilon);

                obj->pf_ss_gainratio = envs_construct_zero(msg_tracks_config->nTracks,
                                                           msg_spectra_config->halfFrameSize);

                obj->pf_ss_freq2freq_gain = freq2freq_gain_construct_zero(msg_spectra_config->halfFrameSize);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_powers_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out1 = (msg_spectra_obj *) NULL;
        obj->out2 = (msg_spectra_obj *) NULL;

        obj->enabled = 0;

        return obj;

    }

    void mod_sss_destroy(mod_sss_obj * obj) {

        switch(obj->mode_sep) {

            case 'd':

                beampatterns_destroy(obj->sep_ds_beampatterns_mics);
                steers_destroy(obj->sep_ds_steers);
                gains_destroy(obj->sep_ds_gains);
                masks_destroy(obj->sep_ds_masks);
                tracks_destroy(obj->sep_ds_tracksPrev);
                tracks_destroy(obj->sep_ds_tracksNow);
                track2gain_destroy(obj->sep_ds_track2gain);
                gain2mask_destroy(obj->sep_ds_gain2mask);
                track2steer_destroy(obj->sep_ds_track2steer);
                steer2demixing_ds_destroy(obj->sep_ds_steer2demixing);
                demixings_destroy(obj->sep_ds_demixingsPrev);
                demixings_destroy(obj->sep_ds_demixingsNow);
                demixing2freq_destroy(obj->sep_ds_demixing2freq);

            break;

            case 'g':

                beampatterns_destroy(obj->sep_gss_beampatterns_mics);
                steers_destroy(obj->sep_gss_steers);
                gains_destroy(obj->sep_gss_gains);
                masks_destroy(obj->sep_gss_masks);
                tracks_destroy(obj->sep_gss_tracksPrev);
                tracks_destroy(obj->sep_gss_tracksNow);
                track2gain_destroy(obj->sep_gss_track2gain);
                gain2mask_destroy(obj->sep_gss_gain2mask);
                track2steer_destroy(obj->sep_gss_track2steer);
                steer2demixing_gss_destroy(obj->sep_gss_steer2demixing);
                demixings_destroy(obj->sep_gss_demixingsPrev);
                demixings_destroy(obj->sep_gss_demixingsNow);
                demixing2freq_destroy(obj->sep_gss_demixing2freq);

            break;

            default:

                printf("Invalid separation method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        demixings_destroy(obj->sep_demixings);
        masks_destroy(obj->sep_masks);

        switch(obj->mode_pf) {

            case 'm':

                freq2env_destroy(obj->pf_ms_freq2env);
                envs_destroy(obj->pf_ms_noisys);
                demixing2env_destroy(obj->pf_ms_demixing2env);
                envs_destroy(obj->pf_ms_noisesEst);
                env2env_mcra_destroy(obj->pf_ms_env2env_mcra);
                envs_destroy(obj->pf_ms_noisesSep);
                env2env_interf_destroy(obj->pf_ms_env2env_interf);
                envs_destroy(obj->pf_ms_interfs);
                env2env_gainspeech_destroy(obj->pf_ms_env2env_gainspeech);
                envs_destroy(obj->pf_ms_gainspeeches);
                envs_destroy(obj->pf_ms_snrs);
                envs_destroy(obj->pf_ms_vs);
                env2env_probspeech_destroy(obj->pf_ms_env2env_probspeech);
                envs_destroy(obj->pf_ms_probspeeches);
                env2env_gainall_destroy(obj->pf_ms_env2env_gainall);
                envs_destroy(obj->pf_ms_gainalls);
                freq2freq_gain_destroy(obj->pf_ms_freq2freq_gain);

            break;

            case 's':

                freq2env_destroy(obj->pf_ss_freq2env_channels);
                envs_destroy(obj->pf_ss_env_channels);
                demixing2env_destroy(obj->pf_ss_demixing2env);
                envs_destroy(obj->pf_ss_env_channelseps);
                freq2env_destroy(obj->pf_ss_freq2env_seps);
                envs_destroy(obj->pf_ss_env_seps);
                env2env_gainratio_destroy(obj->pf_ss_env2env_gainratio);
                envs_destroy(obj->pf_ss_gainratio);
                freq2freq_gain_destroy(obj->pf_ss_freq2freq_gain);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        free((void *) obj);

    }

    int mod_sss_process(mod_sss_obj * obj) {

        int rtnValue1;
        int rtnValue2;
        int rtnValue;

        switch(obj->mode_sep) {

            case 'd':

                rtnValue1 = mod_sss_process_dds(obj);

            break;

            case 'g':

                rtnValue1 = mod_sss_process_dgss(obj);

            break;

            default:

                printf("Invalid separation method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        switch(obj->mode_pf) {

            case 'm':

                rtnValue2 = mod_sss_process_mspf(obj);

            break;

            case 's':
            
                rtnValue2 = mod_sss_process_sspf(obj);

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }        

        if (rtnValue1 != rtnValue2) {
            printf("Return value mismatch.\n");
            exit(EXIT_FAILURE);
        }
        else {
            rtnValue = rtnValue1;
        }

        return rtnValue;

    }

    int mod_sss_process_dds(mod_sss_obj * obj) {

        int rtnValue;

        if ((obj->in1->timeStamp != obj->in2->timeStamp) ||
            (obj->in1->timeStamp != obj->in3->timeStamp)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            if (obj->enabled == 1) {

                tracks_copy(obj->sep_ds_tracksPrev,
                            obj->sep_ds_tracksNow);

                tracks_copy(obj->sep_ds_tracksNow,
                            obj->in3->tracks);

                track2gain_process(obj->sep_ds_track2gain, 
                                   obj->sep_ds_beampatterns_mics, 
                                   obj->sep_ds_tracksNow,
                                   obj->sep_ds_gains);
  
                gain2mask_process(obj->sep_ds_gain2mask, 
                                  obj->sep_ds_gains, 
                                  obj->sep_ds_masks);

                track2steer_process(obj->sep_ds_track2steer, 
                                    obj->sep_ds_tracksNow,
                                    obj->sep_ds_gains,
                                    obj->sep_ds_masks,
                                    obj->sep_ds_steers);

                demixings_copy(obj->sep_ds_demixingsPrev, 
                               obj->sep_ds_demixingsNow);

                steer2demixing_ds_process(obj->sep_ds_steer2demixing, 
                                          obj->sep_ds_tracksNow,
                                          obj->sep_ds_steers, 
                                          obj->sep_ds_masks, 
                                          obj->sep_ds_demixingsNow);

                demixing2freq_process(obj->sep_ds_demixing2freq, 
                                      obj->sep_ds_tracksNow,
                                      obj->sep_ds_demixingsNow, 
                                      obj->sep_ds_masks, 
                                      obj->in1->freqs, 
                                      obj->out1->freqs);

                demixings_copy(obj->sep_demixings,
                               obj->sep_ds_demixingsNow);

                masks_copy(obj->sep_masks,
                           obj->sep_ds_masks);

            }
            else {

                masks_zero(obj->sep_masks);

            }

            obj->out1->timeStamp = obj->in1->timeStamp;
            
            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);

            rtnValue = -1;

        }

        return rtnValue;        

    }

    int mod_sss_process_dgss(mod_sss_obj * obj) {

        int rtnValue;

        if ((obj->in1->timeStamp != obj->in2->timeStamp) ||
            (obj->in1->timeStamp != obj->in3->timeStamp)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            if (obj->enabled == 1) {
  
                tracks_copy(obj->sep_gss_tracksPrev,
                            obj->sep_gss_tracksNow);

                tracks_copy(obj->sep_gss_tracksNow,
                            obj->in3->tracks);

                track2gain_process(obj->sep_gss_track2gain, 
                                   obj->sep_gss_beampatterns_mics,
                                   obj->sep_gss_tracksNow,
                                   obj->sep_gss_gains);

                gain2mask_process(obj->sep_gss_gain2mask, 
                                  obj->sep_gss_gains, 
                                  obj->sep_gss_masks);

                track2steer_process(obj->sep_gss_track2steer, 
                                    obj->sep_gss_tracksNow,
                                    obj->sep_gss_gains,
                                    obj->sep_gss_masks,
                                    obj->sep_gss_steers);

                demixings_copy(obj->sep_gss_demixingsPrev,
                               obj->sep_gss_demixingsNow);

                steer2demixing_gss_process(obj->sep_gss_steer2demixing, 
                                           obj->sep_gss_tracksPrev, 
                                           obj->sep_gss_tracksNow, 
                                           obj->sep_gss_steers, 
                                           obj->sep_gss_masks, 
                                           obj->in1->freqs,
                                           obj->sep_gss_demixingsPrev,
                                           obj->sep_gss_demixingsNow);

                demixing2freq_process(obj->sep_gss_demixing2freq, 
                                      obj->sep_gss_tracksNow,
                                      obj->sep_gss_demixingsNow, 
                                      obj->sep_gss_masks, 
                                      obj->in1->freqs, 
                                      obj->out1->freqs);        

                demixings_copy(obj->sep_demixings,
                               obj->sep_gss_demixingsNow);

                masks_copy(obj->sep_masks,
                           obj->sep_gss_masks);            
              
            }
            else {

                masks_zero(obj->sep_masks);

            }          
          
            obj->out1->timeStamp = obj->in1->timeStamp;
            
            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out1);

            rtnValue = -1;

        }

        return rtnValue;       

    }

    int mod_sss_process_mspf(mod_sss_obj * obj) {

        int rtnValue;

        if ((obj->in1->timeStamp != obj->in2->timeStamp) ||
            (obj->in1->timeStamp != obj->in3->timeStamp)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            if (obj->enabled == 1) {

                freq2env_process(obj->pf_ms_freq2env,
                                 obj->out1->freqs,
                                 obj->pf_ms_noisys);

                demixing2env_process(obj->pf_ms_demixing2env,
                                     obj->in3->tracks, 
                                     obj->sep_demixings, 
                                     obj->sep_masks, 
                                     obj->in2->envs,
                                     obj->pf_ms_noisesEst);

                env2env_mcra_process(obj->pf_ms_env2env_mcra, 
                                     obj->in3->tracks, 
                                     obj->pf_ms_noisys, 
                                     obj->pf_ms_noisesEst,
                                     obj->pf_ms_noisesSep);

                env2env_interf_process(obj->pf_ms_env2env_interf, 
                                       obj->in3->tracks, 
                                       obj->pf_ms_noisys, 
                                       obj->pf_ms_noisesSep, 
                                       obj->pf_ms_interfs);           

                env2env_gainspeech_process(obj->pf_ms_env2env_gainspeech, 
                                           obj->in3->tracks, 
                                           obj->pf_ms_noisys, 
                                           obj->pf_ms_interfs, 
                                           obj->pf_ms_gainspeeches, 
                                           obj->pf_ms_snrs, 
                                           obj->pf_ms_vs);

                env2env_probspeech_process(obj->pf_ms_env2env_probspeech, 
                                           obj->in3->tracks,
                                           obj->pf_ms_snrs, 
                                           obj->pf_ms_vs, 
                                           obj->pf_ms_probspeeches);

                env2env_gainall_process(obj->pf_ms_env2env_gainall, 
                                        obj->in3->tracks, 
                                        obj->pf_ms_gainspeeches, 
                                        obj->pf_ms_probspeeches, 
                                        obj->pf_ms_gainalls);

                freq2freq_gain_process(obj->pf_ms_freq2freq_gain, 
                                       obj->out1->freqs, 
                                       obj->pf_ms_gainalls,
                                       obj->out2->freqs);

            }
            else {

                freqs_zero(obj->out2->freqs);

            }

            obj->out2->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;  

    }

    int mod_sss_process_sspf(mod_sss_obj * obj) {

        int rtnValue;

        if ((obj->in1->timeStamp != obj->in2->timeStamp) ||
            (obj->in1->timeStamp != obj->in3->timeStamp)) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {
 
            if (obj->enabled == 1) {

                freq2env_process(obj->pf_ss_freq2env_channels,
                                 obj->in1->freqs,
                                 obj->pf_ss_env_channels);

                demixing2env_process(obj->pf_ss_demixing2env,
                                     obj->in3->tracks, 
                                     obj->sep_demixings, 
                                     obj->sep_masks, 
                                     obj->pf_ss_env_channels,
                                     obj->pf_ss_env_channelseps);   

                freq2env_process(obj->pf_ss_freq2env_seps,
                                 obj->out1->freqs,
                                 obj->pf_ss_env_seps);         

                env2env_gainratio_process(obj->pf_ss_env2env_gainratio, 
                                          obj->in3->tracks, 
                                          obj->pf_ss_env_seps, 
                                          obj->pf_ss_env_channelseps,
                                          obj->pf_ss_gainratio);

                freq2freq_gain_process(obj->pf_ss_freq2freq_gain, 
                                       obj->out1->freqs, 
                                       obj->pf_ss_gainratio,
                                       obj->out2->freqs);

            }
            else {

                freqs_zero(obj->out2->freqs);

            }

            obj->out2->timeStamp = obj->in1->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out2);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_powers_obj * in2, msg_tracks_obj * in3, msg_spectra_obj * out1, msg_spectra_obj * out2) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->in3 = in3;
        obj->out1 = out1;
        obj->out2 = out2;

    }

    void mod_sss_disconnect(mod_sss_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_powers_obj *) NULL;
        obj->in3 = (msg_tracks_obj *) NULL;
        obj->out1 = (msg_spectra_obj *) NULL;
        obj->out2 = (msg_spectra_obj *) NULL;

    }

    void mod_sss_enable(mod_sss_obj * obj) {

        obj->enabled = 1;

    }

    void mod_sss_disable(mod_sss_obj * obj) {

        obj->enabled = 0;

    }

    mod_sss_cfg * mod_sss_cfg_construct(void) {

        mod_sss_cfg * cfg;

        cfg = (mod_sss_cfg *) malloc(sizeof(mod_sss_cfg));

        cfg->mode_sep = 0x00;
        cfg->mode_pf = 0x00;

        cfg->nThetas = 0;
        cfg->gainMin = 0.0f;

        cfg->mics = (mics_obj *) NULL;
        cfg->samplerate = (samplerate_obj *) NULL;
        cfg->soundspeed = (soundspeed_obj *) NULL;

        return cfg;

    }

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg) {

        if (cfg->mics != NULL) {
            mics_destroy(cfg->mics);
        }

        if (cfg->samplerate != NULL) {
            samplerate_destroy(cfg->samplerate);
        }

        if (cfg->soundspeed != NULL) {
            soundspeed_destroy(cfg->soundspeed);
        }

        free((void *) cfg);

    }

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg) {
        
        // Empty

    }
