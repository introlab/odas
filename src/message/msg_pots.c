
   /**
    * \file     msg_pots.c
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
    
    #include <message/msg_pots.h>

    msg_pots_obj * msg_pots_construct(const msg_pots_cfg * cfg) {

        msg_pots_obj * obj;

        obj = (msg_pots_obj *) malloc(sizeof(msg_pots_obj));

        obj->timeStamp = 0;
        obj->fS = cfg->fS;
        obj->pots = pots_construct_zero(cfg->nPots);

        return obj;

    }

    void msg_pots_destroy(msg_pots_obj * obj) {

        pots_destroy(obj->pots);
        free((void *) obj);

    }

    void msg_pots_copy(msg_pots_obj * dest, const msg_pots_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        pots_copy(dest->pots, src->pots);

    }

    void msg_pots_zero(msg_pots_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        pots_zero(obj->pots);

    }

    unsigned int msg_pots_isZero(const msg_pots_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_pots_cfg * msg_pots_cfg_construct(void) {

        msg_pots_cfg * cfg;

        cfg = (msg_pots_cfg *) malloc(sizeof(msg_pots_cfg));

        cfg->nPots = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_pots_cfg_destroy(msg_pots_cfg * cfg) {

        free((void *) cfg);

    }

    void msg_pots_cfg_printf(const msg_pots_cfg * msg_pots_config) {

        printf("nPots = %u\n", msg_pots_config->nPots);        
        printf("fS = %u\n", msg_pots_config->fS);        

    }
