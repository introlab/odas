#ifndef __ODAS_UTILS_INVERSE
#define __ODAS_UTILS_INVERSE

   /**
    * \file     inverse.h
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

    #include "gaussjordan.h"
    #include "matrix.h"
    #include "cmatrix.h"

    typedef struct inverse_real_obj {

        unsigned int nRowsCols;

        gaussjordan_obj * gaussjordan;

    } inverse_real_obj;

    typedef struct inverse_complex_obj {

        unsigned int nRowsCols;

        gaussjordan_obj * gaussjordan;

        matrix_obj * A;
        matrix_obj * B;

        matrix_obj * Ainv;
        matrix_obj * Binv;

        matrix_obj * BAinv;
        matrix_obj * ABinv;

        matrix_obj * BAinvB;
        matrix_obj * ABinvA;

        matrix_obj * ApBAinvB;
        matrix_obj * BpABinvA;

        matrix_obj * ApBAinvB_inv;
        matrix_obj * BpABinvA_inv;

        matrix_obj * mBpABinvA_inv;

    } inverse_complex_obj;

    inverse_real_obj * inverse_real_construct_zero(const unsigned int nRowsCols, const float epsilon);

    void inverse_real_destroy(inverse_real_obj * obj);

    void inverse_real_process(inverse_real_obj * obj, const matrix_obj * src, matrix_obj * dest);

    inverse_complex_obj * inverse_complex_construct_zero(const unsigned int nRowsCols, const float epsilon);

    void inverse_complex_destroy(inverse_complex_obj * obj);

    void inverse_complex_process(inverse_complex_obj * obj, const cmatrix_obj * src, cmatrix_obj * dest);

#endif