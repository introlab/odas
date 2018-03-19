#ifndef __ODAS_ASINK_SPECTRA
#define __ODAS_ASINK_SPECTRA

    /**
    * \file     asink_spectra.h
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

    #include "../amessage/amsg_spectra.h"
    #include "../sink/snk_spectra.h"
    #include "../general/thread.h"

    #include <stdlib.h>

    typedef struct asnk_spectra_obj {

        snk_spectra_obj * snk_spectra;
        amsg_spectra_obj * in;
        thread_obj * thread;

    } asnk_spectra_obj;

    asnk_spectra_obj * asnk_spectra_construct(const snk_spectra_cfg * snk_spectra_config, const msg_spectra_cfg * msg_spectra_config);

    void asnk_spectra_destroy(asnk_spectra_obj * obj);

    void asnk_spectra_connect(asnk_spectra_obj * obj, amsg_spectra_obj * in);

    void asnk_spectra_disconnect(asnk_spectra_obj * obj);

    void * asnk_spectra_thread(void * ptr);

#endif