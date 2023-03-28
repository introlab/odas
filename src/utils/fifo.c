   
   /**
    * \file     fifo.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *
    */

    #include <utils/fifo.h>

    fifo_obj * fifo_construct_zero(const unsigned int nMaxElements) {

        fifo_obj * obj;

        obj = (fifo_obj *) malloc(sizeof(fifo_obj));

        obj->array = (void **) malloc(sizeof(void *) * nMaxElements);
        memset(obj->array, 0x00, sizeof(void *) * nMaxElements);

        obj->nElements = 0;
        obj->nMaxElements = nMaxElements;

        pthread_mutex_init(&(obj->use), NULL);
        sem_init(&(obj->pop), 0, 0);
        sem_init(&(obj->push), 0, nMaxElements);

        return obj;

    }

    void fifo_destroy(fifo_obj * obj) {

        sem_destroy(&(obj->pop));
        sem_destroy(&(obj->push));
        pthread_mutex_destroy(&(obj->use));
        free((void *) obj->array);
        free((void *) obj);

    }

    void fifo_push(fifo_obj * obj, void * element) {

        sem_wait(&(obj->push));

        pthread_mutex_lock(&(obj->use));

        obj->array[obj->nElements] = element;
        obj->nElements++;

        pthread_mutex_unlock(&(obj->use));

        sem_post(&(obj->pop));

    }

    void * fifo_pop(fifo_obj * obj) {

        void * rtnPtr;

        sem_wait(&(obj->pop));

        pthread_mutex_lock(&(obj->use));

        rtnPtr = obj->array[0];
        memmove(&(obj->array[0]), &(obj->array[1]), (obj->nElements-1) * sizeof(void *));
        obj->nElements--;
        memset(&(obj->array[obj->nElements]), 0x00, (obj->nMaxElements-obj->nElements) * sizeof(void *));

        pthread_mutex_unlock(&(obj->use));

        sem_post(&(obj->push));

        return rtnPtr;

    }

    int fifo_nElements(fifo_obj * obj) {

        int nElements;

        pthread_mutex_lock(&(obj->use));
        nElements = obj->nElements;
        pthread_mutex_unlock(&(obj->use));

        return nElements;

    }

    void fifo_printf(const fifo_obj * obj) {

        unsigned int iElement;

        for (iElement = 0; iElement < obj->nMaxElements; iElement++) {

            printf("(%03u): %p\n",iElement,obj->array[iElement]);

        }

    }
