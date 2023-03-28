
   /**
    * \file     msg_powers.c
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
    
    #include <message/msg_powers.h>

    msg_powers_obj * msg_powers_construct(const msg_powers_cfg * msg_powers_config) {

        msg_powers_obj * obj;

        obj = (msg_powers_obj *) malloc(sizeof(msg_powers_obj));

        obj->timeStamp = 0;
        obj->fS = msg_powers_config->fS;
        obj->envs = envs_construct_zero(msg_powers_config->nChannels, msg_powers_config->halfFrameSize);

        return obj;

    }

    void msg_powers_destroy(msg_powers_obj * obj) {

        envs_destroy(obj->envs);
        free((void *) obj);

    }

    void msg_powers_copy(msg_powers_obj * dest, const msg_powers_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        envs_copy(dest->envs, src->envs);

    }

    void msg_powers_zero(msg_powers_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        envs_zero(obj->envs);

    }

    unsigned int msg_powers_isZero(const msg_powers_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;        

    }

    msg_powers_cfg * msg_powers_cfg_construct(void) {

        msg_powers_cfg * cfg;

        cfg = (msg_powers_cfg *) malloc(sizeof(msg_powers_cfg));

        cfg->halfFrameSize = 0;
        cfg->nChannels = 0;
        cfg->fS = 0;

        return cfg;

    }

    void msg_powers_cfg_destroy(msg_powers_cfg * msg_powers_config) {

        free((void *) msg_powers_config);

    }

    void msg_powers_cfg_printf(const msg_powers_cfg * msg_powers_config) {

        if (msg_powers_config != NULL) {

            printf("halfFrameSize = %u\n", msg_powers_config->halfFrameSize);
            printf("nChannels = %u\n", msg_powers_config->nChannels);
            printf("fS = %u\n", msg_powers_config->fS);

        }
        else {

            printf("(null)\n");

        }    

    }
