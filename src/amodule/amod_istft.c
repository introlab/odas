
    /**
    * \file     amod_istft.c
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
    
    #include <amodule/amod_istft.h>

    amod_istft_obj * amod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config) {

        amod_istft_obj * obj;

        obj = (amod_istft_obj *) malloc(sizeof(amod_istft_obj));

        obj->mod_istft = mod_istft_construct(mod_istft_config, msg_spectra_config, msg_hops_config);
        
        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;        

        obj->thread = thread_construct(&amod_istft_thread, (void *) obj);

        return obj;

    }

    void amod_istft_destroy(amod_istft_obj * obj) {

        mod_istft_destroy(obj->mod_istft);
        thread_destroy(obj->thread);

        free((void *) obj);   

    }

    void amod_istft_connect(amod_istft_obj * obj, amsg_spectra_obj * in, amsg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void amod_istft_disconnect(amod_istft_obj * obj) {

        obj->in = (amsg_spectra_obj *) NULL;
        obj->out = (amsg_hops_obj *) NULL;

    }

    void * amod_istft_thread(void * ptr) {

        amod_istft_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (amod_istft_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in);
            msg_hops_out = amsg_hops_empty_pop(obj->out);
            mod_istft_connect(obj->mod_istft, msg_spectra_in, msg_hops_out);
            rtnValue = mod_istft_process(obj->mod_istft);
            mod_istft_disconnect(obj->mod_istft);
            amsg_spectra_empty_push(obj->in, msg_spectra_in);
            amsg_hops_filled_push(obj->out, msg_hops_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
