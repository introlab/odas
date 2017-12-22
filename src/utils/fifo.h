#ifndef __ODAS_UTILS_FIFO
#define __ODAS_UTILS_FIFO

    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdio.h>

    typedef struct fifo_obj {

        void ** array;
        unsigned int nElements;
        unsigned int nMaxElements;

        pthread_mutex_t use;
        sem_t push;
        sem_t pop;

    } fifo_obj;

    fifo_obj * fifo_construct_zero(const unsigned int nMaxElements);

    void fifo_destroy(fifo_obj * obj);

    void fifo_push(fifo_obj * obj, void * element);

    void * fifo_pop(fifo_obj * obj);

    int fifo_nElements(fifo_obj * obj);

    void fifo_printf(const fifo_obj * obj);

#endif