#ifndef __ODAS_CONNECTOR_POTS
#define __ODAS_CONNECTOR_POTS

   /**
    * \file     con_pots.h
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

    #include "../message/msg_pots.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_pots_obj {

        msg_pots_obj * in;
        msg_pots_obj ** outs;

        unsigned int nOuts;

    } con_pots_obj;

    con_pots_obj * con_pots_construct(const unsigned int nOuts, const msg_pots_cfg * msg_pots_config);

    void con_pots_destroy(con_pots_obj * obj);

    int con_pots_process(con_pots_obj * obj);

#endif