
    /**
    * \file     amod_stft.c
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

    #include <amodule/amod_stft.h>

    amod_stft_obj * amod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config) {

        amod_stft_obj * obj;

        obj = (amod_stft_obj *) malloc(sizeof(amod_stft_obj));

        obj->mod_stft = mod_stft_construct(mod_stft_config, msg_hops_config, msg_spectra_config);
        
        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

        obj->thread = thread_construct(&amod_stft_thread, (void *) obj);

        mod_stft_disable(obj->mod_stft);

        return obj;

    }

    void amod_stft_destroy(amod_stft_obj * obj) {

        mod_stft_destroy(obj->mod_stft);
        thread_destroy(obj->thread);

        free((void *) obj);           

    }

    void amod_stft_connect(amod_stft_obj * obj, amsg_hops_obj * in, amsg_spectra_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_stft_disconnect(amod_stft_obj * obj) {

        obj->in = (amsg_hops_obj *) NULL;
        obj->out = (amsg_spectra_obj *) NULL;

    }

    void amod_stft_enable(amod_stft_obj * obj) {

        mod_stft_enable(obj->mod_stft);

    }

    void amod_stft_disable(amod_stft_obj * obj) {

        mod_stft_disable(obj->mod_stft);

    }

    void * amod_stft_thread(void * ptr) {

        amod_stft_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_spectra_obj * msg_spectra_out;
        int rtnValue;

        obj = (amod_stft_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in);
            msg_spectra_out = amsg_spectra_empty_pop(obj->out);
            mod_stft_connect(obj->mod_stft, msg_hops_in, msg_spectra_out);
            rtnValue = mod_stft_process(obj->mod_stft);
            mod_stft_disconnect(obj->mod_stft);
            amsg_hops_empty_push(obj->in, msg_hops_in);
            amsg_spectra_filled_push(obj->out, msg_spectra_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
