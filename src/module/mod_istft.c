
   /**
    * \file     mod_istft.c
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
    
    #include <module/mod_istft.h>
    
    mod_istft_obj * mod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config) {

        mod_istft_obj * obj;

        obj = (mod_istft_obj *) malloc(sizeof(mod_istft_obj));

        obj->freq2frame = freq2frame_construct_zero(2*(msg_spectra_config->halfFrameSize-1), msg_spectra_config->halfFrameSize);
        obj->frames = frames_construct_zero(msg_hops_config->nChannels,2*(msg_spectra_config->halfFrameSize-1));
        obj->frame2hop = frame2hop_construct_zero(msg_hops_config->hopSize, 2*(msg_spectra_config->halfFrameSize-1), msg_hops_config->nChannels);

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

        obj->enabled = 0;

        return obj;

    }

    void mod_istft_destroy(mod_istft_obj * obj) {

        freq2frame_destroy(obj->freq2frame);
        frames_destroy(obj->frames);
        frame2hop_destroy(obj->frame2hop);

        free((void *) obj);

    }

    int mod_istft_process(mod_istft_obj * obj) {

        int rtnValue;

        if (msg_spectra_isZero(obj->in) == 0) {

            if (obj->enabled == 1) {

                freq2frame_process(obj->freq2frame, obj->in->freqs, obj->frames);
                frame2hop_process(obj->frame2hop, obj->frames, obj->out->hops);

            }
            else {

                hops_zero(obj->out->hops);

            }

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_hops_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_istft_connect(mod_istft_obj * obj, msg_spectra_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_istft_disconnect(mod_istft_obj * obj) {

        obj->in = (msg_spectra_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    void mod_istft_enable(mod_istft_obj * obj) {

        obj->enabled = 1;

    }

    void mod_istft_disable(mod_istft_obj * obj) {

        obj->enabled = 0;

    }

    mod_istft_cfg * mod_istft_cfg_construct(void) {

        mod_istft_cfg * cfg;

        cfg = (mod_istft_cfg *) malloc(sizeof(mod_istft_cfg));

        return cfg;        

    }

    void mod_istft_cfg_destroy(mod_istft_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_istft_cfg_printf(const mod_istft_cfg * cfg) {

    }
