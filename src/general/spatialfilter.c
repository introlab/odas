
   /**
    * \file     spatialfilter.c
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
