#ifndef __ODAS_MODULE_STFT
#define __ODAS_MODULE_STFT

   /**
    * \file     mod_stft.h
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

    #include "../system/hop2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2freq.h"
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    typedef struct mod_stft_obj {

        hop2frame_obj * hop2frame;
        frames_obj * frames;
        frame2freq_obj * frame2freq;

        msg_hops_obj * in;
        msg_spectra_obj * out;        

    } mod_stft_obj;

    typedef struct mod_stft_cfg {
        
    } mod_stft_cfg;

    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * mod_stft_config, const msg_hops_cfg * msg_hops_config, const msg_spectra_cfg * msg_spectra_config);

    void mod_stft_destroy(mod_stft_obj * obj);

    int mod_stft_process(mod_stft_obj * obj);

    void mod_stft_connect(mod_stft_obj * obj, msg_hops_obj * in, msg_spectra_obj * out);

    void mod_stft_disconnect(mod_stft_obj * obj);

    mod_stft_cfg * mod_stft_cfg_construct(void);

    void mod_stft_cfg_destroy(mod_stft_cfg * cfg);

    void mod_stft_cfg_printf(const mod_stft_cfg * cfg);

#endif