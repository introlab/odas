
    /**
    * \file     amsg_targets.c
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
    
    #include <amessage/amsg_targets.h>

    amsg_targets_obj * amsg_targets_construct(const unsigned int nMessages, const msg_targets_cfg * msg_targets_config) {

        amsg_targets_obj * obj;
        unsigned int iMessage;

        obj = (amsg_targets_obj *) malloc(sizeof(amsg_targets_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_targets_construct(msg_targets_config));

        }

        return obj;   

    }

    void amsg_targets_destroy(amsg_targets_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_targets_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_targets_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_targets_obj * amsg_targets_filled_pop(amsg_targets_obj * obj) {

        return ((msg_targets_obj *) fifo_pop(obj->filled));

    }

    void amsg_targets_filled_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets) {

        fifo_push(obj->filled, (void *) msg_targets);

    }

    msg_targets_obj * amsg_targets_empty_pop(amsg_targets_obj * obj) {

        return ((msg_targets_obj *) fifo_pop(obj->empty));

    }

    void amsg_targets_empty_push(amsg_targets_obj * obj, msg_targets_obj * msg_targets) {

        fifo_push(obj->empty, (void *) msg_targets);

    }
