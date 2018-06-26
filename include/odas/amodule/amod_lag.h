#ifndef __ODAS_AMODULE_LAG
#define __ODAS_AMODULE_LAG

    /**
    * \file     amod_lag.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-24
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

    #include "../module/mod_lag.h"
    #include "../amessage/amsg_spectra.h"
    #include "../general/thread.h"

    typedef struct amod_lag_obj {

        mod_lag_obj * mod_lag;
        amsg_spectra_obj * in;
        amsg_spectra_obj * out;
        thread_obj * thread;        

    } amod_lag_obj;

    amod_lag_obj * amod_lag_construct(const mod_lag_cfg * mod_lag_config, const msg_spectra_cfg * msg_spectra_config);

    void amod_lag_destroy(amod_lag_obj * obj);

    void amod_lag_connect(amod_lag_obj * obj, amsg_spectra_obj * in, amsg_spectra_obj * out);

    void amod_lag_disconnect(amod_lag_obj * obj);

    void * amod_lag_thread(void * ptr);    

#endif