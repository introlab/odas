
   /**
    * \file     msg_spectra.c
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
    
    #include <message/msg_spectra.h>

    msg_spectra_obj * msg_spectra_construct(const msg_spectra_cfg * msg_spectra_config) {

        msg_spectra_obj * obj;

        obj = (msg_spectra_obj *) malloc(sizeof(msg_spectra_obj));

        obj->timeStamp = 0;
        obj->fS = msg_spectra_config->fS;
        obj->freqs = freqs_construct_zero(msg_spectra_config->nChannels, msg_spectra_config->halfFrameSize);

        return obj;

    }

    void msg_spectra_destroy(msg_spectra_obj * obj) {

        freqs_destroy(obj->freqs);
        free((void *) obj);

    }

    void msg_spectra_copy(msg_spectra_obj * dest, const msg_spectra_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        freqs_copy(dest->freqs, src->freqs);

    }

    void msg_spectra_zero(msg_spectra_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        freqs_zero(obj->freqs);

    }

    unsigned int msg_spectra_isZero(const msg_spectra_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_spectra_cfg * msg_spectra_cfg_construct(void) {

        msg_spectra_cfg * cfg;

        cfg = (msg_spectra_cfg *) malloc(sizeof(msg_spectra_cfg));

        cfg->halfFrameSize = 0;
        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_spectra_cfg_destroy(msg_spectra_cfg * msg_spectra_config) {

        free((void *) msg_spectra_config);

    }

    void msg_spectra_cfg_printf(const msg_spectra_cfg * msg_spectra_config) {

        if (msg_spectra_config != NULL) {

            printf("halfFrameSize = %u\n", msg_spectra_config->halfFrameSize);
            printf("nChannels = %u\n", msg_spectra_config->nChannels);
            printf("fS = %u\n", msg_spectra_config->fS);

        }
        else {

            printf("(null)\n");

        }        

    }
