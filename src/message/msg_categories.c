
   /**
    * \file     msg_categories.c
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
