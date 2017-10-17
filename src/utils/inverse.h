#ifndef __ODAS_UTILS_INVERSE
#define __ODAS_UTILS_INVERSE

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