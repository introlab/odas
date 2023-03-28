    /**
    * \file     con_spectra.c
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
    
    #include <connector/con_spectra.h>

    con_spectra_obj * con_spectra_construct(const unsigned int nOuts, const msg_spectra_cfg * msg_spectra_config) {

        con_spectra_obj * obj;
        unsigned int iOut;

        obj = (con_spectra_obj *) malloc(sizeof(con_spectra_obj));

        obj->nOuts = nOuts;

        obj->in = msg_spectra_construct(msg_spectra_config);

        obj->outs = (msg_spectra_obj **) malloc(sizeof(msg_spectra_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_spectra_construct(msg_spectra_config);
        }

        return obj;

    }

    void con_spectra_destroy(con_spectra_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_spectra_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_spectra_destroy(obj->in);

        free((void *) obj);

    }

    int con_spectra_process(con_spectra_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_spectra_copy(obj->outs[iOut], obj->in);
        }

        if (msg_spectra_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }
