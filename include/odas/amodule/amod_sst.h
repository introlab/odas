#ifndef __ODAS_AMODULE_SST
#define __ODAS_AMODULE_SST

    /**
    * \file     amod_sst.h
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
    #include "../module/mod_sst.h"
    #include "../amessage/amsg_pots.h"
    #include "../amessage/amsg_targets.h"
    #include "../amessage/amsg_tracks.h"
    #include "../general/thread.h"

    typedef struct amod_sst_obj {

        mod_sst_obj * mod_sst;
        amsg_pots_obj * in1;
        amsg_targets_obj * in2;
        amsg_tracks_obj * out;
        thread_obj * thread;    

    } amod_sst_obj;

    amod_sst_obj * amod_sst_construct(const mod_sst_cfg * mod_sst_config, const mod_ssl_cfg * mod_ssl_config, const msg_pots_cfg * msg_pots_config, const msg_targets_cfg * msg_targets_config, const msg_tracks_cfg * msg_tracks_config);

    void amod_sst_destroy(amod_sst_obj * obj);

    void amod_sst_connect(amod_sst_obj * obj, amsg_pots_obj * in1, amsg_targets_obj * in2, amsg_tracks_obj * out);

    void amod_sst_disconnect(amod_sst_obj * obj);

    void amod_sst_enable(amod_sst_obj * obj);

    void amod_sst_disable(amod_sst_obj * obj);

    void * amod_sst_thread(void * ptr);    

#endif