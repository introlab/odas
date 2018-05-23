
   /**
    * \file     mod_ssl.c
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
    
    #include <module/mod_ssl.h>

    mod_ssl_obj * mod_ssl_construct(const mod_ssl_cfg * mod_ssl_config, const msg_spectra_cfg * msg_spectra_config, const msg_pots_cfg * msg_pots_config) {

        mod_ssl_obj * obj;
        unsigned int iLevel;
        unsigned int iPot;

        points_obj * points;

        obj = (mod_ssl_obj *) malloc(sizeof(mod_ssl_obj));

        obj->nChannels = mod_ssl_config->mics->nChannels;
        obj->nPairs = obj->nChannels * (obj->nChannels - 1) / 2;
        obj->nPots = msg_pots_config->nPots;
        obj->nLevels = mod_ssl_config->nLevels;
        obj->frameSize = 2 * (msg_spectra_config->halfFrameSize - 1);
        obj->halfFrameSize = msg_spectra_config->halfFrameSize; 
        obj->frameSizeInterp = obj->frameSize * mod_ssl_config->interpRate;
        obj->halfFrameSizeInterp = (obj->halfFrameSize - 1) * mod_ssl_config->interpRate + 1;
        obj->interpRate = mod_ssl_config->interpRate;

        obj->scans = scanning_init_scans(mod_ssl_config->mics, 
                                         mod_ssl_config->spatialfilters,
                                         mod_ssl_config->nLevels, 
                                         mod_ssl_config->levels, 
                                         mod_ssl_config->samplerate->mu, 
                                         mod_ssl_config->soundspeed, 
                                         mod_ssl_config->nMatches, 
                                         obj->frameSize, 
                                         mod_ssl_config->deltas,
                                         mod_ssl_config->probMin, 
                                         mod_ssl_config->nRefinedLevels, 
                                         mod_ssl_config->nThetas, 
                                         mod_ssl_config->gainMin,
                                         mod_ssl_config->interpRate);      

        obj->freq2freq_phasor = freq2freq_phasor_construct_zero(obj->halfFrameSize,
                                                                mod_ssl_config->epsilon);

        obj->phasors = freqs_construct_zero(mod_ssl_config->mics->nChannels, 
                                            msg_spectra_config->halfFrameSize);

        obj->freq2freq_product = freq2freq_product_construct_zero(obj->halfFrameSize);

        obj->products = freqs_construct_zero(mod_ssl_config->mics->nPairs, 
                                             msg_spectra_config->halfFrameSize);

        obj->freq2freq_interpolate = freq2freq_interpolate_construct_zero(obj->halfFrameSize,
                                                                          obj->halfFrameSizeInterp);

        obj->productsInterp = freqs_construct_zero(mod_ssl_config->mics->nPairs,
                                                   obj->halfFrameSizeInterp);

        obj->freq2xcorr = freq2xcorr_construct_zero(obj->frameSizeInterp, 
                                                    obj->halfFrameSizeInterp);
        
        obj->xcorrs = xcorrs_construct_zero(mod_ssl_config->mics->nPairs,
                                            obj->frameSizeInterp);

        obj->xcorrsMax = xcorrs_construct_zero(mod_ssl_config->mics->nPairs,
                                               obj->frameSizeInterp);

        obj->aimgs = (aimg_obj **) malloc(sizeof(aimg_obj *) * msg_pots_config->nPots);

        for (iLevel = 0; iLevel < mod_ssl_config->nLevels; iLevel++) {

            obj->aimgs[iLevel] = aimg_construct_zero(obj->scans->points[iLevel]->nPoints);

        }

        obj->xcorr2xcorr = xcorr2xcorr_construct_zero(obj->frameSizeInterp);
        
        obj->xcorr2aimg = (xcorr2aimg_obj **) malloc(sizeof(xcorr2aimg_obj *) * mod_ssl_config->nLevels);

        for (iLevel = 0; iLevel < mod_ssl_config->nLevels; iLevel++) {
            
            obj->xcorr2aimg[iLevel] = xcorr2aimg_construct_zero(obj->scans->points[iLevel]->nPoints);	

        }       

        obj->pots = pots_construct_zero(msg_pots_config->nPots);

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_pots_obj *) NULL;

        obj->enabled = 0;
      
        return obj;

    }

    void mod_ssl_destroy(mod_ssl_obj * obj) {

        unsigned int iLevel;
        unsigned int iPot;

        scans_destroy(obj->scans);

        freq2freq_phasor_destroy(obj->freq2freq_phasor);
        freq2freq_product_destroy(obj->freq2freq_product);
        freq2freq_interpolate_destroy(obj->freq2freq_interpolate);
        freqs_destroy(obj->phasors);
        freqs_destroy(obj->products);
        freqs_destroy(obj->productsInterp);
        freq2xcorr_destroy(obj->freq2xcorr);
        xcorrs_destroy(obj->xcorrs);
        xcorrs_destroy(obj->xcorrsMax);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
            aimg_destroy(obj->aimgs[iLevel]);
        }

        free((void *) obj->aimgs);

        xcorr2xcorr_destroy(obj->xcorr2xcorr);

        for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {
            xcorr2aimg_destroy(obj->xcorr2aimg[iLevel]);
        }

        free((void *) obj->xcorr2aimg);

        pots_destroy(obj->pots);

        free((void *) obj);

    }

    int mod_ssl_process(mod_ssl_obj * obj) {

        int rtnValue;
        unsigned int iPot;
        unsigned int iLevel;
        unsigned int iPoint;

        float maxValue;
        unsigned int maxIndex;

        if (msg_spectra_isZero(obj->in) == 0) {

            if (obj->enabled == 1) {

                freq2freq_phasor_process(obj->freq2freq_phasor, 
                                         obj->in->freqs, 
                                         obj->phasors);

                freq2freq_product_process(obj->freq2freq_product, 
                                          obj->phasors, 
                                          obj->phasors,
                                          obj->scans->pairs,
                                          obj->products);        

                freq2freq_interpolate_process(obj->freq2freq_interpolate,
                                              obj->products,
                                              obj->productsInterp);

                freq2xcorr_process(obj->freq2xcorr, 
                                   obj->productsInterp, 
                                   obj->scans->pairs,
                                   obj->xcorrs);           

                for (iPot = 0; iPot < obj->nPots; iPot++) {
                    
                    if (iPot > 0) {

                        xcorr2xcorr_process_reset(obj->xcorr2xcorr, 
                    	                          obj->scans->tdoas[obj->nLevels-1],
                                                  obj->scans->deltas[obj->nLevels-1],
                                                  obj->scans->pairs,
                                                  maxIndex,
                                                  obj->xcorrs);

                    }

                    maxIndex = 0;

                    for (iLevel = 0; iLevel < obj->nLevels; iLevel++) {

                        xcorr2xcorr_process_max(obj->xcorr2xcorr, 
                	                            obj->xcorrs, 
                	                            obj->scans->tdoas[iLevel],
             	                                obj->scans->deltas[iLevel],
                                                obj->scans->pairs,
                	                            obj->xcorrsMax);

                        xcorr2aimg_process(obj->xcorr2aimg[iLevel],
                    	                   obj->scans->tdoas[iLevel],
                    	                   obj->scans->indexes[iLevel],
                                           obj->scans->spatialindexes[iLevel],
                                           maxIndex,
                    	                   obj->xcorrsMax,
                    	                   obj->aimgs[iLevel]);

                        maxValue = obj->aimgs[iLevel]->array[0];

                        for (iPoint = 0; iPoint < obj->aimgs[iLevel]->aimgSize; iPoint++) {

                            if (obj->aimgs[iLevel]->array[iPoint] > maxValue) {

                        	    maxValue = obj->aimgs[iLevel]->array[iPoint];
                        	    maxIndex = iPoint;

                            }

                        }
                       
                    }

                    obj->pots->array[iPot * 4 + 0] = obj->scans->points[obj->nLevels-1]->array[maxIndex * 3 + 0];
                    obj->pots->array[iPot * 4 + 1] = obj->scans->points[obj->nLevels-1]->array[maxIndex * 3 + 1];
                    obj->pots->array[iPot * 4 + 2] = obj->scans->points[obj->nLevels-1]->array[maxIndex * 3 + 2];
                    obj->pots->array[iPot * 4 + 3] = maxValue * ((float) obj->interpRate);

                }
                
                memcpy(obj->out->pots->array, obj->pots->array, sizeof(float) * obj->pots->nPots * 4);

            }
            else {

                pots_zero(obj->out->pots);

            }

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_pots_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_ssl_connect(mod_ssl_obj * obj, msg_spectra_obj * in, msg_pots_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_ssl_disconnect(mod_ssl_obj * obj) {

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_pots_obj *) NULL;

    }

    void mod_ssl_enable(mod_ssl_obj * obj) {

        obj->enabled = 1;

    }

    void mod_ssl_disable(mod_ssl_obj * obj) {

        obj->enabled = 0;

    }

    mod_ssl_cfg * mod_ssl_cfg_construct(void) {

        mod_ssl_cfg * cfg;

        cfg = (mod_ssl_cfg *) malloc(sizeof(mod_ssl_cfg));

        cfg->mics = (mics_obj *) NULL;
        cfg->samplerate = (samplerate_obj *) NULL;
        cfg->soundspeed = (soundspeed_obj *) NULL;
        cfg->spatialfilters = (spatialfilters_obj *) NULL;
        
        cfg->nLevels = 0;;
        cfg->levels = (unsigned int *) NULL;
        cfg->deltas = (unsigned int *) NULL;
        cfg->nMatches = 0;
        cfg->probMin = 0.0f;
        cfg->nRefinedLevels = 0;
        cfg->nThetas = 0;
        cfg->gainMin = 0.0f;    

        return cfg;

    }

    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg) {

        if (cfg->mics != NULL) {
            mics_destroy(cfg->mics);
        }

        if (cfg->samplerate != NULL) {
            samplerate_destroy(cfg->samplerate);
        }

        if (cfg->soundspeed != NULL) {
            soundspeed_destroy(cfg->soundspeed);
        }

        if (cfg->spatialfilters != NULL) {
            spatialfilters_destroy(cfg->spatialfilters);
        }

        if (cfg->levels != NULL) {
            free((void *) cfg->levels);
        }

        if (cfg->deltas != NULL) {
            free((void *) cfg->deltas);
        }

        free((void *) cfg);

    }

    void mod_ssl_cfg_printf(const mod_ssl_cfg * cfg) {

        unsigned int iLevel;

        mics_printf(cfg->mics);
        samplerate_printf(cfg->samplerate);
        soundspeed_printf(cfg->soundspeed);
        spatialfilters_printf(cfg->spatialfilters);

        for (iLevel = 0; iLevel < cfg->nLevels; iLevel++) {

            if (iLevel == 0) {

                printf("levels = (%u): level = %u, delta = %d\n", iLevel, cfg->levels[iLevel], cfg->deltas[iLevel]);

            }
            else {

                printf("         (%u): level = %u, delta = %d\n", iLevel, cfg->levels[iLevel], cfg->deltas[iLevel]);

            }


        }

        printf("nMatches = %u\n", cfg->nMatches);        
        printf("probMin = %f\n", cfg->probMin);
        printf("nRefinedLevels = %u\n", cfg->nRefinedLevels);
        printf("nThetas = %u\n", cfg->nThetas);
        printf("gainMin = %f\n", cfg->gainMin);

    }
