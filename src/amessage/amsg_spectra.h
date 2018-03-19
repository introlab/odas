#ifndef __ODAS_AMESSAGE_SPECTRA
#define __ODAS_AMESSAGE_SPECTRA

    /**
    * \file     amsg_spectra.h
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

    #include <stdlib.h>

    #include "../message/msg_spectra.h"
    #include "../utils/fifo.h"

    typedef struct amsg_spectra_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_spectra_obj;

    amsg_spectra_obj * amsg_spectra_construct(const unsigned int nMessages, const msg_spectra_cfg * msg_spectra_config);

    void amsg_spectra_destroy(amsg_spectra_obj * obj);

    msg_spectra_obj * amsg_spectra_filled_pop(amsg_spectra_obj * obj);

    void amsg_spectra_filled_push(amsg_spectra_obj * obj, msg_spectra_obj * msg_spectra);

    msg_spectra_obj * amsg_spectra_empty_pop(amsg_spectra_obj * obj);

    void amsg_spectra_empty_push(amsg_spectra_obj * obj, msg_spectra_obj * msg_spectra);

#endif