   
   /**
    * \file     snk_spectra.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */
    
    #include <sink/snk_spectra.h>

    snk_spectra_obj * snk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config) {

        snk_spectra_obj * obj;

        obj = (snk_spectra_obj *) malloc(sizeof(snk_spectra_obj));

        obj->halfFrameSize = msg_spectra_config->halfFrameSize;
        obj->nChannels = msg_spectra_config->nChannels;
        obj->fS = msg_spectra_config->fS;
        
        obj->format = format_clone(snk_spectra_config->format);
        obj->interface = interface_clone(snk_spectra_config->interface);

        switch (obj->format->type) {
            
            case format_binary_float: break;
            default:

                printf("Invalid format.\n");
                exit(EXIT_FAILURE);

            break;

        }

        obj->in = (msg_spectra_obj *) NULL;

        return obj;

    }

    void snk_spectra_destroy(snk_spectra_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_spectra_connect(snk_spectra_obj * obj, msg_spectra_obj * in) {

        obj->in = in;

    }

    void snk_spectra_disconnect(snk_spectra_obj * obj) {

        obj->in = (msg_spectra_obj *) NULL;

    }

    void snk_spectra_open(snk_spectra_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_spectra_open_interface_blackhole(obj);

            break;

            default:

                printf("Sink spectra: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_spectra_open_interface_blackhole(snk_spectra_obj * obj) {

        // Empty

    }

    void snk_spectra_close(snk_spectra_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_spectra_close_interface_blackhole(obj);

            break;

            default:

                printf("Sink spectra: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_spectra_close_interface_blackhole(snk_spectra_obj * obj) {

        // Empty

    }

    int snk_spectra_process(snk_spectra_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_undefined:

                    snk_spectra_process_format_undefined(obj);

                break;

                default:

                    printf("Sink spectra: Invalid format type.\n");
                    exit(EXIT_FAILURE);

                break;                

            }

            switch(obj->interface->type) {

                case interface_blackhole:

                    snk_spectra_process_interface_blackhole(obj);

                break;

                default:

                    printf("Sink spectra: Invalid interface type.\n");
                    exit(EXIT_FAILURE);

                break;

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void snk_spectra_process_interface_blackhole(snk_spectra_obj * obj) {

        // Empty

    }

    void snk_spectra_process_format_undefined(snk_spectra_obj * obj) {

        // Empty

    }

    snk_spectra_cfg * snk_spectra_cfg_construct(void) {

        snk_spectra_cfg * cfg;

        cfg = (snk_spectra_cfg *) malloc(sizeof(snk_spectra_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_spectra_cfg_destroy(snk_spectra_cfg * snk_spectra_config) {

        if (snk_spectra_config->format != NULL) {
            format_destroy(snk_spectra_config->format);
        }
        if (snk_spectra_config->interface != NULL) {
            interface_destroy(snk_spectra_config->interface);
        }

        free((void *) snk_spectra_config);

    }
