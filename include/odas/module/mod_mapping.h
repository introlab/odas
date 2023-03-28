#ifndef __ODAS_MODULE_MAPPING
#define __ODAS_MODULE_MAPPING

   /**
    * \file     mod_mapping.h
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

    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    #include "../general/link.h"
    #include "../system/hop2hop.h"

    typedef struct mod_mapping_obj {

        hop2hop_multiplex_obj * hop2hop_multiplex;
        links_obj * links;

        msg_hops_obj * in;
        msg_hops_obj * out;

        char enabled;

    } mod_mapping_obj;

    typedef struct mod_mapping_cfg {
        
        links_obj * links;

    } mod_mapping_cfg;

    mod_mapping_obj * mod_mapping_construct(const mod_mapping_cfg * mod_mapping_config, const msg_hops_cfg * msg_hops_config);

    void mod_mapping_destroy(mod_mapping_obj * obj);

    int mod_mapping_process(mod_mapping_obj * obj);

    void mod_mapping_connect(mod_mapping_obj * obj, msg_hops_obj * in, msg_hops_obj * out);

    void mod_mapping_disconnect(mod_mapping_obj * obj);

    void mod_mapping_enable(mod_mapping_obj * obj);

    void mod_mapping_disable(mod_mapping_obj * obj);

    mod_mapping_cfg * mod_mapping_cfg_construct(void);

    void mod_mapping_cfg_destroy(mod_mapping_cfg * cfg);

    void mod_mapping_cfg_printf(const mod_mapping_cfg * cfg);

#endif