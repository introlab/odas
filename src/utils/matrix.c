    
    #include "matrix.h"

    matrix_obj * matrix_construct_zero(const unsigned int nRows, const unsigned int nCols) {

        matrix_obj * obj;
        unsigned int iRow;
        unsigned int iCol;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->nRows = nRows;
        obj->nCols = nCols;
        obj->array = (float **) malloc(sizeof(float *) * nRows);

        for (iRow = 0; iRow < nRows; iRow++) {
        	
        	obj->array[iRow] = (float *) malloc(sizeof(float) * nCols);

            for (iCol = 0; iCol < nCols; iCol++) {

                obj->array[iRow][iCol] = 0.0f;

            }

        }

        return obj;

    }

    matrix_obj * matrix_construct_matrix(const matrix_obj * matrix) {

        matrix_obj * obj;

        unsigned int iRow;
        unsigned int iCol;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->nRows = matrix->nRows;
        obj->nCols = matrix->nCols;
        obj->array = (float **) malloc(sizeof(float *) * matrix->nRows);

        for (iRow = 0; iRow < matrix->nRows; iRow++) {

            obj->array[iRow] = (float *) malloc(sizeof(float) * matrix->nCols);

            for (iCol = 0; iCol < matrix->nCols; iCol++) {

                obj->array[iRow][iCol]  = matrix->array[iRow][iCol];

            }

        }

        return obj;

    }

    void matrix_copy_zero(matrix_obj * obj) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow][iCol] = 0.0f;

            }

        }    

    }

    void matrix_copy_matrix(matrix_obj * obj, const matrix_obj * matrix) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < matrix->nRows; iRow++) {

            obj->array[iRow] = (float *) malloc(sizeof(float) * matrix->nCols);

            for (iCol = 0; iCol < matrix->nCols; iCol++) {

                obj->array[iRow][iCol]  = matrix->array[iRow][iCol];

            }

        }

    }

    void matrix_destroy(matrix_obj * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            free((void *) obj->array[iRow]);

        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_transpose(matrix_obj * obj, const matrix_obj * src) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow][iCol] = src->array[iCol][iRow];

            }

        }   

    }

    void matrix_add(matrix_obj * obj, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow][iCol] = src1->array[iRow][iCol] + src2->array[iRow][iCol];

            }

        }

    }

    void matrix_sub(matrix_obj * obj, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->array[iRow][iCol] = src1->array[iRow][iCol] - src2->array[iRow][iCol];

            }

        }

    }

    void matrix_mul(matrix_obj * obj, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;
        unsigned int iElement;

        for (iRow = 0; iRow < src1->nRows; iRow++) {

            for (iCol = 0; iCol < src2->nCols; iCol++) {

                obj->array[iRow][iCol] = 0.0f;

                for (iElement = 0; iElement < src1->nCols; iElement++) {

                    obj->array[iRow][iCol] += (src1->array[iRow][iElement] * src2->array[iElement][iCol]);

                }

            }

        }

    }

    void matrix_inv(matrix_obj * obj, const matrix_obj * src) {

        float a00, a01, a02, a10, a11, a12, a20, a21, a22;
        float det;

        if ((src->nRows == 2) && (src->nCols == 2)) {

            a00 = src->array[0][0];
            a01 = src->array[0][1];
            a10 = src->array[1][0];
            a11 = src->array[1][1];

            det = a00*a11 - a01*a10;

            obj->array[0][0] = +a11 / det;
            obj->array[0][1] = -a01 / det;
            obj->array[1][0] = -a10 / det;
            obj->array[1][1] = +a00 / det;

        }

        if ((src->nRows == 3) && (src->nCols == 3)) {

            a00 = src->array[0][0];
            a01 = src->array[0][1];
            a02 = src->array[0][2];
            a10 = src->array[1][0];
            a11 = src->array[1][1];
            a12 = src->array[1][2];
            a20 = src->array[2][0];
            a21 = src->array[2][1];
            a22 = src->array[2][2];

            det = a00*a11*a22 - a00*a12*a21 - a01*a10*a22 + a01*a12*a20 + a02*a10*a21 - a02*a11*a20;

            obj->array[0][0] = +(a11*a22 - a12*a21) / det;
            obj->array[0][1] = -(a01*a22 - a02*a21) / det;
            obj->array[0][2] = +(a01*a12 - a02*a11) / det;
            obj->array[1][0] = -(a10*a22 - a12*a20) / det;
            obj->array[1][1] = +(a00*a22 - a02*a20) / det;
            obj->array[1][2] = -(a00*a12 - a02*a10) / det;
            obj->array[2][0] = +(a10*a21 - a11*a20) / det;
            obj->array[2][1] = -(a00*a21 - a01*a20) / det;
            obj->array[2][2] = +(a00*a11 - a01*a10) / det;

        }

    }

    float matrix_det(const matrix_obj * obj) {

        float a00, a01, a02, a10, a11, a12, a20, a21, a22;
        float det;

        det = 0.0f;

        if ((obj->nRows == 3) && (obj->nCols == 3)) {

            a00 = obj->array[0][0];
            a01 = obj->array[0][1];
            a10 = obj->array[1][0];
            a11 = obj->array[1][1];

            det = a00*a11 - a01*a10;

        }

        if ((obj->nRows == 3) && (obj->nCols == 3)) {

            a00 = obj->array[0][0];
            a01 = obj->array[0][1];
            a02 = obj->array[0][2];
            a10 = obj->array[1][0];
            a11 = obj->array[1][1];
            a12 = obj->array[1][2];
            a20 = obj->array[2][0];
            a21 = obj->array[2][1];
            a22 = obj->array[2][2];

            det = a00*a11*a22 - a00*a12*a21 - a01*a10*a22 + a01*a12*a20 + a02*a10*a21 - a02*a11*a20;        

        }

        return det;

    }

    void matrix_scale(matrix_obj * obj, const matrix_obj * src, const float scale) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < src->nRows; iRow++) {

            for (iCol = 0; iCol < src->nCols; iCol++) {

                obj->array[iRow][iCol] = scale * src->array[iRow][iCol];

            }

        }

    }

    void matrix_printf(const matrix_obj * obj) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                printf("%+1.5f ",obj->array[iRow][iCol]);

            }

            printf("\n");

        }

    }