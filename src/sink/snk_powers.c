   
   /**
    * \file     snk_powers.c
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
    
    #include <sink/snk_powers.h>

    snk_powers_obj * snk_powers_construct(const snk_powers_cfg * snk_powers_config, const msg_powers_cfg * msg_powers_config) {

        snk_powers_obj * obj;

        obj = (snk_powers_obj *) malloc(sizeof(snk_powers_obj));

        obj->halfFrameSize = msg_powers_config->halfFrameSize;
        obj->nChannels = msg_powers_config->nChannels;
        obj->fS = msg_powers_config->fS;
        
        obj->format = format_clone(snk_powers_config->format);
        obj->interface = interface_clone(snk_powers_config->interface);

        if (!((obj->interface->type == interface_blackhole)  && (obj->format->type == format_undefined))) {
            
            printf("Sink powers: Invalid interface and/or format.\n");
            exit(EXIT_FAILURE);

        }

        obj->in = (msg_powers_obj *) NULL;

        return obj;

    }

    void snk_powers_destroy(snk_powers_obj * obj) {

        format_destroy(obj->format);
        interface_destroy(obj->interface);

        free((void *) obj);

    }

    void snk_powers_connect(snk_powers_obj * obj, msg_powers_obj * in) {

        obj->in = in;

    }

    void snk_powers_disconnect(snk_powers_obj * obj) {

        obj->in = (msg_powers_obj *) NULL;

    }

    void snk_powers_open(snk_powers_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_powers_open_interface_blackhole(obj);

            break;

            default:

                printf("Sink powers: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_powers_open_interface_blackhole(snk_powers_obj * obj) {

        // Empty

    }

    void snk_powers_close(snk_powers_obj * obj) {

        switch(obj->interface->type) {

            case interface_blackhole:

                snk_powers_close_interface_blackhole(obj);

            break;

            default:

                printf("Sink powers: Invalid interface type.\n");
                exit(EXIT_FAILURE);

            break;

        }

    }

    void snk_powers_close_interface_blackhole(snk_powers_obj * obj) {

        // Empty

    }

    int snk_powers_process(snk_powers_obj * obj) {

        int rtnValue;

        if (obj->in->timeStamp != 0) {

            switch(obj->format->type) {

                case format_undefined:

                    snk_powers_process_format_undefined(obj);

                break;

                default:

                    printf("Sink powers: Invalid format type.\n");
                    exit(EXIT_FAILURE);

                break;                

            }

            switch(obj->interface->type) {

                case interface_blackhole:

                    snk_powers_process_interface_blackhole(obj);

                break;

                default:

                    printf("Sink powers: Invalid interface type.\n");
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

    void snk_powers_process_interface_blackhole(snk_powers_obj * obj) {

        // Empty

    }

    void snk_powers_process_format_undefined(snk_powers_obj * obj) {

        // Empty

    }

    snk_powers_cfg * snk_powers_cfg_construct(void) {

        snk_powers_cfg * cfg;

        cfg = (snk_powers_cfg *) malloc(sizeof(snk_powers_cfg));

        cfg->fS = 0;
        cfg->format = (format_obj *) NULL;
        cfg->interface = (interface_obj *) NULL;

        return cfg;

    }

    void snk_powers_cfg_destroy(snk_powers_cfg * snk_powers_config) {

        if (snk_powers_config->format != NULL) {
            format_destroy(snk_powers_config->format);
        }
        if (snk_powers_config->interface != NULL) {
            interface_destroy(snk_powers_config->interface);
        }

        free((void *) snk_powers_config);

    }
