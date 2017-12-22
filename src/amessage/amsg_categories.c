    
    #include "amsg_categories.h"

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
