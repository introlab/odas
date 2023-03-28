   
   /**
    * \file     matrix.c
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
    
    #include <utils/matrix.h>

    matrix_obj * matrix_construct_zero(const unsigned int nRows, const unsigned int nCols) {

        matrix_obj * obj;
        unsigned int iRow;
        unsigned int iCol;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->nRows = nRows;
        obj->nCols = nCols;
        obj->array = (float *) malloc(sizeof(float) * nRows * nCols);

        memset(obj->array, 0x00, sizeof(float) * nRows * nCols);

        return obj;

    }

    matrix_obj * matrix_construct_matrix(const matrix_obj * matrix) {

        matrix_obj * obj;

        unsigned int iRow;
        unsigned int iCol;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->nRows = matrix->nRows;
        obj->nCols = matrix->nCols;
        obj->array = (float *) malloc(sizeof(float) * matrix->nRows * matrix->nCols);

        memcpy(obj->array, matrix->array, sizeof(float) * matrix->nRows * matrix->nCols);

        return obj;

    }

    void matrix_copy_zero(matrix_obj * obj) {

        unsigned int iRow;
        unsigned int iCol;

        memset(obj->array, 0x00, sizeof(float) * obj->nRows * obj->nCols);

    }

    void matrix_copy_matrix(matrix_obj * obj, const matrix_obj * matrix) {

        unsigned int iRow;
        unsigned int iCol;

        memcpy(obj->array, matrix->array, sizeof(float) * matrix->nRows * matrix->nCols);

    }

    void matrix_destroy(matrix_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_transpose(matrix_obj * obj, const matrix_obj * src) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow*obj->nCols+iCol] = src->array[iCol*src->nCols+iRow];

            }

        }   

    }

    void matrix_add(matrix_obj * obj, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow*obj->nCols+iCol] = src1->array[iRow*src1->nCols+iCol] + src2->array[iRow*src2->nCols+iCol];

            }

        }

    }

    void matrix_sub(matrix_obj * obj, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow*obj->nCols+iCol] = src1->array[iRow*src1->nCols+iCol] - src2->array[iRow*src2->nCols+iCol];

            }

        }

    }

    void matrix_mul(matrix_obj * obj, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;
        unsigned int iElement;

        for (iRow = 0; iRow < src1->nRows; iRow++) {

            for (iCol = 0; iCol < src2->nCols; iCol++) {

                obj->array[iRow*obj->nCols+iCol] = 0.0f;

                for (iElement = 0; iElement < src1->nCols; iElement++) {

                    obj->array[iRow*obj->nCols+iCol] += (src1->array[iRow*src1->nCols+iElement] * src2->array[iElement*src2->nCols+iCol]);

                }

            }

        }

    }

    void matrix_inv(matrix_obj * obj, const matrix_obj * src) {

        float a00, a01, a02, a10, a11, a12, a20, a21, a22;
        float det;

        if ((src->nRows == 2) && (src->nCols == 2)) {

            a00 = src->array[0*src->nRows+0];
            a01 = src->array[0*src->nRows+1];
            a10 = src->array[1*src->nRows+0];
            a11 = src->array[1*src->nRows+1];

            det = a00*a11 - a01*a10;

            obj->array[0*obj->nRows+0] = +a11 / det;
            obj->array[0*obj->nRows+1] = -a01 / det;
            obj->array[1*obj->nRows+0] = -a10 / det;
            obj->array[1*obj->nRows+1] = +a00 / det;

        }

        if ((src->nRows == 3) && (src->nCols == 3)) {

            a00 = src->array[0*src->nRows+0];
            a01 = src->array[0*src->nRows+1];
            a02 = src->array[0*src->nRows+2];
            a10 = src->array[1*src->nRows+0];
            a11 = src->array[1*src->nRows+1];
            a12 = src->array[1*src->nRows+2];
            a20 = src->array[2*src->nRows+0];
            a21 = src->array[2*src->nRows+1];
            a22 = src->array[2*src->nRows+2];

            det = a00*a11*a22 - a00*a12*a21 - a01*a10*a22 + a01*a12*a20 + a02*a10*a21 - a02*a11*a20;

            obj->array[0*obj->nRows+0] = +(a11*a22 - a12*a21) / det;
            obj->array[0*obj->nRows+1] = -(a01*a22 - a02*a21) / det;
            obj->array[0*obj->nRows+2] = +(a01*a12 - a02*a11) / det;
            obj->array[1*obj->nRows+0] = -(a10*a22 - a12*a20) / det;
            obj->array[1*obj->nRows+1] = +(a00*a22 - a02*a20) / det;
            obj->array[1*obj->nRows+2] = -(a00*a12 - a02*a10) / det;
            obj->array[2*obj->nRows+0] = +(a10*a21 - a11*a20) / det;
            obj->array[2*obj->nRows+1] = -(a00*a21 - a01*a20) / det;
            obj->array[2*obj->nRows+2] = +(a00*a11 - a01*a10) / det;

        }

    }

    float matrix_det(const matrix_obj * obj) {

        float a00, a01, a02, a10, a11, a12, a20, a21, a22;
        float det;

        det = 0.0f;

        if ((obj->nRows == 3) && (obj->nCols == 3)) {

            a00 = obj->array[0*obj->nRows+0];
            a01 = obj->array[0*obj->nRows+1];
            a10 = obj->array[1*obj->nRows+0];
            a11 = obj->array[1*obj->nRows+1];

            det = a00*a11 - a01*a10;

        }

        if ((obj->nRows == 3) && (obj->nCols == 3)) {

            a00 = obj->array[0*obj->nRows+0];
            a01 = obj->array[0*obj->nRows+1];
            a02 = obj->array[0*obj->nRows+2];
            a10 = obj->array[1*obj->nRows+0];
            a11 = obj->array[1*obj->nRows+1];
            a12 = obj->array[1*obj->nRows+2];
            a20 = obj->array[2*obj->nRows+0];
            a21 = obj->array[2*obj->nRows+1];
            a22 = obj->array[2*obj->nRows+2];

            det = a00*a11*a22 - a00*a12*a21 - a01*a10*a22 + a01*a12*a20 + a02*a10*a21 - a02*a11*a20;        

        }

        return det;

    }

    void matrix_scale(matrix_obj * obj, const matrix_obj * src, const float scale) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < src->nRows; iRow++) {

            for (iCol = 0; iCol < src->nCols; iCol++) {

                obj->array[iRow*obj->nCols+iCol] = scale * src->array[iRow*src->nCols+iCol];

            }

        }

    }

    void matrix_printf(const matrix_obj * obj) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                printf("%+1.5f ",obj->array[iRow*obj->nCols+iCol]);

            }

            printf("\n");

        }

    }
