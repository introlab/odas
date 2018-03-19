#ifndef __ODAS_CONNECTOR_SPECTRA
#define __ODAS_CONNECTOR_SPECTRA

   /**
    * \file     con_spectra.h
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

    #include "../message/msg_spectra.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct con_spectra_obj {

        msg_spectra_obj * in;
        msg_spectra_obj ** outs;

        unsigned int nOuts;

    } con_spectra_obj;

    con_spectra_obj * con_spectra_construct(const unsigned int nOuts, const msg_spectra_cfg * msg_spectra_config);

    void con_spectra_destroy(con_spectra_obj * obj);

    int con_spectra_process(con_spectra_obj * obj);

#endif