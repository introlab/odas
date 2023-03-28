#ifndef __ODAS_AMESSAGE_SPECTRA
#define __ODAS_AMESSAGE_SPECTRA

    /**
    * \file     amsg_spectra.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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