
    /**
    * \file     amod_sss.c
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

    #include <amodule/amod_sss.h>

    amod_sss_obj * amod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config) {

        amod_sss_obj * obj;

        obj = (amod_sss_obj *) malloc(sizeof(amod_sss_obj));

        obj->mod_sss = mod_sss_construct(mod_sss_config, msg_tracks_config, msg_spectra_config);

        obj->in1 = (amsg_spectra_obj *) NULL;
        obj->in2 = (amsg_powers_obj *) NULL;
        obj->in3 = (amsg_tracks_obj *) NULL;
        obj->out1 = (amsg_spectra_obj *) NULL;
        obj->out2 = (amsg_spectra_obj *) NULL;
        
        obj->thread = thread_construct(&amod_sss_thread, (void *) obj);

        return obj;

    }

    void amod_sss_destroy(amod_sss_obj * obj) {

        mod_sss_destroy(obj->mod_sss);
        thread_destroy(obj->thread);

        free((void *) obj); 

    }

    void amod_sss_connect(amod_sss_obj * obj, amsg_spectra_obj * in1, amsg_powers_obj * in2, amsg_tracks_obj * in3, amsg_spectra_obj * out1, amsg_spectra_obj * out2) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->in3 = in3;
        obj->out1 = out1;
        obj->out2 = out2;

    }

    void amod_sss_disconnect(amod_sss_obj * obj) {

        obj->in1 = (amsg_spectra_obj *) NULL;
        obj->in2 = (amsg_powers_obj *) NULL;
        obj->in3 = (amsg_tracks_obj *) NULL;
        obj->out1 = (amsg_spectra_obj *) NULL;
        obj->out2 = (amsg_spectra_obj *) NULL;

    }

    void * amod_sss_thread(void * ptr) {

        amod_sss_obj * obj;
        msg_spectra_obj * msg_spectra_in;
        msg_powers_obj * msg_powers_in;
        msg_tracks_obj * msg_tracks_in;
        msg_spectra_obj * msg_spectra_out1;
        msg_spectra_obj * msg_spectra_out2;
        int rtnValue;

        obj = (amod_sss_obj *) ptr;

        while(1) {

            // Pop a message, process, and push back
            msg_spectra_in = amsg_spectra_filled_pop(obj->in1);
            msg_powers_in = amsg_powers_filled_pop(obj->in2);
            msg_tracks_in = amsg_tracks_filled_pop(obj->in3);
            msg_spectra_out1 = amsg_spectra_empty_pop(obj->out1);
            msg_spectra_out2 = amsg_spectra_empty_pop(obj->out2);
            mod_sss_connect(obj->mod_sss, msg_spectra_in, msg_powers_in, msg_tracks_in, msg_spectra_out1, msg_spectra_out2);
            rtnValue = mod_sss_process(obj->mod_sss);
            mod_sss_disconnect(obj->mod_sss);
            amsg_spectra_empty_push(obj->in1, msg_spectra_in);
            amsg_powers_empty_push(obj->in2, msg_powers_in);
            amsg_tracks_empty_push(obj->in3, msg_tracks_in);
            amsg_spectra_filled_push(obj->out1, msg_spectra_out1);
            amsg_spectra_filled_push(obj->out2, msg_spectra_out2);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

    }
