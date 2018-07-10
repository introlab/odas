
    /**
    * \file     share.c
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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