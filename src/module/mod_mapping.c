
   /**
    * \file     mod_mapping.c
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
    
    #include <module/mod_mapping.h>

    mod_mapping_obj * mod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config) {

        mod_mapping_obj * obj;
        unsigned int iLink;

        obj = (mod_mapping_obj *) malloc(sizeof(mod_mapping_obj));

        obj->hop2hop_multiplex = hop2hop_multiplex_construct_zero(msg_hops_config->hopSize);
        obj->links = links_clone(mod_mapping_config->links);

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

        obj->enabled = 0;

        return obj;

    }

    void mod_mapping_destroy(mod_mapping_obj * obj) {

        links_destroy(obj->links);
        hop2hop_multiplex_destroy(obj->hop2hop_multiplex);
        free((void *) obj);

    }

    int mod_mapping_process(mod_mapping_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            if (obj->enabled == 1) {

                hop2hop_multiplex_process(obj->hop2hop_multiplex, 
                                          obj->links, 
                                          obj->in->hops, 
                                          obj->out->hops);

            }
            else {

                hops_zero(obj->out->hops);

            }

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_hops_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_mapping_connect(mod_mapping_obj * obj, msg_hops_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_mapping_disconnect(mod_mapping_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    void mod_mapping_enable(mod_mapping_obj * obj) {

        obj->enabled = 1;

    }

    void mod_mapping_disable(mod_mapping_obj * obj) {

        obj->enabled = 0;

    }

    mod_mapping_cfg * mod_mapping_cfg_construct(void) {

        mod_mapping_cfg * cfg;

        cfg = (mod_mapping_cfg *) malloc(sizeof(mod_mapping_cfg));

        cfg->links = (links_obj *) NULL;

        return cfg;

    }

    void mod_mapping_cfg_destroy(mod_mapping_cfg * cfg) {

        if (cfg->links != NULL) {
            links_destroy(cfg->links);
        }

        free((void *) cfg);

    }

    void mod_mapping_cfg_printf(const mod_mapping_cfg * cfg) {

        printf("links:"); links_printf(cfg->links);

    }
