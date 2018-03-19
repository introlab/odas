
   /**
    * \file     mod_stft.c
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

    #include <module/mod_stft.h>

    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config) {

        mod_stft_obj * obj;

        obj = (mod_stft_obj *) malloc(sizeof(mod_stft_obj));

        obj->hop2frame =  hop2frame_construct_zero(msg_hops_config->hopSize, 2*(msg_spectra_config->halfFrameSize-1),msg_hops_config->nChannels);
        obj->frames = frames_construct_zero(msg_hops_config->nChannels,2*(msg_spectra_config->halfFrameSize-1));
        obj->frame2freq = frame2freq_construct_zero(2*(msg_spectra_config->halfFrameSize-1), msg_spectra_config->halfFrameSize);

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

        return obj;

    }

    void mod_stft_destroy(mod_stft_obj * obj) {

        hop2frame_destroy(obj->hop2frame);
        frames_destroy(obj->frames);
        frame2freq_destroy(obj->frame2freq);

        free((void *) obj);

    }

    int mod_stft_process(mod_stft_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            hop2frame_process(obj->hop2frame, obj->in->hops, obj->frames);
            frame2freq_process(obj->frame2freq, obj->frames, obj->out->freqs);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_spectra_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_stft_connect(mod_stft_obj * obj, msg_hops_obj * in, msg_spectra_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_stft_disconnect(mod_stft_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_spectra_obj *) NULL;

    }

    mod_stft_cfg * mod_stft_cfg_construct(void) {

        mod_stft_cfg * cfg;

        cfg = (mod_stft_cfg *) malloc(sizeof(mod_stft_cfg));

        return cfg;

    }

    void mod_stft_cfg_destroy(mod_stft_cfg * cfg) {

        free((void *) cfg);

    }


    void mod_stft_cfg_printf(const mod_stft_cfg * cfg) {

    }
