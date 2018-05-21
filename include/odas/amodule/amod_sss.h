#ifndef __ODAS_AMODULE_SSS
#define __ODAS_AMODULE_SSS

    /**
    * \file     amod_sss.h
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

    #include "../module/mod_sss.h"
    #include "../amessage/amsg_powers.h"
    #include "../amessage/amsg_tracks.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_sss_obj {

        mod_sss_obj * mod_sss;
        amsg_spectra_obj * in1;
        amsg_powers_obj * in2;
        amsg_tracks_obj * in3;
        amsg_spectra_obj * out1;
        amsg_spectra_obj * out2;
        thread_obj * thread;    

    } amod_sss_obj;

    amod_sss_obj * amod_sss_construct(const mod_sss_cfg * mod_sss_config, const msg_tracks_cfg * msg_tracks_config, const msg_spectra_cfg * msg_spectra_config);

    void amod_sss_destroy(amod_sss_obj * obj);

    void amod_sss_connect(amod_sss_obj * obj, amsg_spectra_obj * in1, amsg_powers_obj * in2, amsg_tracks_obj * in3, amsg_spectra_obj * out1, amsg_spectra_obj * out2);

    void amod_sss_disconnect(amod_sss_obj * obj);

    void amod_sss_enable(amod_sss_obj * obj);

    void amod_sss_disable(amod_sss_obj * obj);

    void * amod_sss_thread(void * ptr);        

#endif