
   /**
    * \file     msg_categories.c
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

    #include <message/msg_categories.h>

    msg_categories_obj * msg_categories_construct(const msg_categories_cfg * msg_categories_config) {

        msg_categories_obj * obj;

        obj = (msg_categories_obj *) malloc(sizeof(msg_categories_obj));

        obj->timeStamp = 0;
        obj->fS = msg_categories_config->fS;
        obj->categories = categories_construct_zero(msg_categories_config->nChannels);

        return obj;

    }

    void msg_categories_destroy(msg_categories_obj * obj) {

        categories_destroy(obj->categories);
        free((void *) obj);

    }

    void msg_categories_copy(msg_categories_obj * dest, const msg_categories_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;

        categories_copy(dest->categories, src->categories);

    }

    void msg_categories_zero(msg_categories_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        categories_zero(obj->categories);

    }

    unsigned int msg_categories_isZero(const msg_categories_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_categories_cfg * msg_categories_cfg_construct(void) {

        msg_categories_cfg * cfg;

        cfg = (msg_categories_cfg *) malloc(sizeof(msg_categories_cfg));

        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_categories_cfg_destroy(msg_categories_cfg * msg_categories_config) {

        free((void *) msg_categories_config);

    }

    void msg_categories_cfg_printf(const msg_categories_cfg * msg_categories_config) {

        printf("nChannels = %u\n", msg_categories_config->nChannels);        
        printf("fS = %u\n", msg_categories_config->fS);

    }
