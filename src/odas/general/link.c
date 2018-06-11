
   /**
    * \file     link.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
