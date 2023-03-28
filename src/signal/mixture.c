   
   /**
    * \file     mixture.c
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
    
    #include <signal/mixture.h>

    mixture_obj * mixture_construct_zero(const unsigned int nPots, const unsigned int nTracks) {

        mixture_obj * obj;

        obj = (mixture_obj *) malloc(sizeof(mixture_obj));

        obj->assignations = combining_generate(nPots, nTracks);

        obj->nPots = nPots;
        obj->nTracks = nTracks;
        obj->nTracksNewFalse = nTracks + 2;
        obj->nCombinations = obj->assignations->nAssignations;
       
        obj->p_Ez_AICD = (float *) malloc(sizeof(float) * (3+nTracks) * obj->nPots );
        memset(obj->p_Ez_AICD, 0x00, sizeof(float) * (3+nTracks) * obj->nPots );

        obj->p_Eszs_phics = (float *) malloc(sizeof(float) * obj->nTracksNewFalse * obj->nPots);
        memset(obj->p_Eszs_phics, 0x00, sizeof(float) * obj->nTracksNewFalse * obj->nPots);

        obj->p_phics = (float *) malloc(sizeof(float) * obj->nTracksNewFalse * obj->nPots);        
        memset(obj->p_phics, 0x00, sizeof(float) * obj->nTracksNewFalse * obj->nPots);

        obj->p_Ez_phic = (float *) malloc(sizeof(float) * obj->nCombinations);
        memset(obj->p_Ez_phic, 0x00, sizeof(float) * obj->nCombinations);

        obj->p_phic = (float *) malloc(sizeof(float) * obj->nCombinations);
        memset(obj->p_phic, 0x00, sizeof(float) * obj->nCombinations);

        obj->p_phic_Ez = (float *) malloc(sizeof(float) * obj->nCombinations);
        memset(obj->p_phic_Ez, 0x00, sizeof(float) * obj->nCombinations);

        return obj;

    }

    void mixture_destroy(mixture_obj * obj) {

        assignations_destroy(obj->assignations);

        free((void *) obj->p_Ez_AICD);
        free((void *) obj->p_Eszs_phics);
        free((void *) obj->p_phics);
        free((void *) obj->p_Ez_phic);
        free((void *) obj->p_phic);
        free((void *) obj->p_phic_Ez);

        free((void *) obj);

    }

    void mixture_printf(const mixture_obj * obj) {

        unsigned int iTrack;
        unsigned int iTrackNewFalse;
        unsigned int iPot;
        unsigned int iCombination;

        printf("p(E|A) = ");
        for (iPot = 0; iPot < obj->nPots; iPot++) {
            printf("%+1.3e ",obj->p_Ez_AICD[0 * obj->nPots + iPot]);
        }
        printf("\n");

        printf("p(E|I) = ");
        for (iPot = 0; iPot < obj->nPots; iPot++) {
            printf("%+1.3e ",obj->p_Ez_AICD[1 * obj->nPots + iPot]);
        }
        printf("\n");

        printf("p(z|D) = ");
        for (iPot = 0; iPot < obj->nPots; iPot++) {
            printf("%+1.3e ",obj->p_Ez_AICD[2 * obj->nPots + iPot]);
        }
        printf("\n");

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {
            printf("p(z|C,%u) = ",iTrack);
            for (iPot = 0; iPot < obj->nPots; iPot++) {
                printf("%+1.3e ", obj->p_Ez_AICD[3 * obj->nPots + iPot]);
            }
            printf("\n");
        }
        printf("\n");

        printf("p(E,z|phi(s)):\n");
        for (iTrackNewFalse = 0; iTrackNewFalse < obj->nTracksNewFalse; iTrackNewFalse++) {
            
            printf("  phi = %d: ",iTrackNewFalse-2);
            for (iPot = 0; iPot < obj->nPots; iPot++) {
                printf("%+1.3e ",obj->p_Eszs_phics[iTrackNewFalse * obj->nPots + iPot]);
            }
            printf("\n");

        }
        printf("\n");

        printf("p(phi(s)):\n");
        for (iTrackNewFalse = 0; iTrackNewFalse < obj->nTracksNewFalse; iTrackNewFalse++) {
            
            printf("  phi = %d: ",iTrackNewFalse-2);
            for (iPot = 0; iPot < obj->nPots; iPot++) {
                printf("%+1.3e ",obj->p_phics[iTrackNewFalse * obj->nPots + iPot]);
            }
            printf("\n");

        }
        printf("\n");

        printf("p(E,z|phi), p(phi), p(phi|E,z):\n");

        for (iCombination = 0; iCombination < obj->nCombinations; iCombination++) {

            printf("  ");

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+01d ",obj->assignations->array[iCombination * obj->nPots + iPot]);

            }

            printf(": %+1.3e %+1.3e %+1.3e\n",obj->p_Ez_phic[iCombination],obj->p_phic[iCombination],obj->p_phic_Ez[iCombination]);

        }       

    }
