    
    #include <utils/share.h>

    share_obj * share_construct(void * ptr) {

    	share_obj * obj;

    	obj = (share_obj *) malloc(sizeof(share_obj));

    	obj->ptr = ptr;
        pthread_mutex_init(&(obj->use), NULL);   	

    	return obj;

    }

    void share_destroy(share_obj * obj) {

        pthread_mutex_destroy(&(obj->use));
    	free((void *) obj);

    }

    void * share_get(share_obj * obj) {

		pthread_mutex_lock(&(obj->use));
		return obj->ptr;

    }

    void share_release(share_obj * obj, void * ptr) {

    	if (ptr != obj->ptr) {
    		printf("Bad reference to shared element\n");
    		exit(EXIT_FAILURE);
    	}

    	pthread_mutex_unlock(&(obj->use));

    }