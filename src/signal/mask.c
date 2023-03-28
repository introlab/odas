   
   /**
    * \file     mask.c
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
    
    #include <signal/mask.h>

    masks_obj * masks_construct_zero(const unsigned int nSeps, const unsigned int nChannels) {

        masks_obj * obj;

        obj = (masks_obj *) malloc(sizeof(masks_obj));

        obj->nSeps = nSeps;
        obj->nChannels = nChannels;
        
        obj->array = (char *) malloc(sizeof(char) * nSeps * nChannels);
        memset(obj->array, 0x00, sizeof(char) * nSeps * nChannels);

        return obj;

    }

    void masks_copy(masks_obj * dest, const masks_obj * src) {

        memcpy(dest->array, src->array, sizeof(char) * src->nSeps * src->nChannels);

    }    

    void masks_zero(masks_obj * obj) {

        memset(obj->array, 0x00, sizeof(char) * obj->nSeps * obj->nChannels);

    }

    void masks_destroy(masks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void masks_printf(const masks_obj * obj) {

        unsigned int iSep;
        unsigned int iChannel;

        for (iSep = 0; iSep < obj->nSeps; iSep++) {

            printf("(%02u): ",iSep);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%d ",obj->array[iSep * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }
