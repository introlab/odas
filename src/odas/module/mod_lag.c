    
    /**
    * \file     mod_lag.c
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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


    #include <module/mod_lag.h>

    mod_lag_obj * mod_lag_construct(const mod_lag_cfg * mod_lag_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_lag_obj * obj;
        unsigned int iElement;

        obj = (mod_lag_obj *) malloc(sizeof(mod_lag_obj));

        if (mod_lag_config->nElements == 0) {
            printf("The number of elements must be at least 1\n");
            exit(EXIT_FAILURE);
        }

        obj->nElements = mod_lag_config->nElements;

        obj->freqs = (freqs_obj **) malloc(sizeof(freqs_obj *) * obj->nElements);

        for (iElement = 0; iElement < obj->nElements; iElement++) {

            obj->freqs[iElement] = freqs_construct_zero(msg_spectra_config->nChannels, msg_spectra_config->halfFrameSize);

        }

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

        return obj;

    }

    void mod_lag_destroy(mod_lag_obj * obj) {

        unsigned int iElement;

        for (iElement = 0; iElement < obj->nElements; iElement++) {

            freqs_destroy(obj->freqs[iElement]);

        }

        free((void *) obj->freqs);

        free((void *) obj);

    }

    int mod_lag_process(mod_lag_obj * obj) {

        unsigned int iElement;

        int rtnValue;

        if (msg_spectra_isZero(obj->in) == 0) {

            for (iElement = 0; iElement < (obj->nElements - 1); iElement++) {

                freqs_copy(obj->freqs[obj->nElements - iElement - 1], obj->freqs[obj->nElements - iElement - 2]);

            }

            freqs_copy(obj->freqs[0], obj->in->freqs);
            freqs_copy(obj->out->freqs, obj->freqs[obj->nElements - 1]);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_lag_connect(mod_lag_obj * obj, msg_spectra_obj * in, msg_spectra_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_lag_disconnect(mod_lag_obj * obj) {

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

    }

    mod_lag_cfg * mod_lag_cfg_construct(void) {

        mod_lag_cfg * cfg;

        cfg = (mod_lag_cfg *) malloc(sizeof(mod_lag_cfg));

        return cfg;

    }

    void mod_lag_cfg_destroy(mod_lag_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_lag_cfg_printf(const mod_lag_cfg * cfg) {

    }