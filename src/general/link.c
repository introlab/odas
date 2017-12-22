    
    #include "link.h"

    links_obj * links_construct_zero(const unsigned int nLinks) {

        links_obj * obj;

        obj = (links_obj *) malloc(sizeof(links_obj));

        obj->nLinks = nLinks;
        obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nLinks);
        memset(obj->array, 0x00, sizeof(unsigned int) * nLinks);

        return obj;

    }

    links_obj * links_clone(const links_obj * obj) {

        links_obj * clone;

        clone = (links_obj *) malloc(sizeof(links_obj));

        clone->nLinks = obj->nLinks;
        clone->array = (unsigned int *) malloc(sizeof(unsigned int) * obj->nLinks);
        memcpy(clone->array, obj->array, sizeof(unsigned int) * obj->nLinks);

        return clone;

    }

    void links_destroy(links_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void links_printf(const links_obj * obj) {

        unsigned int iLink;

        for (iLink = 0; iLink < obj->nLinks; iLink++) {
            printf("(%u): %u\n",iLink,obj->array[iLink]);
        }

    }