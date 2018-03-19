
   /**
    * \file     soundspeed.c
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
    
    #include <general/soundspeed.h>

    soundspeed_obj * soundspeed_construct_zero(void) {

        soundspeed_obj * obj;

        obj = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        obj->mu = 0.0f;
        obj->sigma2 = 0.0f;

        return obj;

    }

    soundspeed_obj * soundspeed_clone(const soundspeed_obj * obj) {

        soundspeed_obj * clone;

        clone = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        clone->mu = obj->mu;
        clone->sigma2 = obj->sigma2;

        return clone;

    }

    void soundspeed_destroy(soundspeed_obj * obj) {

        free((void *) obj);

    }

    void soundspeed_printf(const soundspeed_obj * obj) {

        printf("mu = %f\n",obj->mu);
        printf("sigma2 = %f\n",obj->sigma2);

    }
