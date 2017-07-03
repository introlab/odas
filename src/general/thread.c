    
    #include "thread.h"

    thread_obj * thread_construct(void * (* start_routine) (void *), void * arg) {

        thread_obj * obj;

        obj = (thread_obj *) malloc(sizeof(thread_obj));

        pthread_mutex_init(&(obj->use), NULL);
        obj->stop = 0;
        obj->start_routine = start_routine;
        obj->arg = arg;

        return obj;

    }

    void thread_destroy(thread_obj * obj) {

        pthread_mutex_destroy(&(obj->use));

        free((void *) obj);

    }

    void thread_start(thread_obj * obj) {

        pthread_mutex_lock(&(obj->use));
        obj->stop = 0;
        pthread_create(&(obj->thread), NULL, obj->start_routine, obj->arg);
        pthread_mutex_unlock(&(obj->use));

    }

    void thread_stop(thread_obj * obj) {

        pthread_mutex_lock(&(obj->use));
        obj->stop = 1;
        pthread_mutex_unlock(&(obj->use));

    }

    char thread_askedToStop(thread_obj * obj) {

        char rtnValue;        

        pthread_mutex_lock(&(obj->use));
        rtnValue = obj->stop;
        pthread_mutex_unlock(&(obj->use));

        return rtnValue;        

    }

    void thread_join(thread_obj * obj) {

        pthread_join(obj->thread, NULL);

    }
    