    
    #include "amsg_pots.h"

    amsg_pots_obj * amsg_pots_construct(const unsigned int nMessages, const msg_pots_cfg * msg_pots_config) {

        amsg_pots_obj * obj;
        unsigned int iMessage;

        obj = (amsg_pots_obj *) malloc(sizeof(amsg_pots_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_pots_construct(msg_pots_config));

        }

        return obj;        

    }

    void amsg_pots_destroy(amsg_pots_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_pots_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_pots_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_pots_obj * amsg_pots_filled_pop(amsg_pots_obj * obj) {

        return ((msg_pots_obj *) fifo_pop(obj->filled));

    }

    void amsg_pots_filled_push(amsg_pots_obj * obj, msg_pots_obj * msg_pots) {

        fifo_push(obj->filled, (void *) msg_pots);

    }

    msg_pots_obj * amsg_pots_empty_pop(amsg_pots_obj * obj) {

        return ((msg_pots_obj *) fifo_pop(obj->empty));

    }

    void amsg_pots_empty_push(amsg_pots_obj * obj, msg_pots_obj * msg_pots) {

        fifo_push(obj->empty, (void *) msg_pots);

    }