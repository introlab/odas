#ifndef __ODAS_AMODULE_NOISE
#define __ODAS_AMODULE_NOISE

    /**
    * \file     amod_noise.h
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

    #include "../module/mod_noise.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_powers.h"
    #include "../general/thread.h"

    typedef struct amod_noise_obj {

        mod_noise_obj * mod_noise;
        amsg_spectra_obj * in;
        amsg_powers_obj * out;
        thread_obj * thread;    

    } amod_noise_obj;

    amod_noise_obj * amod_noise_construct(const mod_noise_cfg * mod_noise_config, const msg_spectra_cfg * msg_spectra_config, const msg_powers_cfg * msg_powers_config);

    void amod_noise_destroy(amod_noise_obj * obj);

    void amod_noise_connect(amod_noise_obj * obj, amsg_spectra_obj * in, amsg_powers_obj * out);

    void amod_noise_disconnect(amod_noise_obj * obj);

    void amod_noise_enable(amod_noise_obj * obj);

    void amod_noise_disable(amod_noise_obj * obj);

    void * amod_noise_thread(void * ptr);    

#endif