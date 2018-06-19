
   /**
    * \file     mod_align.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-14
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
    
    #include <module/mod_align.h>    

    mod_align_obj * mod_align_construct(const mod_align_cfg * mod_align_config, const msg_targets_cfg * msg_targets_in_config, const msg_hops_cfg * msg_hops_in_config, const msg_targets_cfg * msg_targets_out_config) {

        mod_align_obj * obj;

        obj = (mod_align_obj *) malloc(sizeof(mod_align_obj));

        obj->in1 = (msg_targets_obj *) NULL;
        obj->in2 = (msg_hops_obj *) NULL;
        obj->out = (msg_targets_obj *) NULL;

        obj->fSin = msg_targets_in_config->fS;
        obj->fSout = msg_targets_out_config->fS;

        obj->targets = targets_construct_zero(msg_targets_in_config->nTargets);

        obj->enabled = 0;

        return obj;

    }

    void mod_align_destroy(mod_align_obj * obj) {

        targets_destroy(obj->targets);

        free((void *) obj);

    }

    int mod_align_process_push(mod_align_obj * obj) {

        int rtnValue;

        if (obj->in1->timeStamp != 0) {

            if (obj->enabled == 1) {

                targets_copy(obj->targets, obj->in1->targets);

            }

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }     

        return rtnValue;   

    }

    int mod_align_process_pop(mod_align_obj * obj) {

        int rtnValue;

        if (obj->in2->timeStamp != 0) {

            if (obj->enabled == 1) {

                targets_copy(obj->out->targets, obj->targets);

            }
            else {

                targets_zero(obj->out->targets);

            }

            obj->out->fS = obj->fSout;
            obj->out->timeStamp = obj->in2->timeStamp;

            rtnValue = 0;

        }
        else {

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_align_connect(mod_align_obj * obj, msg_targets_obj * in1, msg_hops_obj * in2, msg_targets_obj * out) {

        obj->in1 = in1;
        obj->in2 = in2;
        obj->out = out;

    }

    void mod_align_disconnect(mod_align_obj * obj) {

        obj->in1 = (msg_targets_obj *) NULL;
        obj->in2 = (msg_hops_obj *) NULL;
        obj->out = (msg_targets_obj *) NULL;

    }

    void mod_align_enable(mod_align_obj * obj) {

        obj->enabled = 1;

    }

    void mod_align_disable(mod_align_obj * obj) {

        obj->enabled = 0;

    }

    mod_align_cfg * mod_align_cfg_construct(void) {

        mod_align_cfg * cfg;

        cfg = (mod_align_cfg *) malloc(sizeof(mod_align_cfg));

        return cfg;

    }

    void mod_align_cfg_destroy(mod_align_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_align_cfg_printf(const mod_align_cfg * cfg) {

    }