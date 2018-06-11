
   /**
    * \file     ser_hops.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-06
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

	#include <serializer/ser_hops.h>

    ser_hops_obj * ser_hops_construct(const ser_hops_cfg * ser_hops_config, const msg_hops_cfg * msg_hops_config) {

    	ser_hops_obj * obj;

    	obj = (ser_hops_obj *) malloc(sizeof(ser_hops_obj));

        obj->timeStamp = 0;

        obj->hopSize = msg_hops_config->hopSize;
        obj->nChannels = msg_hops_config->nChannels;
        obj->fS = msg_hops_config->fS;

        obj->string = (char *) malloc(sizeof(char) * (obj->hopSize * 8 + 1));
        memset(obj->string, 0x00, sizeof(char) * (obj->hopSize * 8 + 1));

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (char *) NULL;

    	return obj;

    }

    void ser_hops_destroy(ser_hops_obj * obj) {

    	free((void *) obj);

    }

    void ser_hops_connect(ser_hops_obj * obj, msg_hops_obj * in, char * out) {

    	obj->in = in;
    	obj->out = out;

    }

    void ser_hops_disconnect(ser_hops_obj * obj) {

    	obj->in = (msg_hops_obj *) NULL;
    	obj->out = (char *) NULL;

    }

    void ser_hops_process(ser_hops_obj * obj) {

    	unsigned int iChannel;
        unsigned int iSample;
        char number[256];

    	strcpy(obj->out, "");
    	strcat(obj->out, "{\n");
    	strcat(obj->out, "    \"hops\":\n");
		strcat(obj->out, "        [\n");

    	for (iChannel = 0; iChannel < obj->nChannels; iChannel++) {

            strcat(obj->out, "            [");

            for (iSample = 0; iSample < obj->hopSize; iSample++) {

                sprintf(number, "%1.3e", obj->in->hops->array[iChannel][iSample]);
                strcat(obj->out, number);

                if (iSample != (obj->hopSize - 1)) {
                    strcat(obj->out, ",");
                }

            }

            strcat(obj->out, "]");

    		if (iChannel != (obj->nChannels - 1)) {
    			strcat(obj->out, ",");
    		}

    		strcat(obj->out, "\n");

    	}

    	strcat(obj->out, "        ]\n");
    	strcat(obj->out, "}\n");

    }

    ser_hops_cfg * ser_hops_cfg_construct(void) {

    }

    void ser_hops_cfg_destroy(ser_hops_cfg * cfg) {

    }