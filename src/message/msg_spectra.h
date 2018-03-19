#ifndef __ODAS_MESSAGE_SPECTRA
#define __ODAS_MESSAGE_SPECTRA

   /**
    * \file     msg_spectra.h
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

    #include "../signal/freq.h"

    typedef struct msg_spectra_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        freqs_obj * freqs;

    } msg_spectra_obj;

    typedef struct msg_spectra_cfg {

        unsigned int halfFrameSize;
        unsigned int nChannels;
        unsigned int fS;

    } msg_spectra_cfg;

    msg_spectra_obj * msg_spectra_construct(const msg_spectra_cfg * msg_spectra_config);

    void msg_spectra_destroy(msg_spectra_obj * obj);

    void msg_spectra_copy(msg_spectra_obj * dest, const msg_spectra_obj * src);

    void msg_spectra_zero(msg_spectra_obj * obj);

    unsigned int msg_spectra_isZero(const msg_spectra_obj * obj);

    msg_spectra_cfg * msg_spectra_cfg_construct(void);

    void msg_spectra_cfg_destroy(msg_spectra_cfg * msg_spectra_config);

    void msg_spectra_cfg_printf(const msg_spectra_cfg * msg_spectra_config);

#endif