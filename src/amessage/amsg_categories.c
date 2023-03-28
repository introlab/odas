
    /**
    * \file     amsg_categories.c
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
    
    #include <amessage/amsg_categories.h>

    amsg_categories_obj * amsg_categories_construct(const unsigned int nMessages, const msg_categories_cfg * msg_categories_config) {

        amsg_categories_obj * obj;
        unsigned int iMessage;

        obj = (amsg_categories_obj *) malloc(sizeof(amsg_categories_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_categories_construct(msg_categories_config));

        }

        return obj;

    }

    void amsg_categories_destroy(amsg_categories_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_categories_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_categories_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_categories_obj * amsg_categories_filled_pop(amsg_categories_obj * obj) {

        return ((msg_categories_obj *) fifo_pop(obj->filled));

    }

    void amsg_categories_filled_push(amsg_categories_obj * obj, msg_categories_obj * msg_categories) {

        fifo_push(obj->filled, (void *) msg_categories);

    }

    msg_categories_obj * amsg_categories_empty_pop(amsg_categories_obj * obj) {

        return ((msg_categories_obj *) fifo_pop(obj->empty));

    }

    void amsg_categories_empty_push(amsg_categories_obj * obj, msg_categories_obj * msg_categories) {

        fifo_push(obj->empty, (void *) msg_categories);

    }
