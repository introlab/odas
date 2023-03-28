
   /**
    * \file     cmatrix.c
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

    #include <utils/cmatrix.h>

    cmatrix_obj * cmatrix_construct_zero(const unsigned int nRows, const unsigned int nCols) {

        cmatrix_obj * obj;

        obj = (cmatrix_obj *) malloc(sizeof(cmatrix_obj));

        obj->nRows = nRows;
        obj->nCols = nCols;

        obj->real = (float *) malloc(sizeof(float) * nRows * nCols);
        obj->imag = (float *) malloc(sizeof(float) * nRows * nCols);

        memset(obj->real, 0x00, sizeof(float) * nRows * nCols);
        memset(obj->imag, 0x00, sizeof(float) * nRows * nCols);

        return obj;

    }

    cmatrix_obj * cmatrix_construct_matrix(const cmatrix_obj * cmatrix) {

        cmatrix_obj * obj;

        obj = (cmatrix_obj *) malloc(sizeof(cmatrix_obj));

        obj->nRows = cmatrix->nRows;
        obj->nCols = cmatrix->nCols;

        obj->real = (float *) malloc(sizeof(float) * obj->nRows * obj->nCols);
        obj->imag = (float *) malloc(sizeof(float) * obj->nRows * obj->nCols);

        memcpy(obj->real, cmatrix->real, sizeof(float) * cmatrix->nRows * cmatrix->nCols);
        memcpy(obj->imag, cmatrix->imag, sizeof(float) * cmatrix->nRows * cmatrix->nCols);

        return obj;

    }

    void cmatrix_copy_zero(cmatrix_obj * obj) {

        memset(obj->real, 0x00, sizeof(float) * obj->nRows * obj->nCols);
        memset(obj->imag, 0x00, sizeof(float) * obj->nRows * obj->nCols);

    }

    void cmatrix_copy_cmatrix(cmatrix_obj * obj, const cmatrix_obj * cmatrix) {

        memcpy(obj->real, cmatrix->real, sizeof(float) * cmatrix->nRows * cmatrix->nCols);
        memcpy(obj->imag, cmatrix->imag, sizeof(float) * cmatrix->nRows * cmatrix->nCols);

    }

    void cmatrix_destroy(cmatrix_obj * obj) {

        free((void *) obj->real);
        free((void *) obj->imag);
        free((void *) obj);

    }

    void cmatrix_transpose(cmatrix_obj * obj, const cmatrix_obj * src) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->real[iRow * obj->nRows + iCol] = src->real[iCol * obj->nRows + iRow];
                obj->imag[iRow * obj->nRows + iCol] = src->imag[iCol * obj->nRows + iRow];

            }

        }

    }

    void cmatrix_hermitian(cmatrix_obj * obj, const cmatrix_obj * src) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->real[iRow * obj->nRows + iCol] = src->real[iCol * obj->nRows + iRow];
                obj->imag[iRow * obj->nRows + iCol] = -1.0f * src->imag[iCol * obj->nRows + iRow];

            }

        }

    }

    void cmatrix_add(cmatrix_obj * obj, const cmatrix_obj * src1, const cmatrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->real[iRow * obj->nCols + iCol] = src1->real[iRow * obj->nCols + iCol] + src2->real[iRow * obj->nCols + iCol];

            }

        }

    }

    void cmatrix_sub(cmatrix_obj * obj, const cmatrix_obj * src1, const cmatrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                obj->real[iRow * obj->nCols + iCol] = src1->real[iRow * obj->nCols + iCol] - src2->real[iRow * obj->nCols + iCol];

            }

        }

    }

    void cmatrix_mul(cmatrix_obj * obj, const cmatrix_obj * src1, const cmatrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;
        unsigned int iElement;

        float real1, imag1;
        float real2, imag2;
        float real12, imag12;

        for (iRow = 0; iRow < src1->nRows; iRow++) {

            for (iCol = 0; iCol < src2->nCols; iCol++) {

                obj->real[iRow*obj->nCols+iCol] = 0.0f;
                obj->imag[iRow*obj->nCols+iCol] = 0.0f;

                for (iElement = 0; iElement < src1->nCols; iElement++) {

                    real1 = src1->real[iRow*src1->nCols+iElement];
                    imag1 = src1->imag[iRow*src1->nCols+iElement];
                    real2 = src2->real[iElement*src2->nCols+iCol];
                    imag2 = src2->imag[iElement*src2->nCols+iCol];

                    real12 = real1 * real2 - imag1 * imag2;
                    imag12 = real1 * imag2 + imag1 * real2;

                    obj->real[iRow*obj->nCols+iCol] += real12;
                    obj->imag[iRow*obj->nCols+iCol] += imag12;

                }

            }

        }

    }

    void cmatrix_scale(cmatrix_obj * obj, const cmatrix_obj * src, const float scale) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < src->nRows; iRow++) {

            for (iCol = 0; iCol < src->nCols; iCol++) {

                obj->real[iRow * obj->nCols + iCol] = scale * src->real[iRow * obj->nCols + iCol];
                obj->imag[iRow * obj->nCols + iCol] = scale * src->imag[iRow * obj->nCols + iCol];

            }

        }

    }

    void cmatrix_zero(cmatrix_obj * obj) {

        memset(obj->real, 0x00, sizeof(float) * obj->nRows * obj->nCols);
        memset(obj->imag, 0x00, sizeof(float) * obj->nRows * obj->nCols);

    }

    void cmatrix_printf(const cmatrix_obj * obj) {

        unsigned int iRow;
        unsigned int iCol;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                printf("(%+1.5f + %+1.5fj) ",obj->real[iRow*obj->nCols+iCol],obj->imag[iRow*obj->nCols+iCol]);

            }

            printf("\n");

        }

    }
