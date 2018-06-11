#ifndef __ODAS_MODULE_LAG
#define __ODAS_MODULE_LAG

   /**
    * \file     mod_lag.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-24
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include "../message/msg_spectra.h"

    typedef struct mod_lag_obj {

        msg_spectra_obj * in;
        msg_spectra_obj * out;

        freqs_obj ** freqs;
        unsigned int nElements;

        char enabled;

    } mod_lag_obj;

    typedef struct mod_lag_cfg {
        
        unsigned int nElements;

    } mod_lag_cfg;

    mod_lag_obj * mod_lag_construct(const mod_lag_cfg * mod_lag_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_lag_destroy(mod_lag_obj * obj);

    int mod_lag_process(mod_lag_obj * obj);

    void mod_lag_connect(mod_lag_obj * obj, msg_spectra_obj * in, msg_spectra_obj * out);

    void mod_lag_disconnect(mod_lag_obj * obj);

    void mod_lag_enable(mod_lag_obj * obj);

    void mod_lag_disable(mod_lag_obj * obj);

    mod_lag_cfg * mod_lag_cfg_construct(void);

    void mod_lag_cfg_destroy(mod_lag_cfg * cfg);

    void mod_lag_cfg_printf(const mod_lag_cfg * cfg);

#endif