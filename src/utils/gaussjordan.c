    
    #include "gaussjordan.h"

    gaussjordan_obj * gaussjordan_construct_zero(const unsigned int nRowsCols, const float epsilon) {

        gaussjordan_obj * obj;

        obj = (gaussjordan_obj *) malloc(sizeof(gaussjordan_obj));

        obj->nRowsCols = nRowsCols;
        obj->epsilon = epsilon;

        obj->array = (float *) malloc(sizeof(float) * nRowsCols * nRowsCols);
        memset(obj->array, 0x00, sizeof(float) * nRowsCols * nRowsCols);

        return obj;

    }

    void gaussjordan_destroy(gaussjordan_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void gaussjordan_process(gaussjordan_obj * obj, const float * src, float * dest) {

        unsigned int nRows;
        unsigned int nCols;

        signed int iRow;
        signed int iRowUnder;
        signed int iRowOther;
        signed int iCol;

        float epsilon;
        char nonZero;
        char singular;
        
        float element1;
        float element2;
        float gain;

        epsilon = 1E-20f;

        nRows = obj->nRowsCols;
        nCols = obj->nRowsCols;

        // Copy source

        memcpy(obj->array, src, sizeof(float) * nRows * nCols);

        // Create identity matrix

        memset(dest, 0x00, sizeof(float) * nRows * nCols);

        for (iRow = 0; iRow < nRows; iRow++) {

            dest[iRow * nRows + iRow] = 1.0f;

        }

        // Invert

        singular = 0x00;

        for (iRow = 0; iRow < nRows; iRow++) {

            // Check if the leading number is zero

            nonZero = 0x00;

            for (iRowUnder = iRow; iRowUnder < nRows; iRowUnder++) {

                if (fabs(obj->array[iRowUnder * nRows + iRow]) > epsilon) {

                    nonZero = 0x01;
                    break;

                }

            }

            // If all following terms are zero, then cannot invert matrix

            if (nonZero == 0x00) {
                
                singular = 0x01;
                break;

            }

            // If the leading number is zero, then swap rows in both matrices

            if (iRow != iRowUnder) {

                // Swap memory

                for (iCol = 0; iCol < nCols; iCol++) {

                    element1 = obj->array[iRow * nRows + iCol];
                    element2 = obj->array[iRowUnder * nRows + iCol];

                    obj->array[iRow * nRows + iCol] = element2;
                    obj->array[iRowUnder * nRows + iCol] = element1;

                    element1 = dest[iRow * nRows + iCol];
                    element2 = dest[iRowUnder * nRows + iCol];

                    dest[iRow * nRows + iCol] = element2;
                    dest[iRowUnder * nRows + iCol] = element1;

                }

            }

            // Normalize to generate a leading 1

            gain = 1.0f / obj->array[iRow * nRows + iRow];

            for (iCol = iRow; iCol < nCols; iCol++) {
                
                obj->array[iRow * nRows + iCol] *= gain;

            }

            for (iCol = 0; iCol < nCols; iCol++) {

                dest[iRow * nRows + iCol] *= gain;

            }

            // Subtract from all rows

            for (iRowOther = 0; iRowOther < nRows; iRowOther++) {

                if (iRowOther != iRow) {

                    gain = obj->array[iRowOther * nRows + iRow];

                    for (iCol = 0; iCol < nCols; iCol++) {

                        obj->array[iRowOther * nRows + iCol] -= (obj->array[iRow * nRows + iCol] * gain);
                        dest[iRowOther * nRows + iCol] -= (dest[iRow * nRows + iCol] * gain);

                    }

                }

            }
           
        }

        if (singular != 0x00) {

            for (iRow = 0; iRow < nRows; iRow++) {

                for (iCol = 0; iCol < nCols; iCol++) {

                    dest[iRow * nRows + iCol] = +INFINITY;

                }

            }

        }        

    }