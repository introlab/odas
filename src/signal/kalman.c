   
   /**
    * \file     kalman.c
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

    #include <signal/kalman.h>
    
    kalman_obj * kalman_construct_zero(void) {

        kalman_obj * obj;

        obj = (kalman_obj *) malloc(sizeof(kalman_obj));

        obj->x_lm1lm1 = matrix_construct_zero(6,1);
        obj->x_llm1 = matrix_construct_zero(6,1);
        obj->P_lm1lm1 = matrix_construct_zero(6,6);
        obj->P_llm1 = matrix_construct_zero(6,6);

        return obj;

    }

    void kalman_destroy(kalman_obj * obj) {

        matrix_destroy(obj->x_lm1lm1);
        matrix_destroy(obj->x_llm1);
        matrix_destroy(obj->P_lm1lm1);
        matrix_destroy(obj->P_llm1);

        free((void *) obj);

    }
