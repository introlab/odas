    
    #include "profiler.h"

    profiler * profiler_construct(void) {

        profiler * prf;

        prf = (profiler *) malloc(sizeof(profiler));

        prf->duration = 0.0f;

        prf->src_hops_mics_prf = 0.0f;
        prf->con_hops_mics_raw_prf = 0.0f;

        prf->mod_mapping_mics_prf = 0.0f;
        prf->con_hops_mics_map_prf = 0.0f;

        prf->mod_resample_mics_prf = 0.0f;
        prf->con_hops_mics_rs_prf = 0.0f;

        prf->mod_stft_mics_prf = 0.0f;
        prf->con_spectra_mics_prf = 0.0f;

        prf->mod_noise_mics_prf = 0.0f;
        prf->con_powers_mics_prf = 0.0f;

        prf->mod_ssl_prf = 0.0f;
        prf->con_pots_ssl_prf = 0.0f;
        prf->snk_pots_ssl_prf = 0.0f;

        prf->inj_targets_sst_prf = 0.0f;
        prf->con_targets_sst_prf = 0.0f;

        prf->mod_sst_prf = 0.0f;
        prf->con_tracks_sst_prf = 0.0f;
        prf->snk_tracks_sst_prf = 0.0f;

        prf->mod_sss_prf = 0.0f;
        prf->con_spectra_seps_prf = 0.0f;
        prf->con_spectra_pfs_prf = 0.0f;        

        prf->mod_istft_seps_prf = 0.0f;;
        prf->mod_istft_pfs_prf = 0.0f;;
        prf->con_hops_seps_prf = 0.0f;
        prf->con_hops_pfs_prf = 0.0f;

        prf->mod_resample_seps_prf = 0.0f;
        prf->mod_resample_pfs_prf = 0.0f;
        prf->con_hops_seps_rs_prf = 0.0f;
        prf->con_hops_pfs_rs_prf = 0.0f;

        prf->mod_volume_seps_prf = 0.0f;
        prf->mod_volume_pfs_prf = 0.0f;
        prf->con_hops_seps_vol_prf = 0.0f;
        prf->con_hops_pfs_vol_prf = 0.0f;
        prf->snk_hops_seps_vol_prf = 0.0f;
        prf->snk_hops_pfs_vol_prf = 0.0f;

        prf->mod_classify_prf = 0.0f;
        prf->con_categories_prf = 0.0f;
        prf->snk_categories_prf = 0.0f;

        return prf;

    }

    void profiler_destroy(profiler * prf) {

        free((void *) prf);

    }

    void profiler_printf(const profiler * prf) {

        float source, sink, module, injector, connector;
        float total;

        source = prf->src_hops_mics_prf;

        sink = prf->snk_pots_ssl_prf +
               prf->snk_tracks_sst_prf + 
               prf->snk_hops_seps_vol_prf +
               prf->snk_hops_pfs_vol_prf +
               prf->snk_categories_prf;

        module = prf->mod_mapping_mics_prf + 
                 prf->mod_resample_mics_prf +
                 prf->mod_stft_mics_prf +
                 prf->mod_noise_mics_prf +
                 prf->mod_ssl_prf +
                 prf->mod_sst_prf +
                 prf->mod_sss_prf +
                 prf->mod_istft_seps_prf +
                 prf->mod_istft_pfs_prf +
                 prf->mod_resample_seps_prf +
                 prf->mod_resample_pfs_prf +
                 prf->mod_volume_seps_prf +
                 prf->mod_volume_pfs_prf +                
                 prf->mod_classify_prf;

        injector = prf->inj_targets_sst_prf;

        connector = prf->con_hops_mics_raw_prf +
                    prf->con_hops_mics_map_prf +
                    prf->con_hops_mics_rs_prf +
                    prf->con_spectra_mics_prf +
                    prf->con_powers_mics_prf +
                    prf->con_pots_ssl_prf +
                    prf->con_targets_sst_prf +
                    prf->con_tracks_sst_prf +
                    prf->con_spectra_seps_prf +
                    prf->con_spectra_pfs_prf +
                    prf->con_hops_seps_prf +
                    prf->con_hops_pfs_prf +
                    prf->con_hops_seps_rs_prf +
                    prf->con_hops_pfs_rs_prf +
                    prf->con_hops_seps_vol_prf +
                    prf->con_hops_pfs_vol_prf +
                    prf->con_categories_prf;

        total = source + sink + module + connector;                    

        printf("+--------------------------------------------+\n");
        printf("|              Profiler summary              |\n");
        printf("+--------------------------------------------+\n");
        printf("| + Raw                                      |\n");
        printf("|    - Source.......... %07.3f (%06.2f%%)    |\n",prf->src_hops_mics_prf,roundf(10000.0f * prf->src_hops_mics_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_hops_mics_raw_prf,roundf(10000.0f * prf->con_hops_mics_raw_prf / prf->duration) / 100.0f);
        printf("| + Mapping                                  |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_mapping_mics_prf,roundf(10000.0f * prf->mod_mapping_mics_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_hops_mics_map_prf,roundf(10000.0f * prf->con_hops_mics_map_prf / prf->duration) / 100.0f);
        printf("| + Resample                                 |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_resample_mics_prf,roundf(10000.0f * prf->mod_resample_mics_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_hops_mics_rs_prf,roundf(10000.0f * prf->con_hops_mics_rs_prf / prf->duration) / 100.0f);
        printf("| + STFT                                     |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_stft_mics_prf,roundf(10000.0f * prf->mod_stft_mics_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_spectra_mics_prf,roundf(10000.0f * prf->con_spectra_mics_prf / prf->duration) / 100.0f);
        printf("| + Noise                                    |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_noise_mics_prf,roundf(10000.0f * prf->mod_noise_mics_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_powers_mics_prf,roundf(10000.0f * prf->con_powers_mics_prf / prf->duration) / 100.0f);
        printf("| + SSL                                      |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_ssl_prf,roundf(10000.0f * prf->mod_ssl_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_pots_ssl_prf,roundf(10000.0f * prf->con_pots_ssl_prf / prf->duration) / 100.0f);
        printf("|    - Sink............ %07.3f (%06.2f%%)    |\n",prf->snk_pots_ssl_prf,roundf(10000.0f * prf->snk_pots_ssl_prf / prf->duration) / 100.0f);  
        printf("| + Target                                   |\n");
        printf("|    - Injector........ %07.3f (%06.2f%%)    |\n",prf->inj_targets_sst_prf,roundf(10000.0f * prf->inj_targets_sst_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_targets_sst_prf,roundf(10000.0f * prf->con_targets_sst_prf / prf->duration) / 100.0f);
        printf("| + SST                                      |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_sst_prf,roundf(10000.0f * prf->mod_sst_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_tracks_sst_prf,roundf(10000.0f * prf->con_tracks_sst_prf / prf->duration) / 100.0f);
        printf("|    - Sink............ %07.3f (%06.2f%%)    |\n",prf->snk_tracks_sst_prf,roundf(10000.0f * prf->snk_tracks_sst_prf / prf->duration) / 100.0f);       
        printf("| + SSS                                      |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_sss_prf,roundf(10000.0f * prf->mod_sss_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",(prf->con_spectra_seps_prf+prf->con_spectra_pfs_prf),roundf(10000.0f * ((prf->con_spectra_seps_prf+prf->con_spectra_pfs_prf) / prf->duration) / 100.0f));
        printf("| + ISTFT                                    |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",(prf->mod_istft_seps_prf+prf->mod_istft_pfs_prf),roundf(10000.0f * (prf->mod_istft_seps_prf+prf->mod_istft_pfs_prf) / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",(prf->con_hops_seps_prf+prf->con_hops_pfs_prf),roundf(10000.0f * (prf->con_hops_seps_prf+prf->con_hops_pfs_prf) / prf->duration) / 100.0f);
        printf("| + Resample                                 |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",(prf->mod_resample_seps_prf+prf->mod_resample_pfs_prf),roundf(10000.0f * (prf->mod_resample_seps_prf+prf->mod_resample_pfs_prf) / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",(prf->con_hops_seps_rs_prf+prf->con_hops_pfs_rs_prf),roundf(10000.0f * (prf->con_hops_seps_rs_prf+prf->con_hops_pfs_rs_prf) / prf->duration) / 100.0f);
        printf("| + Volume                                   |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",(prf->mod_volume_seps_prf+prf->mod_volume_pfs_prf),roundf(10000.0f * (prf->mod_volume_seps_prf+prf->mod_volume_pfs_prf) / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",(prf->con_hops_seps_vol_prf+prf->con_hops_pfs_vol_prf),roundf(10000.0f * (prf->con_hops_seps_vol_prf+prf->con_hops_pfs_vol_prf) / prf->duration) / 100.0f);       
        printf("|    - Sink............ %07.3f (%06.2f%%)    |\n",(prf->snk_hops_seps_vol_prf+prf->snk_hops_pfs_vol_prf),roundf(10000.0f * (prf->snk_hops_seps_vol_prf+prf->snk_hops_pfs_vol_prf) / prf->duration) / 100.0f);
        printf("| + Classify                                 |\n");
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",prf->mod_classify_prf,roundf(10000.0f * prf->mod_classify_prf / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",prf->con_categories_prf,roundf(10000.0f * prf->con_categories_prf / prf->duration) / 100.0f);
        printf("|    - Sink............ %07.3f (%06.2f%%)    |\n",prf->snk_categories_prf,roundf(10000.0f * prf->snk_categories_prf / prf->duration) / 100.0f);
        printf("+--------------------------------------------+\n");
        printf("| + TOTAL.............. %07.3f (%06.2f%%)    |\n",total,roundf(10000.0f * total / prf->duration) / 100.0f);
        printf("|    - Module.......... %07.3f (%06.2f%%)    |\n",module,roundf(10000.0f * module / prf->duration) / 100.0f);
        printf("|    - Connector....... %07.3f (%06.2f%%)    |\n",connector,roundf(10000.0f * connector / prf->duration) / 100.0f);
        printf("|    - Source.......... %07.3f (%06.2f%%)    |\n",source,roundf(10000.0f * source / prf->duration) / 100.0f);
        printf("|    - Sink............ %07.3f (%06.2f%%)    |\n",sink,roundf(10000.0f * sink / prf->duration) / 100.0f); 
        printf("+--------------------------------------------+\n");

    }