#ifndef __ODAS_GENERAL_LINK
#define __ODAS_GENERAL_LINK

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct links_obj {

        unsigned int * array;
        unsigned int nLinks;

    } links_obj;

    links_obj * links_construct_zero(const unsigned int nLinks);

    links_obj * links_clone(const links_obj * obj);

    void links_destroy(links_obj * obj);

    void links_printf(const links_obj * obj);

#endif