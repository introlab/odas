
   /**
    * \file     thread.c
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
    
    #include <general/thread.h>

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
    
