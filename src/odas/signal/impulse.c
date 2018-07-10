   
    /**
    * \file     impulse.c
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
    
    #include "impulse.h"

    impulse_obj * impulse_construct(const unsigned int nCoefficients) {

        impulse_obj * obj;

        obj = (impulse_obj *) malloc(sizeof(impulse_obj));

        obj->nCoefficients = nCoefficients;
        obj->array = (float *) malloc(sizeof(float) * nCoefficients);
        memset(obj->array, 0x00, sizeof(float) * nCoefficients);

        return obj;

    }

    void impulse_destroy(impulse_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }