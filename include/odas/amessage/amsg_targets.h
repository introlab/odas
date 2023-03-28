#ifndef __ODAS_AMESSAGE_TARGETS
#define __ODAS_AMESSAGE_TARGETS

    /**
    * \file     amsg_targets.h
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

    #include "../message/msg_targets.h"
    #include "../utils/fifo.h"

    typedef struct amsg_targets_obj {

        unsigned int nMessages;
        fifo_obj * filled;
        fifo_obj * empty;

    } amsg_targets_obj;

    amsg_targets_obj * amsg_targets_construct(const unsigned int nMessages, const msg_targets_cfg * msg_targets_config);

    void amsg_targets_destroy(amsg_targets_obj * obj);

    msg_targets_obj * amsg_targets_filled_pop(amsg_targets_obj * obj);

    void amsg_targets_filled_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets);

    msg_targets_obj * amsg_targets_empty_pop(amsg_targets_obj * obj);

    void amsg_targets_empty_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets);

#endif