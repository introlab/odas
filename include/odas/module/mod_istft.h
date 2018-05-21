#ifndef __ODAS_MODULE_ISTFT
#define __ODAS_MODULE_ISTFT

   /**
    * \file     mod_istft.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
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

    #include "../system/freq2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2hop.h"
        
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    typedef struct mod_istft_obj {

        freq2frame_obj * freq2frame;
        frames_obj * frames;
        frame2hop_obj * frame2hop;

        msg_spectra_obj * in;        
        msg_hops_obj * out;

        char enabled;

    } mod_istft_obj;

    typedef struct mod_istft_cfg {
        
    } mod_istft_cfg;

    mod_istft_obj * mod_istft_construct(const mod_istft_cfg * mod_istft_config, const msg_spectra_cfg * msg_spectra_config, const msg_hops_cfg * msg_hops_config);

    void mod_istft_destroy(mod_istft_obj * obj);

    int mod_istft_process(mod_istft_obj * obj);

    void mod_istft_connect(mod_istft_obj * obj, msg_spectra_obj * in, msg_hops_obj * out);

    void mod_istft_disconnect(mod_istft_obj * obj);

    void mod_istft_enable(mod_istft_obj * obj);

    void mod_istft_disable(mod_istft_obj * obj);

    mod_istft_cfg * mod_istft_cfg_construct(void);

    void mod_istft_cfg_destroy(mod_istft_cfg * cfg);

    void mod_istft_cfg_printf(const mod_istft_cfg * cfg);

#endif