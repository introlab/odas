#ifndef __ODAS_UTILS_CMATRIX
#define __ODAS_UTILS_CMATRIX

   /**
    * \file     cmatrix.h
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
    #include <string.h>
    #include <math.h>

    typedef struct cmatrix_obj {

        float * real;
        float * imag;
        unsigned int nRows;
        unsigned int nCols;

    } cmatrix_obj;

    cmatrix_obj * cmatrix_construct_zero(const unsigned int nRows, const unsigned int nCols);

    cmatrix_obj * cmatrix_construct_matrix(const cmatrix_obj * cmatrix);

    void cmatrix_copy_zero(cmatrix_obj * obj);

    void cmatrix_copy_cmatrix(cmatrix_obj * obj, const cmatrix_obj * cmatrix);

    void cmatrix_destroy(cmatrix_obj * obj);

    void cmatrix_transpose(cmatrix_obj * obj, const cmatrix_obj * src);

    void cmatrix_hermitian(cmatrix_obj * obj, const cmatrix_obj * src);

    void cmatrix_add(cmatrix_obj * obj, const cmatrix_obj * src1, const cmatrix_obj * src2);

    void cmatrix_sub(cmatrix_obj * obj, const cmatrix_obj * src1, const cmatrix_obj * src2);

    void cmatrix_mul(cmatrix_obj * obj, const cmatrix_obj * src1, const cmatrix_obj * src2);

    void cmatrix_scale(cmatrix_obj * obj, const cmatrix_obj * src, const float scale);

    void cmatrix_zero(cmatrix_obj * obj);

    void cmatrix_printf(const cmatrix_obj * obj);

#endif