    
    #include "amsg_powers.h"

    amsg_powers_obj * amsg_powers_construct(const unsigned int nMessages, const msg_powers_cfg * msg_powers_config) {

        amsg_powers_obj * obj;
        unsigned int iMessage;

        obj = (amsg_powers_obj *) malloc(sizeof(amsg_powers_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_powers_construct(msg_powers_config));

        }

        return obj;

    }

    void amsg_powers_destroy(amsg_powers_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_powers_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_powers_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_powers_obj * amsg_powers_filled_pop(amsg_powers_obj * obj) {

        return ((msg_powers_obj *) fifo_pop(obj->filled));

    }

    void amsg_powers_filled_push(amsg_powers_obj * obj, msg_powers_obj * msg_powers) {

        fifo_push(obj->filled, (void *) msg_powers);

    }

    msg_powers_obj * amsg_powers_empty_pop(amsg_powers_obj * obj) {

        return ((msg_powers_obj *) fifo_pop(obj->empty));

    }

    void amsg_powers_empty_push(amsg_powers_obj * obj, msg_powers_obj * msg_powers) {

        fifo_push(obj->empty, (void *) msg_powers);

    }