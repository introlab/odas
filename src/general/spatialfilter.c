
   /**
    * \file     spatialfilter.c
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
    
    #include <general/spatialfilter.h>

    spatialfilter_obj * spatialfilter_construct_zero(void) {

        spatialfilter_obj * obj;

        obj = (spatialfilter_obj *) malloc(sizeof(spatialfilter_obj));

        obj->direction = (float *) malloc(sizeof(float) * 3);
        memset(obj->direction, 0x00, sizeof(float) * 3);

        obj->thetaAllPass = 0.0f;
        obj->thetaNoPass = 0.0f;

        return obj;

    }

    spatialfilter_obj * spatialfilter_clone(const spatialfilter_obj * obj) {

        spatialfilter_obj * clone;

        clone = (spatialfilter_obj *) malloc(sizeof(spatialfilter_obj));

        clone->direction = (float *) malloc(sizeof(float) * 3);
        memcpy(clone->direction, obj->direction, sizeof(float) * 3);

        clone->thetaAllPass = obj->thetaAllPass;
        clone->thetaNoPass = obj->thetaNoPass;

        return clone;

    }

    void spatialfilter_destroy(spatialfilter_obj * obj) {

        free((void *) obj->direction);
        free((void *) obj);

    }

    void spatialfilter_printf(const spatialfilter_obj * obj) {

        printf("direction = (%+1.3f,%+1.3f,%+1.3f)\n", obj->direction[0], obj->direction[1], obj->direction[2]);
        printf("thetaAllPass = %f\n", obj->thetaAllPass);
        printf("thetaNoPass = %f\n", obj->thetaNoPass);

    }
