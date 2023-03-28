#ifndef __ODAS_UTILS_INVERSE
#define __ODAS_UTILS_INVERSE

   /**
    * \file     inverse.h
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