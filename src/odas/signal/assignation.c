
   /**
    * \file     assignation.c
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
    
    #include <signal/assignation.h>

    assignations_obj * assignations_construct_zero(const unsigned int nAssignations, const unsigned int nPots) {

    	assignations_obj * obj;

        obj = (assignations_obj *) malloc(sizeof(assignations_obj));

        obj->nAssignations = nAssignations;
        obj->nPots = nPots;
        obj->array = (signed int *) malloc(sizeof(signed int) * nAssignations * nPots);
        memset(obj->array, 0x00, nAssignations * nPots * sizeof(signed int));

    	return obj;

    }

    void assignations_destroy(assignations_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void assignations_printf(const assignations_obj * obj) {

        unsigned int iAssignation;
        unsigned int iPot;

        for (iAssignation = 0; iAssignation < obj->nAssignations; iAssignation++) {

            for (iPot = 0; iPot < obj->nPots; iPot++) {

                printf("%+01d ",obj->array[iAssignation * obj->nPots + iPot]);

            }

            printf("\n");

        }

    }
