
   /**
    * \file     msg_targets.c
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

    #include <message/msg_targets.h>

    msg_targets_obj * msg_targets_construct(const msg_targets_cfg * cfg) {

        msg_targets_obj * obj;

        obj = (msg_targets_obj *) malloc(sizeof(msg_targets_obj));

        obj->timeStamp = 0;
        obj->fS = cfg->fS;
        obj->targets = targets_construct_zero(cfg->nTargets);

        return obj;

    }

    void msg_targets_destroy(msg_targets_obj * obj) {

        targets_destroy(obj->targets);
        free((void *) obj);

    }

    void msg_targets_copy(msg_targets_obj * dest, const msg_targets_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        targets_copy(dest->targets, src->targets);

    }

    void msg_targets_zero(msg_targets_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        targets_zero(obj->targets);

    }

    unsigned int msg_targets_isZero(const msg_targets_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_targets_cfg * msg_targets_cfg_construct(void) {

        msg_targets_cfg * cfg;

        cfg = (msg_targets_cfg *) malloc(sizeof(msg_targets_cfg));

        cfg->nTargets = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_targets_cfg_destroy(msg_targets_cfg * cfg) {

        free((void *) cfg);

    }

    void msg_targets_cfg_printf(const msg_targets_cfg * msg_targets_config) {

        printf("nTargets = %u\n", msg_targets_config->nTargets);
        printf("fS = %u\n", msg_targets_config->fS);        

    }    
