   
   /**
    * \file     target.c
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
    
    #include <signal/target.h>

    targets_obj * targets_construct_zero(const unsigned int nTargets) {

        targets_obj * obj;
        unsigned int iTarget;

        obj = (targets_obj *) malloc(sizeof(targets_obj));

        obj->nTargets = nTargets;
        
        obj->tags = (char **) malloc(sizeof(char *) * nTargets);

        for (iTarget = 0; iTarget < nTargets; iTarget++) {

            obj->tags[iTarget] = (char *) malloc(sizeof(char) * 256);
            strcpy(obj->tags[iTarget], "");

        }

        obj->array = (float *) malloc(sizeof(float) * 3 * nTargets);
        memset(obj->array, 0x00, sizeof(float) * 3 * nTargets);

        return obj;

    }

    void targets_destroy(targets_obj * obj) {

        unsigned int iTarget;

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {
            free((void *) obj->tags[iTarget]);
        }
        free((void *) obj->tags);

        free((void *) obj->array);
        free((void *) obj);

    }

    targets_obj * targets_clone(const targets_obj * obj) {

        targets_obj * clone;
        unsigned int iTarget;

        clone = (targets_obj *) malloc(sizeof(targets_obj));

        clone->nTargets = obj->nTargets;
        clone->array = (float *) malloc(sizeof(float) * 3 * obj->nTargets);
        memcpy(clone->array, obj->array, sizeof(float) * 3 * obj->nTargets);
        
        clone->tags = (char **) malloc(sizeof(char *) * obj->nTargets);

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

            clone->tags[iTarget] = (char *) malloc(sizeof(char) * 256);
            strcpy(clone->tags[iTarget], obj->tags[iTarget]);
            
        }

        return clone;

    }

    void targets_copy(targets_obj * dest, const targets_obj * src) {

        unsigned int iTarget;

        dest->nTargets = src->nTargets;
        memcpy(dest->array, src->array, sizeof(float) * 3 * src->nTargets);
        
        for (iTarget = 0; iTarget < src->nTargets; iTarget++) {

            strcpy(dest->tags[iTarget], src->tags[iTarget]);

        }

    }

    void targets_zero(targets_obj * obj) {

        unsigned int iTarget;

        memset(obj->array, 0x00, sizeof(float) * 3 * obj->nTargets);
        
        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {
            
            strcpy(obj->tags[iTarget], "");

        }

    }

    void targets_printf(const targets_obj * obj) {

        unsigned int iTarget;

        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

            printf("[%s]: %+1.3f %+1.3f %+1.3f\n",
                   obj->tags[iTarget],
                   obj->array[iTarget * 3 + 0],
                   obj->array[iTarget * 3 + 1],
                   obj->array[iTarget * 3 + 2]);
            
        }

    }
