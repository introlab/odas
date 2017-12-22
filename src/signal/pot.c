    
    #include "pot.h"

    pots_obj * pots_construct_zero(const unsigned int nPots) {

        pots_obj * obj;

        obj = (pots_obj *) malloc(sizeof(pots_obj));

        obj->nPots = nPots;
        obj->array = (float *) malloc(sizeof(float) * 4 * nPots);
        memset(obj->array, 0x00, sizeof(float) * 4 * nPots);

        return obj;

    }

    pots_obj * pots_clone(const pots_obj * obj) {

      pots_obj * clone;

      clone = (pots_obj *) malloc(sizeof(pots_obj));

      clone->nPots = obj->nPots;
      clone->array = (float *) malloc(sizeof(float) * 4 * obj->nPots);
      memcpy(clone->array, obj->array, sizeof(float) * 4 * obj->nPots);

      return clone;

    }

    void pots_copy(pots_obj * dest, const pots_obj * src) {

      dest->nPots = src->nPots;

      memcpy(dest->array, src->array, sizeof(float) * 4 * src->nPots);

    }

    void pots_zero(pots_obj * obj) {

      obj->nPots = 0;
      memset(obj->array, 0x00, sizeof(float) * 4 * obj->nPots);

    }

    void pots_destroy(pots_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void pots_printf(const pots_obj * obj) {

        unsigned int iPot;

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            printf("(%02u): %+1.3f %+1.3f %+1.3f %+1.3f\n",
                   iPot,
                   obj->array[iPot * 4 + 0],
                   obj->array[iPot * 4 + 1],
                   obj->array[iPot * 4 + 2],
                   obj->array[iPot * 4 + 3]);
            
        }

    }
