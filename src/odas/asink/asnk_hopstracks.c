    
    #include <asink/asnk_hopstracks.h>

    asnk_hopstracks_obj * asnk_hopstracks_construct(const snk_hopstracks_cfg * snk_hopstracks_config, const msg_hops_cfg * msg_hops_config, const msg_tracks_cfg * msg_tracks_config) {

        asnk_hopstracks_obj * obj;

        obj = (asnk_hopstracks_obj *) malloc(sizeof(asnk_hopstracks_obj));

        obj->snk_hopstracks = snk_hopstracks_construct(snk_hopstracks_config, msg_hops_config, msg_tracks_config);
        obj->in1 = (amsg_hops_obj *) NULL;
        obj->in2 = (amsg_tracks_obj *) NULL;

        obj->thread = thread_construct(&asnk_hopstracks_thread, (void *) obj);

        return obj;

    }

    void asnk_hopstracks_destroy(asnk_hopstracks_obj * obj) {

        snk_hopstracks_destroy(obj->snk_hopstracks);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asnk_hopstracks_connect(asnk_hopstracks_obj * obj, amsg_hops_obj * in1, amsg_tracks_obj * in2) {

    	obj->in1 = in1;
    	obj->in2 = in2;

    }

    void asnk_hopstracks_disconnect(asnk_hopstracks_obj * obj) {

    	obj->in1 = (amsg_hops_obj *) NULL;
    	obj->in2 = (amsg_tracks_obj *) NULL;

    }

    void * asnk_hopstracks_thread(void * ptr) {

        asnk_hopstracks_obj * obj;
        msg_hops_obj * msg_hops_in;
        msg_tracks_obj * msg_tracks_in;
        int rtnValue;

        obj = (asnk_hopstracks_obj *) ptr;

        if ((obj->in1 == NULL) || (obj->in2 == NULL)) {
            printf("asnk_hopstracks: nothing connected to input\n");
            exit(EXIT_FAILURE);
        }

        // Open the sink
        snk_hopstracks_open(obj->snk_hopstracks);

        while(1) {

            // Pop a message, process, and push back
            msg_hops_in = amsg_hops_filled_pop(obj->in1);
            msg_tracks_in = amsg_tracks_filled_pop(obj->in2);
            snk_hopstracks_connect(obj->snk_hopstracks, msg_hops_in, msg_tracks_in);
            rtnValue = snk_hopstracks_process(obj->snk_hopstracks);
            snk_hopstracks_disconnect(obj->snk_hopstracks);
            amsg_hops_empty_push(obj->in1, msg_hops_in);
            amsg_tracks_empty_push(obj->in2, msg_tracks_in);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

        }

        // Close the sink
        snk_hopstracks_close(obj->snk_hopstracks);

    }
