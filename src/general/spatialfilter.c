
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

    spatialfilters_obj * spatialfilters_construct_zero(unsigned int nFilters) {

        spatialfilters_obj * obj;

        obj = (spatialfilters_obj *) malloc(sizeof(spatialfilters_obj));

        obj->nFilters = nFilters;

        obj->direction = (float *) malloc(sizeof(float) * nFilters * 3);
        memset(obj->direction, 0x00, sizeof(float) * nFilters * 3);

        obj->thetaAllPass = (float *) malloc(sizeof(float) * nFilters);
        memset(obj->thetaAllPass, 0x00, sizeof(float) * nFilters);

        obj->thetaNoPass = (float *) malloc(sizeof(float) * nFilters);
        memset(obj->thetaNoPass, 0x00, sizeof(float) * nFilters);

        return obj;

    }

    spatialfilters_obj * spatialfilters_clone(const spatialfilters_obj * obj) {

        spatialfilters_obj * clone;

        clone = (spatialfilters_obj *) malloc(sizeof(spatialfilters_obj));

        clone->direction = (float *) malloc(sizeof(float) * obj->nFilters * 3);
        memcpy(clone->direction, obj->direction, sizeof(float) * obj->nFilters * 3);

        clone->thetaAllPass = (float *) malloc(sizeof(float) * obj->nFilters);
        memcpy(clone->thetaAllPass, obj->thetaAllPass, sizeof(float) * obj->nFilters);

        clone->thetaNoPass = (float *) malloc(sizeof(float) * obj->nFilters);
        memcpy(clone->thetaNoPass, obj->thetaNoPass, sizeof(float) * obj->nFilters);

        return clone;

    }

    void spatialfilters_destroy(spatialfilters_obj * obj) {

        free((void *) obj->direction);
        free((void *) obj->thetaAllPass);
        free((void *) obj->thetaNoPass);
        free((void *) obj);

    }

    void spatialfilters_printf(const spatialfilters_obj * obj) {

        unsigned int iFilter;

        for (iFilter = 0; iFilter < obj->nFilters; iFilter++) {

            printf("direction = (%+1.3f,%+1.3f,%+1.3f), thetaAllPass = %f, thetaNoPass = %f\n", 
                    obj->direction[iFilter * 3 + 0], obj->direction[iFilter * 3 + 1], obj->direction[iFilter * 3 + 2], 
                    obj->thetaAllPass[iFilter], 
                    obj->thetaNoPass[iFilter]);

        }

    }
