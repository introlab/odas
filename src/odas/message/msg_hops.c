
   /**
    * \file     msg_hops.c
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

    #include <message/msg_hops.h>

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * msg_hops_config) {

        msg_hops_obj * obj;

        obj = (msg_hops_obj *) malloc(sizeof(msg_hops_obj));

        obj->timeStamp = 0;
        obj->hops = hops_construct_zero(msg_hops_config->nChannels, msg_hops_config->hopSize);

        return obj;

    }

    void msg_hops_destroy(msg_hops_obj * obj) {

        hops_destroy(obj->hops);
        free((void *) obj);

    }

    void msg_hops_copy(msg_hops_obj * dest, const msg_hops_obj * src) {

        dest->timeStamp = src->timeStamp;
        hops_copy(dest->hops, src->hops);

    }

    void msg_hops_zero(msg_hops_obj * obj) {

        obj->timeStamp = 0;
        hops_zero(obj->hops);

    }

    unsigned int msg_hops_isZero(const msg_hops_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_hops_cfg * msg_hops_cfg_construct(void) {

        msg_hops_cfg * cfg;

        cfg = (msg_hops_cfg *) malloc(sizeof(msg_hops_cfg));

        cfg->hopSize = 0;
        cfg->nChannels = 0;

        return cfg;

    }

    void msg_hops_cfg_destroy(msg_hops_cfg * cfg) {

        free((void *) cfg);

    }

    void msg_hops_cfg_printf(const msg_hops_cfg * cfg) {
       
        if (cfg != NULL) {

            printf("msg_hops_cfg (%p)\n", cfg);
            printf(" + hopSize = %u\n", cfg->hopSize);
            printf(" + nChannels = %u\n", cfg->nChannels);        

        }
        else {

            printf("msg_hops_cfg (null)\n");

        }

    }
