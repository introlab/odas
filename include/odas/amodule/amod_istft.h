#ifndef __ODAS_AMODULE_ISTFT
#define __ODAS_AMODULE_ISTFT

    /**
    * \file     amod_istft.h
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

    #include "../module/mod_istft.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_hops.h"
    #include "../general/thread.h"

    typedef struct amod_istft_obj {

        mod_istft_obj * mod_istft;
        amsg_spectra_obj * in;
        amsg_hops_obj * out;
        thread_obj * thread;    

    } amod_istft_obj;

    amod_istft_obj * amod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config);

    void amod_istft_destroy(amod_istft_obj * obj);

    void amod_istft_connect(amod_istft_obj * obj, amsg_spectra_obj * in, amsg_hops_obj * out);

    void amod_istft_disconnect(amod_istft_obj * obj);

    void amod_istft_enable(amod_istft_obj * obj);

    void amod_istft_disable(amod_istft_obj * obj);

    void * amod_istft_thread(void * ptr);    

#endif