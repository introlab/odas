
   /**
    * \file     msg_targets.c
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
