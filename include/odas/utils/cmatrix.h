#ifndef __ODAS_UTILS_CMATRIX
#define __ODAS_UTILS_CMATRIX

   /**
    * \file     cmatrix.h
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