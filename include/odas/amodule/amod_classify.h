#ifndef __ODAS_AMODULE_CLASSIFY
#define __ODAS_AMODULE_CLASSIFY

    /**
    * \file     amod_classify.h
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

    #include "../module/mod_classify.h"
    #include "../amessage/amsg_hops.h"
    #include "../amessage/amsg_tracks.h"
    #include "../amessage/amsg_categories.h"
    #include "../general/thread.h"

    typedef struct amod_classify_obj {

        mod_classify_obj * mod_classify;
        amsg_hops_obj * in1;
        amsg_tracks_obj * in2;
        amsg_categories_obj * out;
        thread_obj * thread;    

    } amod_classify_obj;

    amod_classify_obj * amod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config, const msg_categories_cfg * msg_categories_config);

    void amod_classify_destroy(amod_classify_obj * obj);

    void amod_classify_connect(amod_classify_obj * obj, amsg_hops_obj * in1, amsg_tracks_obj * in2, amsg_categories_obj * out);

    void amod_classify_disconnect(amod_classify_obj * obj);

    void * amod_classify_thread(void * ptr);    

#endif