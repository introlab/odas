#ifndef __ODAS_UTILS_CMATRIX
#define __ODAS_UTILS_CMATRIX

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