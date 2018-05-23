#ifndef __ODAS_AMODULE_SSL
#define __ODAS_AMODULE_SSL

    /**
    * \file     amod_ssl.h
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

    #include "../module/mod_ssl.h"
    #include "../amessage/amsg_spectra.h"
    #include "../amessage/amsg_powers.h"
    #include "../amessage/amsg_pots.h"
    #include "../general/thread.h"

    typedef struct amod_ssl_obj {

        mod_ssl_obj * mod_ssl;
        amsg_spectra_obj * in;
        amsg_pots_obj * out;
        thread_obj * thread;    

    } amod_ssl_obj;

    amod_ssl_obj * amod_ssl_construct(const mod_ssl_cfg * mod_ssl_config, const msg_spectra_cfg * msg_spectra_config, const msg_pots_cfg * msg_pots_config);

    void amod_ssl_destroy(amod_ssl_obj * obj);

    void amod_ssl_connect(amod_ssl_obj * obj, amsg_spectra_obj * in, amsg_pots_obj * out);

    void amod_ssl_disconnect(amod_ssl_obj * obj);

    void amod_ssl_enable(amod_ssl_obj * obj);

    void amod_ssl_disable(amod_ssl_obj * obj);

    void * amod_ssl_thread(void * ptr);    

#endif