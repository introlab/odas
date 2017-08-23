    
    #include "amsg_envs.h"

    amsg_envs_obj * amsg_envs_construct(const unsigned int nMessages, const msg_envs_cfg * msg_envs_config) {

        amsg_envs_obj * obj;
        unsigned int iMessage;

        obj = (amsg_envs_obj *) malloc(sizeof(amsg_envs_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_envs_construct(msg_envs_config));

        }

        return obj;

    }

    void amsg_envs_destroy(amsg_envs_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_envs_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_envs_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_envs_obj * amsg_envs_filled_pop(amsg_envs_obj * obj) {

        return ((msg_envs_obj *) fifo_pop(obj->filled));

    }

    void amsg_envs_filled_push(amsg_envs_obj * obj, msg_envs_obj * msg_envs) {

        fifo_push(obj->filled, (void *) msg_envs);

    }

    msg_envs_obj * amsg_envs_empty_pop(amsg_envs_obj * obj) {

        return ((msg_envs_obj *) fifo_pop(obj->empty));

    }

    void amsg_envs_empty_push(amsg_envs_obj * obj, msg_envs_obj * msg_envs) {

        fifo_push(obj->empty, (void *) msg_envs);

    }