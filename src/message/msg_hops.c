
   /**
    * \file     msg_hops.c
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

    #include <message/msg_hops.h>

    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * msg_hops_config) {

        msg_hops_obj * obj;

        obj = (msg_hops_obj *) malloc(sizeof(msg_hops_obj));

        obj->timeStamp = 0;
        obj->fS = msg_hops_config->fS;
        obj->hops = hops_construct_zero(msg_hops_config->nChannels, msg_hops_config->hopSize);

        return obj;

    }

    void msg_hops_destroy(msg_hops_obj * obj) {

        hops_destroy(obj->hops);
        free((void *) obj);

    }

    void msg_hops_copy(msg_hops_obj * dest, const msg_hops_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        hops_copy(dest->hops, src->hops);

    }

    void msg_hops_zero(msg_hops_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
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
        cfg->fS = 0;

        return cfg;

    }

    void msg_hops_cfg_destroy(msg_hops_cfg * msg_hops_config) {

        free((void *) msg_hops_config);

    }

    void msg_hops_cfg_printf(const msg_hops_cfg * msg_hops_config) {
       
        printf("hopSize = %u\n", msg_hops_config->hopSize);
        printf("nChannels = %u\n", msg_hops_config->nChannels);        
        printf("fS = %u\n", msg_hops_config->fS);

    }
