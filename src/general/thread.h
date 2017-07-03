#ifndef __ODAS_GENERAL_THREAD
#define __ODAS_GENERAL_THREAD

    #include <stdlib.h>
    #include <stdio.h>
    #include <pthread.h>

    typedef struct thread_obj {

        pthread_mutex_t use;
        char stop;
        pthread_t thread;   
        void * (* start_routine) (void *);
        void * arg;     

    } thread_obj;

    thread_obj * thread_construct(void * (* start_routine) (void *), void * arg);

    void thread_destroy(thread_obj * obj);

    void thread_start(thread_obj * obj);

    void thread_stop(thread_obj * obj);

    char thread_askedToStop(thread_obj * obj);

    void thread_join(thread_obj * obj); 

#endif