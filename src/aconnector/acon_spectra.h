#ifndef __ODAS_ACONNECTOR_SPECTRA
#define __ODAS_ACONNECTOR_SPECTRA

    /**
    * \file     acon_spectra.h
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

    #include "../connector/con_spectra.h"
    #include "../amessage/amsg_spectra.h"
    #include "../message/msg_spectra.h"
    #include "../general/thread.h"

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct acon_spectra_obj {

        amsg_spectra_obj * in;
        amsg_spectra_obj ** outs;
        con_spectra_obj * con_spectra;
        thread_obj * thread;

    } acon_spectra_obj;

    acon_spectra_obj * acon_spectra_construct(const unsigned int nOuts, const unsigned int nMessages, const msg_spectra_cfg * msg_spectra_config);

    void acon_spectra_destroy(acon_spectra_obj * obj);

    void * acon_spectra_thread(void * ptr);

#endif