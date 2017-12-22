
    #include "combining.h"

    assignations_obj * combining_generate(const unsigned int nPots, const unsigned int nTracks) {

        assignations_obj * obj;
        
        unsigned int nCombinations;
        unsigned int iCombination;
        unsigned int iPot;
        
        signed int carry;
        signed int digit;

        nCombinations = 1;

        for (iPot = 0; iPot < nPots; iPot++) {

            nCombinations *= (2+nTracks);

        }

        obj = assignations_construct_zero(nCombinations, nPots);      

        for (iPot = 0; iPot < nPots; iPot++) {

            obj->array[iPot] = -2;

        }

        for (iCombination = 1; iCombination < nCombinations; iCombination++) {

            carry = 1;

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                digit = obj->array[(iCombination-1) * obj->nPots + obj->nPots - iPot - 1];

                digit += carry;

                if (digit == nTracks) {

                    digit = -2;
                    carry = 1;

                }
                else {

                    carry = 0;

                }

                obj->array[iCombination * obj->nPots + obj->nPots - iPot - 1] = digit;

            }

        }

        return obj;

    }
