
    /**
    * \file     con_powers.c
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
    
    #include <connector/con_powers.h>

    con_powers_obj * con_powers_construct(const unsigned int nOuts, const msg_powers_cfg * msg_powers_config) {

        con_powers_obj * obj;
        unsigned int iOut;

        obj = (con_powers_obj *) malloc(sizeof(con_powers_obj));

        obj->nOuts = nOuts;

        obj->in = msg_powers_construct(msg_powers_config);

        obj->outs = (msg_powers_obj **) malloc(sizeof(msg_powers_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_powers_construct(msg_powers_config);
        }

        return obj;

    }

    void con_powers_destroy(con_powers_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_powers_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_powers_destroy(obj->in);

        free((void *) obj);

    }

    int con_powers_process(con_powers_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_powers_copy(obj->outs[iOut], obj->in);
        }

        if (msg_powers_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }
