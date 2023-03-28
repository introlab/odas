
   /**
    * \file     link.c
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
    
    #include <general/link.h>

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
