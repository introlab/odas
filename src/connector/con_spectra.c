    
    #include "con_spectra.h"

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