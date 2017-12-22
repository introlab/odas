    
    #include "amsg_hops.h"

    amsg_hops_obj * amsg_hops_construct(const unsigned int nMessages, const msg_hops_cfg * msg_hops_config) {

        amsg_hops_obj * obj;
        unsigned int iMessage;

        obj = (amsg_hops_obj *) malloc(sizeof(amsg_hops_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_hops_construct(msg_hops_config));

        }

        return obj;

    }

    void amsg_hops_destroy(amsg_hops_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_hops_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_hops_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_hops_obj * amsg_hops_filled_pop(amsg_hops_obj * obj) {

        return ((msg_hops_obj *) fifo_pop(obj->filled));

    }

    void amsg_hops_filled_push(amsg_hops_obj * obj, msg_hops_obj * msg_hops) {

        fifo_push(obj->filled, (void *) msg_hops);

    }

    msg_hops_obj * amsg_hops_empty_pop(amsg_hops_obj * obj) {

        return ((msg_hops_obj *) fifo_pop(obj->empty));

    }

    void amsg_hops_empty_push(amsg_hops_obj * obj, msg_hops_obj * msg_hops) {

        fifo_push(obj->empty, (void *) msg_hops);

    }