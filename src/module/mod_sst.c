    
    #include "mod_sst.h"

    mod_sst_obj * mod_sst_construct(const mod_sst_cfg * mod_sst_config, const mod_ssl_cfg * mod_ssl_config, const msg_pots_cfg * msg_pots_config, const msg_tracks_cfg * msg_tracks_config) {

        mod_sst_obj * obj;
        
        unsigned int iTrackMax;
        points_obj * points;
        beampatterns_obj * beampatterns_mics;
        beampatterns_obj * beampatterns_spatialfilter;
        spatialgains_obj * spatialgains;
        spatialmasks_obj * spatialmasks;
        spatialindexes_obj * spatialindexes;
        unsigned int iPoint;
        unsigned int nPointsActive;
        float diffuse_cst;
        float deltaT;
        
        obj = (mod_sst_obj *) malloc(sizeof(mod_sst_obj));

        obj->nPots = msg_pots_config->nPots;
        obj->nTracksMax = msg_tracks_config->nTracks;
        obj->nTracks = 0;

        obj->mode = mod_sst_config->mode;

        obj->mixtures = (mixture_obj **) malloc(sizeof(mixture_obj *) * (obj->nTracksMax+1));
        obj->coherences = (coherences_obj **) malloc(sizeof(coherences_obj *) * (obj->nTracksMax+1));
        obj->postprobs = (postprobs_obj **) malloc(sizeof(postprobs_obj *) * (obj->nTracksMax+1));

        for (iTrackMax = 0; iTrackMax <= obj->nTracksMax; iTrackMax++) {

            obj->mixtures[iTrackMax] = mixture_construct_zero(obj->nPots, iTrackMax);
            obj->coherences[iTrackMax] = coherences_construct_zero(obj->nPots, iTrackMax);
            obj->postprobs[iTrackMax] = postprobs_construct_zero(obj->nPots, iTrackMax); 

        }

        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracksMax);
        obj->idsAdded = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracksMax);
        obj->idsRemoved = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracksMax);
                
        obj->type = (char *) malloc(sizeof(char) * obj->nTracksMax);
        
        obj->kalmans = (kalman_obj **) malloc(sizeof(kalman_obj *) * obj->nTracksMax); 
        memset(obj->kalmans, 0x00, sizeof(kalman_obj *) * obj->nTracksMax);
        obj->particles = (particles_obj **) malloc(sizeof(particles_obj *) * obj->nTracksMax);
        memset(obj->particles, 0x00, sizeof(particles_obj *) * obj->nTracksMax);
        
        obj->sourceActivities = (float *) malloc(sizeof(float) * obj->nTracksMax);
        memset(obj->sourceActivities, 0x00, sizeof(float) * obj->nTracksMax);

        obj->theta_new = mod_sst_config->theta_new;
        obj->N_prob = mod_sst_config->N_prob;
        obj->theta_prob = mod_sst_config->theta_prob;
        obj->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->nTracksMax);

        obj->theta_inactive = mod_sst_config->theta_inactive;

        obj->n_prob = (unsigned int *) malloc(sizeof(unsigned int) * obj->nTracksMax);
        obj->mean_prob = (float *) malloc(sizeof(float) * obj->nTracksMax);
        obj->n_inactive = (unsigned int *) malloc(sizeof(unsigned int) * obj->nTracksMax);

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            obj->ids[iTrackMax] = 0;
            obj->idsAdded[iTrackMax] = 0;
            obj->idsRemoved[iTrackMax] = 0;

            obj->type[iTrackMax] = 'I';

            switch(obj->mode) {

                case 'k':
                    
                    obj->kalmans[iTrackMax] =  kalman_construct_zero();

                break;

                case 'p':
                    
                    obj->particles[iTrackMax] =  particles_construct_zero(mod_sst_config->nParticles);

                break;

                default:

                    printf("Invalid type of filter\n");
                    exit(EXIT_FAILURE);

                break;

            }
            
            obj->N_inactive[iTrackMax] = mod_sst_config->N_inactive[iTrackMax];

            obj->n_prob[iTrackMax] = 0;
            obj->mean_prob[iTrackMax] = 0.0f;
            obj->n_inactive[iTrackMax] = 0;

        }       

        points = space_sphere(mod_ssl_config->levels[mod_ssl_config->nLevels-1]);
        beampatterns_mics = directivity_beampattern_mics(mod_ssl_config->mics, mod_ssl_config->nThetas);
        beampatterns_spatialfilter = directivity_beampattern_spatialfilter(mod_ssl_config->spatialfilter, mod_ssl_config->nThetas);
        spatialgains = directivity_spatialgains(mod_ssl_config->mics, beampatterns_mics, mod_ssl_config->spatialfilter, beampatterns_spatialfilter, points);           
        spatialmasks = directivity_spatialmasks(spatialgains, mod_ssl_config->gainMin);    
        spatialindexes = directivity_spatialindexes(spatialmasks);

        nPointsActive = 0;

        for (iPoint = 0; iPoint < spatialindexes->nPoints; iPoint++) {

            if (spatialindexes->count[iPoint] > 0) {
                nPointsActive++;
            }

        }

        diffuse_cst = 1.0f / (4.0f * M_PI * ((float) nPointsActive) / ((float) spatialindexes->nPoints));

        points_destroy(points);
        beampatterns_destroy(beampatterns_mics);
        beampatterns_destroy(beampatterns_spatialfilter);
        spatialgains_destroy(spatialgains);
        spatialmasks_destroy(spatialmasks);
        spatialindexes_destroy(spatialindexes);

        deltaT = ((float) mod_sst_config->hopSize) / ((float) msg_pots_config->fS);
        
        switch(obj->mode) {

            case 'k':

                obj->kalman2kalman_prob = kalman2kalman_construct(deltaT,
                                                                  mod_sst_config->sigmaQ,
                                                                  mod_sst_config->sigmaR_prob,
                                                                  mod_sst_config->epsilon);    

                obj->kalman2kalman_active = kalman2kalman_construct(deltaT,
                                                                    mod_sst_config->sigmaQ,
                                                                    mod_sst_config->sigmaR_active,
                                                                    mod_sst_config->epsilon);    

                obj->kalman2coherence_prob = kalman2coherence_construct(mod_sst_config->epsilon, 
                                                                        mod_sst_config->sigmaR_prob);

                obj->kalman2coherence_active = kalman2coherence_construct(mod_sst_config->epsilon, 
                                                                          mod_sst_config->sigmaR_active);

                obj->particle2particle_prob = NULL;
                obj->particle2particle_active = NULL;
                obj->particle2coherence_prob = NULL;
                obj->particle2coherence_active = NULL;                

            break;

            case 'p':

                obj->kalman2kalman_prob = NULL;
                obj->kalman2kalman_active = NULL;
                obj->kalman2coherence_prob = NULL;
                obj->kalman2coherence_active = NULL;

                obj->particle2particle_prob = particle2particle_construct(mod_sst_config->nParticles,
                                                                          deltaT,
                                                                          mod_sst_config->st_alpha,
                                                                          mod_sst_config->st_beta,
                                                                          mod_sst_config->st_ratio,
                                                                          mod_sst_config->ve_alpha,
                                                                          mod_sst_config->ve_beta,
                                                                          mod_sst_config->ve_ratio,
                                                                          mod_sst_config->ac_alpha,
                                                                          mod_sst_config->ac_beta,
                                                                          mod_sst_config->ac_ratio,
                                                                          (double) mod_sst_config->epsilon,
                                                                          mod_sst_config->sigmaR_prob,
                                                                          mod_sst_config->Nmin);

                obj->particle2particle_active = particle2particle_construct(mod_sst_config->nParticles,
                                                                            deltaT,
                                                                            mod_sst_config->st_alpha,
                                                                            mod_sst_config->st_beta,
                                                                            mod_sst_config->st_ratio,
                                                                            mod_sst_config->ve_alpha,
                                                                            mod_sst_config->ve_beta,
                                                                            mod_sst_config->ve_ratio,
                                                                            mod_sst_config->ac_alpha,
                                                                            mod_sst_config->ac_beta,
                                                                            mod_sst_config->ac_ratio,
                                                                            (double) mod_sst_config->epsilon,
                                                                            mod_sst_config->sigmaR_active,
                                                                            mod_sst_config->Nmin);    

                obj->particle2coherence_prob = particle2coherence_construct(mod_sst_config->sigmaR_prob);

                obj->particle2coherence_active = particle2coherence_construct(mod_sst_config->sigmaR_active);

            break;

            default:

            break;

        }

        obj->mixture2mixture = mixture2mixture_construct(mod_sst_config->active_gmm,
                                                         mod_sst_config->inactive_gmm,
                                                         diffuse_cst,
                                                         mod_sst_config->Pfalse,
                                                         mod_sst_config->Pnew,
                                                         mod_sst_config->Ptrack,
                                                         mod_sst_config->epsilon);

        obj->id = 0;

        obj->in = (msg_pots_obj *) NULL;
        obj->out = (msg_tracks_obj *) NULL;

        return obj;

    }

    void mod_sst_destroy(mod_sst_obj * obj) {

        unsigned int iTrackMax;

        for (iTrackMax = 0; iTrackMax <= obj->nTracksMax; iTrackMax++) {

            mixture_destroy(obj->mixtures[iTrackMax]);
            coherences_destroy(obj->coherences[iTrackMax]);
            postprobs_destroy(obj->postprobs[iTrackMax]);

        }

        for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

            if (obj->kalmans[iTrackMax] != NULL) {

                kalman_destroy(obj->kalmans[iTrackMax]);

            }

            if (obj->particles[iTrackMax] != NULL) {

                particles_destroy(obj->particles[iTrackMax]);

            }

        }

        free((void *) obj->mixtures);
        free((void *) obj->coherences);
        free((void *) obj->postprobs);

        free((void *) obj->ids);
        free((void *) obj->idsAdded);
        free((void *) obj->idsRemoved);
        free((void *) obj->type);

        free((void *) obj->kalmans);
        free((void *) obj->particles);

        free((void *) obj->sourceActivities);

        free((void *) obj->N_inactive);
        free((void *) obj->n_prob);
        free((void *) obj->mean_prob);
        free((void *) obj->n_inactive);

        if (obj->kalman2kalman_prob != NULL) {
            kalman2kalman_destroy(obj->kalman2kalman_prob);
        }
        if (obj->kalman2kalman_active != NULL) {
            kalman2kalman_destroy(obj->kalman2kalman_active);
        }
        if (obj->kalman2coherence_prob != NULL) {
            kalman2coherence_destroy(obj->kalman2coherence_prob);
        }
        if (obj->kalman2coherence_active != NULL) {
            kalman2coherence_destroy(obj->kalman2coherence_active);
        }
        if (obj->particle2particle_prob != NULL) {
            particle2particle_destroy(obj->particle2particle_prob);
        }
        if (obj->particle2particle_active != NULL) {
            particle2particle_destroy(obj->particle2particle_active);
        }
        if (obj->particle2coherence_prob != NULL)  {
            particle2coherence_destroy(obj->particle2coherence_prob);
        }
        if (obj->particle2coherence_active != NULL)  {
            particle2coherence_destroy(obj->particle2coherence_active);
        }

        mixture2mixture_destroy(obj->mixture2mixture);

        free((void *) obj);

    }

    int mod_sst_process(mod_sst_obj * obj) {

        unsigned int iPot;
        unsigned int iTrackMax;
        unsigned int iTrack;
        float x,y,z;
        float sourceActivity;
        int rtnValue;

        if (msg_pots_isZero(obj->in) == 0) {

            // Count

            obj->nTracks = 0;

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    obj->nTracks++;

                }

            }

            // Predict  

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    switch(obj->mode) {

                        case 'k':

                            switch (obj->type[iTrackMax]) {
                                
                                case 'P':                    

                                    kalman2kalman_predict(obj->kalman2kalman_prob,
                                                          obj->kalmans[iTrackMax]);         

                                break;

                                case 'A':

                                    kalman2kalman_predict(obj->kalman2kalman_active,
                                                          obj->kalmans[iTrackMax]);  

                                break;

                                default:

                                    printf("Unknown state.\n");
                                    exit(EXIT_FAILURE);                        

                                break;

                            }

                        break;

                        case 'p':

                            switch (obj->type[iTrackMax]) {
                                
                                case 'P':    

                                    particle2particle_predict(obj->particle2particle_prob,
                                                              obj->particles[iTrackMax]);                        

                                break;

                                case 'A':

                                    particle2particle_predict(obj->particle2particle_active,
                                                              obj->particles[iTrackMax]);                        

                                break;

                                default:

                                    printf("Unknown state.\n");
                                    exit(EXIT_FAILURE);                        

                                break;

                            }    

                        break;

                        default:

                            printf("Invalid filter type.\n");
                            exit(EXIT_FAILURE);

                        break;

                    }

                }

            }

            // Coherence

            iTrack = 0;

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    switch(obj->mode) {

                        case 'k':

                            switch (obj->type[iTrackMax]) {
                                
                                case 'P':  

                                    kalman2coherence_process(obj->kalman2coherence_prob,
                                                             obj->kalmans[iTrackMax],
                                                             obj->in->pots,
                                                             iTrack,
                                                             obj->coherences[obj->nTracks]);

                                break;

                                case 'A':

                                    kalman2coherence_process(obj->kalman2coherence_active,
                                                             obj->kalmans[iTrackMax],
                                                             obj->in->pots,
                                                             iTrack,
                                                             obj->coherences[obj->nTracks]);

                                break;

                                default:

                                    printf("Unknown state.\n");
                                    exit(EXIT_FAILURE);                            

                                break;

                            }

                        break;

                        case 'p':

                            switch (obj->type[iTrackMax]) {
                                
                                case 'P':                      

                                    particle2coherence_process(obj->particle2coherence_prob,
                                                               obj->particles[iTrackMax],
                                                               obj->in->pots,
                                                               iTrack,
                                                               obj->coherences[obj->nTracks]);

                                break;

                                case 'A':                      

                                    particle2coherence_process(obj->particle2coherence_active,
                                                               obj->particles[iTrackMax],
                                                               obj->in->pots,
                                                               iTrack,
                                                               obj->coherences[obj->nTracks]);

                                break;

                                default:

                                    printf("Unknown state.\n");
                                    exit(EXIT_FAILURE);                            

                                break;                        

                            }

                        break;

                        default:

                            printf("Invalid filter type.\n");
                            exit(EXIT_FAILURE);

                        break;

                    }

                    iTrack++;

                }

            }

            // Mixture

            mixture2mixture_process(obj->mixture2mixture, 
            	                    obj->mixtures[obj->nTracks], 
            	                    obj->in->pots, 
            	                    obj->coherences[obj->nTracks], 
            	                    obj->postprobs[obj->nTracks]);

            // Update

            iTrack = 0;

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    switch(obj->mode) {

                        case 'k':

                            switch (obj->type[iTrackMax]) {
                                
                                case 'P':                                                  

                                    kalman2kalman_update(obj->kalman2kalman_prob,
                                                         obj->postprobs[obj->nTracks],
                                                         iTrack,
                                                         obj->in->pots,
                                                         obj->kalmans[iTrackMax]);

                                break;

                                case 'A':                      

                                    kalman2kalman_update(obj->kalman2kalman_active,
                                                         obj->postprobs[obj->nTracks],
                                                         iTrack,
                                                         obj->in->pots,
                                                         obj->kalmans[iTrackMax]);

                                break;

                                default:

                                    printf("Unknown state.\n");
                                    exit(EXIT_FAILURE); 

                                break;

                            }

                        break;

                        case 'p':

                            switch (obj->type[iTrackMax]) {
                                
                                case 'P':                      

                                    particle2particle_update(obj->particle2particle_prob,
                                                             obj->postprobs[obj->nTracks],
                                                             iTrack,
                                                             obj->in->pots,
                                                             obj->particles[iTrackMax]);

                                break;

                                case 'A':

                                    particle2particle_update(obj->particle2particle_active,
                                                             obj->postprobs[obj->nTracks],
                                                             iTrack,
                                                             obj->in->pots,
                                                             obj->particles[iTrackMax]);

                                break;

                                default:

                                    printf("Unknown state.\n");
                                    exit(EXIT_FAILURE);                         

                                break;

                            }

                        break;

                        default:

                            printf("Invalid filter type.\n");
                            exit(EXIT_FAILURE);

                        break;

                    }

                    iTrack++;

                }

            }

            // Activity

            iTrack = 0;
            memset(obj->sourceActivities, 0x00, sizeof(float) * obj->nTracksMax);

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    sourceActivity = obj->postprobs[obj->nTracks]->arrayTrackTotal[iTrack];
                    obj->sourceActivities[iTrackMax] = sourceActivity;

                    // Update counters
                    
                    switch (obj->type[iTrackMax]) {
                        
                        case 'P':

                            obj->n_prob[iTrackMax]++;
                            obj->mean_prob[iTrackMax] += sourceActivity;

                        break;

                        case 'A':

                            if (sourceActivity >= obj->theta_inactive) {
                                obj->n_inactive[iTrackMax] = 0;
                            }
                            else {
                                obj->n_inactive[iTrackMax]++;   
                            }

                        break;

                        default:

                            printf("Unknown state.\n");
                            exit(EXIT_FAILURE);

                        break;

                    }

                    iTrack++;

                }

            }        

            // Transitions

            iTrack = 0;

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    if ((obj->type[iTrackMax] == 'P') && 
                        (obj->n_prob[iTrackMax] == obj->N_prob) && 
                        (obj->mean_prob[iTrackMax]/((float) obj->N_prob) >= obj->theta_prob)) {

                        obj->type[iTrackMax] = 'A';
                        obj->n_inactive[iTrackMax] = 0;

                    }

                    iTrack++;

                }

            }          

            // Add source
            
            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                obj->idsAdded[iTrackMax] = 0;

            }

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                if (obj->postprobs[obj->nTracks]->arrayNew[iPot] > obj->theta_new) {                

                    for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                        if (obj->ids[iTrackMax] == 0) {

                            obj->id++;
                            obj->idsAdded[iTrackMax] = obj->id;
                            
                            switch(obj->mode) {

                                case 'k':

                                    kalman2kalman_init(obj->kalman2kalman_prob, 
                                                       obj->in->pots,
                                                       iPot, 
                                                       obj->kalmans[iTrackMax]); 

                                break;

                                case 'p':

                                    particle2particle_init(obj->particle2particle_prob, 
                                                           obj->in->pots,
                                                           iPot, 
                                                           obj->particles[iTrackMax]);

                                break;

                                default:

                                    printf("Invalid filter type.\n");
                                    exit(EXIT_FAILURE);

                                break;

                            }

                            obj->type[iTrackMax] = 'P';
                            obj->n_prob[iTrackMax] = 0;
                            obj->mean_prob[iTrackMax] = 0.0f;

                            break;

                        }

                    }

                }

            }

            // Remove source

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                obj->idsRemoved[iTrackMax] = 0;
                
            }

            iTrack = 0;

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    if ((obj->type[iTrackMax] == 'P') && 
                        (obj->n_prob[iTrackMax] == obj->N_prob) && 
                        (obj->mean_prob[iTrackMax]/((float) obj->N_prob) < obj->theta_prob)) {

                        obj->idsRemoved[iTrackMax] = obj->ids[iTrackMax];

                    }

                    if ((obj->type[iTrackMax] == 'A') &&
                        (obj->n_inactive[iTrackMax] >= obj->N_inactive[obj->nTracks-1])) {

                        obj->idsRemoved[iTrackMax] = obj->ids[iTrackMax];

                    }

                    iTrack++;

                }

            }

            // Update IDs

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->idsAdded[iTrackMax] != 0) {

                    obj->ids[iTrackMax] = obj->idsAdded[iTrackMax];

                }

                if (obj->idsRemoved[iTrackMax] != 0) {

                    obj->ids[iTrackMax] = 0;

                }

            }

            // Count

            obj->nTracks = 0;

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    obj->nTracks++;

                }

            }


            // Copy in tracking
       
            memset(obj->out->tracks->array, 0x00, sizeof(float) * obj->out->tracks->nTracks * 3);
            memset(obj->out->tracks->ids, 0x00, sizeof(unsigned long long) * obj->out->tracks->nTracks);

            for (iTrackMax = 0; iTrackMax < obj->nTracksMax; iTrackMax++) {

                if (obj->ids[iTrackMax] != 0) {

                    if (obj->type[iTrackMax] == 'A') {

                        switch(obj->mode) {

                            case 'k':

                                kalman2kalman_estimate(obj->kalman2kalman_active, 
                                                       obj->kalmans[iTrackMax], 
                                                       &x, 
                                                       &y, 
                                                       &z);

                            break;

                            case 'p':

                                particle2particle_estimate(obj->particle2particle_active, 
                                                           obj->particles[iTrackMax], 
                                                           &x,
                                                           &y,
                                                           &z);

                            break;

                            default:

                                printf("Invalid filter type.\n");
                                exit(EXIT_FAILURE);

                            break;

                        }

                        obj->out->tracks->array[iTrackMax * 3 + 0] = x;
                        obj->out->tracks->array[iTrackMax * 3 + 1] = y;
                        obj->out->tracks->array[iTrackMax * 3 + 2] = z;
                        obj->out->tracks->ids[iTrackMax] = obj->ids[iTrackMax];
                        obj->out->tracks->activity[iTrackMax] = obj->sourceActivities[iTrackMax];

                    }

                }

            }

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_tracks_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_sst_connect(mod_sst_obj * obj, msg_pots_obj * in, msg_tracks_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_sst_disconnect(mod_sst_obj * obj) {

        obj->in = (msg_pots_obj *) NULL;
        obj->out = (msg_tracks_obj *) NULL;

    }

    mod_sst_cfg * mod_sst_cfg_construct(void) {

        mod_sst_cfg * cfg;

        cfg = (mod_sst_cfg *) malloc(sizeof(mod_sst_cfg));

        cfg->mode = 0x00;

        cfg->hopSize = 0;
        cfg->sigmaQ = 0.0f;
        
        cfg->nParticles = 0;
        cfg->st_alpha = 0.0f;
        cfg->st_beta = 0.0f;
        cfg->st_ratio = 0.0f;
        cfg->ve_alpha = 0.0f;
        cfg->ve_beta = 0.0f;
        cfg->ve_ratio = 0.0f;
        cfg->ac_alpha = 0.0f;
        cfg->ac_beta = 0.0f;
        cfg->ac_ratio = 0.0f;
        cfg->Nmin = 0.0f;

        cfg->epsilon = 0.0f;
        cfg->sigmaR_prob = 0.0f;
        cfg->sigmaR_active = 0.0f;
        cfg->active_gmm = (gaussians_1d_obj *) NULL;
        cfg->inactive_gmm = (gaussians_1d_obj *) NULL;
        cfg->Pfalse = 0.0f;
        cfg->Pnew = 0.0f;
        cfg->Ptrack = 0.0f;

        cfg->theta_new = 0.0f;
        cfg->N_prob = 0;
        cfg->theta_prob = 0.0f;
        cfg->N_inactive = (unsigned int *) NULL;
        cfg->theta_inactive = 0.0f;

        return cfg;

    }

    void mod_sst_cfg_destroy(mod_sst_cfg * cfg) {

        if (cfg->active_gmm != NULL) {
            gaussians_1d_destroy(cfg->active_gmm);
        }

        if (cfg->inactive_gmm != NULL) {
            gaussians_1d_destroy(cfg->inactive_gmm);
        }

        if (cfg->N_inactive != NULL) {
            free((void *) cfg->N_inactive);
        }

        free((void *) cfg);

    }

    void mod_sst_cfg_printf(const mod_sst_cfg * cfg) {

        unsigned int iTrackMax;

        printf("mode = %c\n", cfg->mode);
        printf("nTracksMax = %u\n", cfg->nTracksMax);
        printf("hopSize = %u\n", cfg->hopSize);
        printf("sigmaQ = %f\n", cfg->sigmaQ);
        printf("nParticles = %u\n", cfg->nParticles);
        printf("st_alpha = %f\n", cfg->st_alpha);
        printf("st_beta = %f\n", cfg->st_beta);
        printf("st_ratio = %f\n", cfg->st_ratio);
        printf("ve_alpha = %f\n", cfg->ve_alpha);
        printf("ve_beta = %f\n", cfg->ve_beta);
        printf("ve_ratio = %f\n", cfg->ve_ratio);
        printf("ac_alpha = %f\n", cfg->ac_alpha);
        printf("ac_beta = %f\n", cfg->ac_beta);
        printf("ac_ratio = %f\n", cfg->ac_ratio);
        printf("Nmin = %f\n", cfg->Nmin);
        printf("epsilon = %f\n", cfg->epsilon);
        printf("sigmaR_prob = %f\n", cfg->sigmaR_prob);
        printf("sigmaR_active = %f\n", cfg->sigmaR_active);

        printf("active_gmm:\n");
        gaussians_1d_printf(cfg->active_gmm);

        printf("inactive_gmm:\n");
        gaussians_1d_printf(cfg->inactive_gmm);

        printf("Pfalse = %f\n", cfg->Pfalse);
        printf("Pnew = %f\n", cfg->Pnew);
        printf("Ptrack = %f\n", cfg->Ptrack);
        printf("theta_new = %f\n", cfg->theta_new);
        printf("N_prob = %u\n", cfg->N_prob);
        printf("theta_prob = %f\n", cfg->theta_prob);

        printf("N_inactive = (");
        for (iTrackMax = 0; iTrackMax < cfg->nTracksMax; iTrackMax++) {

            printf("%u",cfg->N_inactive[iTrackMax]);

            if (iTrackMax != (cfg->nTracksMax-1)) {
                printf(", ");
            }

        }
        printf(")\n");  

        printf("theta_inactive = %f\n", cfg->theta_inactive);      

    }