
    #include <odas/odas.h>

    #include <time.h>
    #include <stdlib.h>

    #include <utils/inverse.h>

    int main(int argc, char * argv[]) {

        cmatrix_obj * cmatrix1;
        cmatrix_obj * cmatrix2;
        inverse_complex_obj * inverse_complex;

        unsigned int iRow;
        unsigned int iCol;
        unsigned int iIteration;
        unsigned int nIterations;

        nIterations = 100000;

        cmatrix1 = cmatrix_construct_zero(16,16);
        cmatrix2 = cmatrix_construct_zero(16,16);
        inverse_complex = inverse_complex_construct_zero(16,1E-20);

        srand(time(NULL));

        for (iRow = 0; iRow < 16; iRow++) {

            for (iCol = 0; iCol < 16; iCol++) {

                cmatrix1->real[iRow * 16 + iCol] = ((float) rand()) / ((float) RAND_MAX);
                cmatrix1->imag[iRow * 16 + iCol] = ((float) rand()) / ((float) RAND_MAX);

            }

        }

        for (iIteration = 0; iIteration <  nIterations; iIteration++) {

            inverse_complex_process(inverse_complex, cmatrix1, cmatrix2);

        }

    }
