    
    #include "mod_sss.h"

    mod_sss_obj * mod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_sss_obj * obj;
        
        obj = (mod_sss_obj *) malloc(sizeof(mod_sss_obj));

        obj->nSeps = msg_tracks_config->nTracks;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->halfFrameSize = msg_spectra_config->halfFrameSize;

        switch(obj->mode_sep) {

            case 'd':

            break;

            case 'g':

            break;

            case 'm':

            break;

            default:

                printf("Invalid separation method.\n");
                exit(EXIT_FAILURE);

            break;

        }

        switch(obj->mode_pf) {

            case 'm':

            break;

            default:

                printf("Invalid post-filtering method.\n");
                exit(EXIT_FAILURE);

            break;

        }



        return obj;

    }

    void mod_sss_destroy(mod_sss_obj * obj) {

        free((void *) obj);

    }

    int mod_sss_process(mod_sss_obj * obj) {

        int rtnValue;


        return rtnValue;

    }

    int mod_sss_process_dds(mod_sss_obj * obj) {

    }

    int mod_sss_process_dgss(mod_sss_obj * obj) {

    }

    int mod_sss_process_dmvdr(mod_sss_obj * obj) {

    }

    void mod_sss_connect(mod_sss_obj * obj, msg_spectra_obj * in1, msg_tracks_obj * in2, msg_spectra_obj * out1, msg_spectra_obj * out2) {

    }

    void mod_sss_disconnect(mod_sss_obj * obj) {

    }

    mod_sss_cfg * mod_sss_cfg_construct(void) {

    }

    void mod_sss_cfg_destroy(mod_sss_cfg * cfg) {

    }

    void mod_sss_cfg_printf(const mod_sss_cfg * cfg) {
        
    }