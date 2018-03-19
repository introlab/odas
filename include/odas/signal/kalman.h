#ifndef __ODAS_SIGNAL_KALMAN
#define __ODAS_SIGNAL_KALMAN

   /**
    * \file     kalman.h
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

    #include <stdlib.h>
    #include <stdio.h>

    #include "../utils/matrix.h"

    typedef struct kalman_obj {

        matrix_obj * x_lm1lm1;
        matrix_obj * x_llm1;
        matrix_obj * P_lm1lm1;
        matrix_obj * P_llm1;

    } kalman_obj;

    kalman_obj * kalman_construct_zero(void);

    void kalman_destroy(kalman_obj * obj);

#endif