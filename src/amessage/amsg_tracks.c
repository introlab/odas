    
    #include "amsg_tracks.h"

    amsg_tracks_obj * amsg_tracks_construct(const unsigned int nMessages, const msg_tracks_cfg * msg_tracks_config) {

        amsg_tracks_obj * obj;
        unsigned int iMessage;

        obj = (amsg_tracks_obj *) malloc(sizeof(amsg_tracks_obj));

        obj->nMessages = nMessages;
        obj->filled = fifo_construct_zero(nMessages);
        obj->empty = fifo_construct_zero(nMessages);

        for (iMessage = 0; iMessage < nMessages; iMessage++) {

            fifo_push(obj->empty, (void *) msg_tracks_construct(msg_tracks_config));

        }

        return obj;   

    }

    void amsg_tracks_destroy(amsg_tracks_obj * obj) {

        while(fifo_nElements(obj->filled) > 0) {
            msg_tracks_destroy((void *) fifo_pop(obj->filled));
        }

        while(fifo_nElements(obj->empty) > 0) {
            msg_tracks_destroy((void *) fifo_pop(obj->empty));
        }

        fifo_destroy(obj->filled);
        fifo_destroy(obj->empty);

        free((void *) obj);

    }

    msg_tracks_obj * amsg_tracks_filled_pop(amsg_tracks_obj * obj) {

        return ((msg_tracks_obj *) fifo_pop(obj->filled));

    }

    void amsg_tracks_filled_push(amsg_tracks_obj * obj, msg_tracks_obj * msg_tracks) {

        fifo_push(obj->filled, (void *) msg_tracks);

    }

    msg_tracks_obj * amsg_tracks_empty_pop(amsg_tracks_obj * obj) {

        return ((msg_tracks_obj *) fifo_pop(obj->empty));

    }

    void amsg_tracks_empty_push(amsg_tracks_obj * obj, msg_tracks_obj * msg_tracks) {

        fifo_push(obj->empty, (void *) msg_tracks);

    }