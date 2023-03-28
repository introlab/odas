
   /**
    * \file     mod_volume.c
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
    
    #include <module/mod_volume.h>

    mod_volume_obj * mod_volume_construct(const mod_volume_cfg * mod_volume_config, const msg_hops_cfg * msg_hops_config) {

        mod_volume_obj * obj;

        obj = (mod_volume_obj *) malloc(sizeof(mod_volume_obj));

        obj->hop2hop_gain = hop2hop_gain_construct_zero(msg_hops_config->hopSize, mod_volume_config->gain);

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

        obj->enabled = 0;

        return obj;

    }

    void mod_volume_destroy(mod_volume_obj * obj) {

        hop2hop_gain_destroy(obj->hop2hop_gain);

    }

    int mod_volume_process(mod_volume_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            if (obj->enabled == 1) {

                hop2hop_gain_process(obj->hop2hop_gain, 
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

    void mod_volume_connect(mod_volume_obj * obj, msg_hops_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_volume_disconnect(mod_volume_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    void mod_volume_enable(mod_volume_obj * obj) {

        obj->enabled = 1;

    }

    void mod_volume_disable(mod_volume_obj * obj) {

        obj->enabled = 0;

    }

    mod_volume_cfg * mod_volume_cfg_construct(void) {

        mod_volume_cfg * cfg;

        cfg = (mod_volume_cfg *) malloc(sizeof(mod_volume_cfg));

        return cfg;

    }

    void mod_volume_cfg_destroy(mod_volume_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_volume_cfg_printf(const mod_volume_cfg * cfg) {

    }
