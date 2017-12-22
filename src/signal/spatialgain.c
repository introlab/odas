    
    #include "spatialgain.h"

    // +----------------------------------------------------------+
    // | Constructor                                              |
    // +----------------------------------------------------------+

    spatialgains_obj * spatialgains_construct_zero(const unsigned int nChannels, const unsigned int nPoints) {

        spatialgains_obj * obj;

        obj = (spatialgains_obj *) malloc(sizeof(spatialgains_obj));

        obj->nChannels = nChannels;
        obj->nPoints = nPoints;

        obj->array = (float *) malloc(sizeof(float) * nChannels * nPoints);
        memset(obj->array, 0x00, sizeof(float) * nChannels * nPoints);

        return obj;

    }

    // +----------------------------------------------------------+
    // | Clone                                                    |
    // +----------------------------------------------------------+

    spatialgains_obj * spatialgains_clone(const spatialgains_obj * obj) {

        spatialgains_obj * clone;

        clone = (spatialgains_obj *) malloc(sizeof(spatialgains_obj));

        clone->nChannels = obj->nChannels;
        clone->nPoints = obj->nPoints;

        clone->array = (float *) malloc(sizeof(float) * obj->nChannels * obj->nPoints);
        memcpy(clone->array, obj->array, sizeof(float) * obj->nChannels * obj->nPoints);

        return clone;

    }

    // +----------------------------------------------------------+
    // | Destructor                                               |
    // +----------------------------------------------------------+

    void spatialgains_destroy(spatialgains_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    // +----------------------------------------------------------+
    // | Print                                                    |
    // +----------------------------------------------------------+

    void spatialgains_printf(const spatialgains_obj * obj) {

        unsigned int iPoint;
        unsigned int iChannel;

        for (iPoint = 0; iPoint < obj->nPoints; iPoint++) {

            printf("(%04u): ",iPoint);

            for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

                printf("%1.2f ",obj->array[iPoint * obj->nChannels + iChannel]);

            }

            printf("\n");

        }

    }