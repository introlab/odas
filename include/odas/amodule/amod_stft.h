#ifndef __ODAS_AMODULE_STFT
#define __ODAS_AMODULE_STFT

    /**
    * \file     amod_stft.h
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

    #include "../module/mod_stft.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_stft_obj {

        mod_stft_obj * mod_stft;
        amsg_hops_obj * in;
        amsg_spectra_obj * out;
        thread_obj * thread;    

    } amod_stft_obj;

    amod_stft_obj * amod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config);

    void amod_stft_destroy(amod_stft_obj * obj);

    void amod_stft_connect(amod_stft_obj * obj, amsg_hops_obj * in, amsg_spectra_obj * out);

    void amod_stft_disconnect(amod_stft_obj * obj);

    void amod_stft_enable(amod_stft_obj * obj);

    void amod_stft_disable(amod_stft_obj * obj);

    void * amod_stft_thread(void * ptr);    

#endif