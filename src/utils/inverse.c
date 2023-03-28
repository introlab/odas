   
   /**
    * \file     inverse.c
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
    
    #include <utils/inverse.h>

    inverse_real_obj * inverse_real_construct_zero(const unsigned int nRowsCols, const float epsilon) {

        inverse_real_obj * obj;

        obj = (inverse_real_obj *) malloc(sizeof(inverse_real_obj));

        obj->nRowsCols = nRowsCols;
        obj->gaussjordan = gaussjordan_construct_zero(nRowsCols, epsilon);

        return obj;

    }

    void inverse_real_destroy(inverse_real_obj * obj) {

        gaussjordan_destroy(obj->gaussjordan);
        free((void *) obj);

    }

    void inverse_real_process(inverse_real_obj * obj, const matrix_obj * src, matrix_obj * dest) {

        gaussjordan_process(obj->gaussjordan, src->array, dest->array);

    }

    inverse_complex_obj * inverse_complex_construct_zero(const unsigned int nRowsCols, const float epsilon) {

        inverse_complex_obj * obj;

        obj = (inverse_complex_obj *) malloc(sizeof(inverse_complex_obj));

        obj->nRowsCols = nRowsCols;
        obj->gaussjordan = gaussjordan_construct_zero(nRowsCols, epsilon);

        obj->A = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->B = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->Ainv = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->Binv = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->BAinv = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->ABinv = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->BAinvB = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->ABinvA = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->ApBAinvB = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->BpABinvA = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->ApBAinvB_inv = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->BpABinvA_inv = matrix_construct_zero(nRowsCols,nRowsCols);
        obj->mBpABinvA_inv = matrix_construct_zero(nRowsCols,nRowsCols);

        return obj;

    }

    void inverse_complex_destroy(inverse_complex_obj * obj) {

        matrix_destroy(obj->A);
        matrix_destroy(obj->B);
        matrix_destroy(obj->Ainv);
        matrix_destroy(obj->Binv);
        matrix_destroy(obj->BAinv);
        matrix_destroy(obj->ABinv);
        matrix_destroy(obj->BAinvB);
        matrix_destroy(obj->ABinvA);
        matrix_destroy(obj->ApBAinvB);
        matrix_destroy(obj->BpABinvA);
        matrix_destroy(obj->ApBAinvB_inv);
        matrix_destroy(obj->BpABinvA_inv);
        matrix_destroy(obj->mBpABinvA_inv);

    }

    void inverse_complex_process(inverse_complex_obj * obj, const cmatrix_obj * src, cmatrix_obj * dest) {

        memcpy(obj->A->array, src->real, sizeof(float) * obj->nRowsCols * obj->nRowsCols);
        memcpy(obj->B->array, src->imag, sizeof(float) * obj->nRowsCols * obj->nRowsCols);

        gaussjordan_process(obj->gaussjordan, obj->A->array, obj->Ainv->array);
        gaussjordan_process(obj->gaussjordan, obj->B->array, obj->Binv->array);

        matrix_mul(obj->BAinv, obj->B, obj->Ainv);
        matrix_mul(obj->ABinv, obj->A, obj->Binv);
        matrix_mul(obj->BAinvB, obj->BAinv, obj->B);
        matrix_mul(obj->ABinvA, obj->ABinv, obj->A);
        matrix_add(obj->ApBAinvB, obj->A, obj->BAinvB);
        matrix_add(obj->BpABinvA, obj->B, obj->ABinvA);

        gaussjordan_process(obj->gaussjordan, obj->ApBAinvB->array, obj->ApBAinvB_inv->array);
        gaussjordan_process(obj->gaussjordan, obj->BpABinvA->array, obj->BpABinvA_inv->array);

        matrix_scale(obj->mBpABinvA_inv, obj->BpABinvA_inv, -1.0f);

        memcpy(dest->real, obj->ApBAinvB_inv->array, sizeof(float) * obj->nRowsCols * obj->nRowsCols);
        memcpy(dest->imag, obj->mBpABinvA_inv->array, sizeof(float) * obj->nRowsCols * obj->nRowsCols);

    }
