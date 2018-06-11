
   /**
    * \file     thread.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    
