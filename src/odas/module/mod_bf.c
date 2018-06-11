    
   /**
    * \file     mod_bf.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-29
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
    
    #include <module/mod_bf.h>

    #include <stdio.h>

    mod_bf_obj * mod_bf_construct(const mod_bf_cfg * mod_bf_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_bf_obj * obj;
        
        obj = (mod_bf_obj *) malloc(sizeof(mod_bf_obj));

        obj->nSeps = msg_tracks_config->nTracks;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->mode = mod_bf_config->mode;

        switch(obj->mode) {

            case 'd':

                obj->ds_beampatterns_mics = directivity_beampattern_mics(mod_bf_config->mics, 
                                                                         mod_bf_config->nThetas);

                obj->ds_steers = steers_construct_zero(msg_spectra_config->halfFrameSize,
                                                       msg_tracks_config->nTracks,
                                                       msg_spectra_config->nChannels);

                obj->ds_gains = gains_construct_zero(msg_tracks_config->nTracks,
                                                     msg_spectra_config->nChannels);

                obj->ds_masks = masks_construct_zero(msg_tracks_config->nTracks,
                                                     msg_spectra_config->nChannels);

                obj->ds_track2gain = track2gain_construct_zero(msg_tracks_config->nTracks,
                                                               msg_spectra_config->nChannels,
                                                               mod_bf_config->mics->direction);

                obj->ds_gain2mask = gain2mask_construct_zero(msg_tracks_config->nTracks,
                                                             msg_spectra_config->nChannels,
                                                             mod_bf_config->gainMin);

                obj->ds_track2steer = track2steer_construct_zero(msg_tracks_config->nTracks,
                                                                 msg_spectra_config->nChannels,
                                                                 msg_spectra_config->halfFrameSize,
                                                                 mod_bf_config->soundspeed->mu,
                                                                 mod_bf_config->samplerate->mu,
                                                                 mod_bf_config->mics->mu);

                obj->ds_steer2demixing = steer2demixing_ds_construct_zero(msg_tracks_config->nTracks,
                                                                          msg_spectra_config->nChannels,
                                                                          msg_spectra_config->halfFrameSize,
                                                                          mod_bf_config->epsilon);

                obj->ds_demixings = demixings_construct_zero(msg_spectra_config->halfFrameSize,
                                                             msg_tracks_config->nTracks,
                                                             msg_spectra_config->nChannels);

                obj->ds_demixing2freq = demixing2freq_construct_zero(msg_tracks_config->nTracks,
                                                                     msg_spectra_config->nChannels,
                                                                     msg_spectra_config->halfFrameSize);

            break;

            default:

                printf("Bf: Invalid mode\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

        obj->enabled = 0;

        return obj;

    }

    void mod_bf_destroy(mod_bf_obj * obj) {

        switch(obj->mode) {

            case 'd':

                beampatterns_destroy(obj->ds_beampatterns_mics);
                steers_destroy(obj->ds_steers);
                gains_destroy(obj->ds_gains);
                masks_destroy(obj->ds_masks);
                track2gain_destroy(obj->ds_track2gain);
                gain2mask_destroy(obj->ds_gain2mask);
                track2steer_destroy(obj->ds_track2steer);
                steer2demixing_ds_destroy(obj->ds_steer2demixing);
                demixings_destroy(obj->ds_demixings);
                demixing2freq_destroy(obj->ds_demixing2freq);

            break;        

            default:

                printf("Bf: Invalid mode\n");
                exit(EXIT_FAILURE);

            break;

        }

        free((void *) obj);

    }

    int mod_bf_process(mod_bf_obj * obj) {

        int rtnValue;

        switch(obj->mode) {

            case 'd':

                rtnValue = mod_bf_process_dds(obj);

            break;

            default:

                printf("Bf: invalid mode\n");
                exit(EXIT_FAILURE);

            break;

        }

        return rtnValue;

    }

    int mod_bf_process_dds(mod_bf_obj * obj) {

        int rtnValue;

        if (obj->in1->timeStamp != obj->in2->timeStamp) {

            printf("Time stamp mismatch.\n");
            exit(EXIT_FAILURE);

        }

        if (msg_spectra_isZero(obj->in1) == 0) {

            if (obj->enabled == 1) {

                track2gain_process(obj->ds_track2gain, 
                                   obj->ds_beampatterns_mics, 
                                   obj->in2->tracks,
                                   obj->ds_gains);
  
                gain2mask_process(obj->ds_gain2mask, 
                                  obj->ds_gains, 
                                  obj->ds_masks);

                track2steer_process(obj->ds_track2steer, 
                                    obj->in2->tracks,
                                    obj->ds_gains,
                                    obj->ds_masks,
                                    obj->ds_steers);

                steer2demixing_ds_process(obj->ds_steer2demixing, 
                                          obj->in2->tracks,
                                          obj->ds_steers, 
                                          obj->ds_masks, 
                                          obj->ds_demixings);

                demixing2freq_process(obj->ds_demixing2freq, 
                                      obj->in2->tracks,
                                      obj->ds_demixings, 
                                      obj->ds_masks, 
                                      obj->in1->freqs, 
                                      obj->out->freqs);

            }
            else {

                freqs_zero(obj->out->freqs);

            }

            obj->out->timeStamp = obj->in1->timeStamp;
            
            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;           

    }

    void mod_bf_connect(mod_bf_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;

    }

    void mod_bf_disconnect(mod_bf_obj * obj) {

        obj->in1 = (msg_spectra_obj *) NULL;
        obj->in2 = (msg_tracks_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

    }

    void mod_bf_enable(mod_bf_obj * obj) {

        obj->enabled = 1;

    }

    void mod_bf_disable(mod_bf_obj * obj) {

        obj->enabled = 0;

    }

    mod_bf_cfg * mod_bf_cfg_construct(void) {

        mod_bf_cfg * cfg;

        cfg = (mod_bf_cfg *) malloc(sizeof(mod_bf_cfg));

        return cfg;

    }

    void mod_bf_cfg_destroy(mod_bf_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_bf_cfg_printf(const mod_bf_cfg * cfg) {

        unsigned int iChannel;

        if (cfg != NULL) {

            printf("mod_bf_cfg (%p)\n", cfg);
            printf(" + mode = %c\n", cfg->mode);
            printf(" + nThetas = %u\n", cfg->nThetas);
            printf(" + gainMin = %f\n", cfg->gainMin);
            printf(" + epsilon = %f\n", cfg->epsilon);

            printf(" + mics (%p)\n", cfg->mics);

            for (iChannel = 0; iChannel < cfg->mics->nChannels; iChannel++) {

                printf("    + %u mu = (%f, %f, %f)\n", iChannel, 
                        cfg->mics->mu[iChannel*3+0], cfg->mics->mu[iChannel*3+1], cfg->mics->mu[iChannel*3+2]);
                printf("    + %u sigma2 = (%f, %f, %f, %f, %f, %f, %f, %f, %f)\n", iChannel, 
                        cfg->mics->sigma2[iChannel*9+0], cfg->mics->sigma2[iChannel*9+1], cfg->mics->sigma2[iChannel*9+2],
                        cfg->mics->sigma2[iChannel*9+3], cfg->mics->sigma2[iChannel*9+4], cfg->mics->sigma2[iChannel*9+5],
                        cfg->mics->sigma2[iChannel*9+6], cfg->mics->sigma2[iChannel*9+7], cfg->mics->sigma2[iChannel*9+8]);
                printf("    + %u direction = (%f, %f, %f)\n", iChannel,
                        cfg->mics->direction[iChannel*3+0], cfg->mics->direction[iChannel*3+1], cfg->mics->direction[iChannel*3+2]);
                printf("    + %u thetaAllPass = %f\n", iChannel,
                        cfg->mics->thetaAllPass[iChannel]);
                printf("    + %u thetaNoPass = %f\n", iChannel,
                        cfg->mics->thetaNoPass[iChannel]);

            }

            printf(" + samplerate (%p)\n", cfg->samplerate);
            printf("    + mu = %u\n", cfg->samplerate->mu);
            printf("    + sigma2 = %f\n", cfg->samplerate->sigma2);

            printf(" + soundspeed (%p)\n", cfg->soundspeed);
            printf("    + mu = %f\n", cfg->soundspeed->mu);
            printf("    + sigma2 = %f\n", cfg->soundspeed->sigma2);

        }
        else {

            printf("mod_bf_cfg (null)\n");

        }

    }
