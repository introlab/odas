   
   /**
    * \file     kalman.c
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

    #include <signal/kalman.h>
    
    kalman_obj * kalman_construct_zero(void) {

        kalman_obj * obj;

        obj = (kalman_obj *) malloc(sizeof(kalman_obj));

        obj->x_lm1lm1 = matrix_construct_zero(6,1);
        obj->x_llm1 = matrix_construct_zero(6,1);
        obj->P_lm1lm1 = matrix_construct_zero(6,6);
        obj->P_llm1 = matrix_construct_zero(6,6);

        return obj;

    }

    void kalman_destroy(kalman_obj * obj) {

        matrix_destroy(obj->x_lm1lm1);
        matrix_destroy(obj->x_llm1);
        matrix_destroy(obj->P_lm1lm1);
        matrix_destroy(obj->P_llm1);

        free((void *) obj);

    }
