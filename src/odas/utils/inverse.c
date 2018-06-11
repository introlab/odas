   
   /**
    * \file     inverse.c
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
