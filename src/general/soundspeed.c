
   /**
    * \file     soundspeed.c
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
    
    #include <general/soundspeed.h>

    soundspeed_obj * soundspeed_construct_zero(void) {

        soundspeed_obj * obj;

        obj = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        obj->mu = 0.0f;
        obj->sigma2 = 0.0f;

        return obj;

    }

    soundspeed_obj * soundspeed_clone(const soundspeed_obj * obj) {

        soundspeed_obj * clone;

        clone = (soundspeed_obj *) malloc(sizeof(soundspeed_obj));

        clone->mu = obj->mu;
        clone->sigma2 = obj->sigma2;

        return clone;

    }

    void soundspeed_destroy(soundspeed_obj * obj) {

        free((void *) obj);

    }

    void soundspeed_printf(const soundspeed_obj * obj) {

        printf("mu = %f\n",obj->mu);
        printf("sigma2 = %f\n",obj->sigma2);

    }
