#ifndef __ODAS_MODULE_TT
#define __ODAS_MODULE_TT

   /**
    * \file     mod_tt.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-30
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
  
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>

    #include "../message/msg_targets.h"
    #include "../message/msg_tracks.h"

    typedef struct mod_tt_obj {

        unsigned int nTracks;
        unsigned int nTargets;

        unsigned long long id;

        char ** tags;
        unsigned long long * ids;
        float * array;

        msg_targets_obj * in;
        msg_tracks_obj * out;

        char enabled;

    } mod_tt_obj;

    typedef struct mod_tt_cfg {

    } mod_tt_cfg;

    mod_tt_obj * mod_tt_construct(const mod_tt_cfg * mod_tt_config, const msg_targets_cfg * msg_targets_config, const msg_tracks_cfg * msg_tracks_config);

    void mod_tt_destroy(mod_tt_obj * obj);

    int mod_tt_process(mod_tt_obj * obj);

    void mod_tt_connect(mod_tt_obj * obj, msg_targets_obj * in, msg_tracks_obj * out);

    void mod_tt_disconnect(mod_tt_obj * obj);

    void mod_tt_enable(mod_tt_obj * obj);

    void mod_tt_disable(mod_tt_obj * obj);

    mod_tt_cfg * mod_tt_cfg_construct(void);

    void mod_tt_cfg_destroy(mod_tt_cfg * cfg);

    void mod_tt_cfg_printf(const mod_tt_cfg * cfg);

#endif