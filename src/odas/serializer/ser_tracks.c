    
   /**
    * \file     ser_tracks.c
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

	#include <serializer/ser_tracks.h>    

    ser_tracks_obj * ser_tracks_construct(const ser_tracks_cfg * ser_tracks_config, const msg_tracks_cfg * msg_tracks_config) {

    	ser_tracks_obj * obj;

    	obj = (ser_tracks_obj *) malloc(sizeof(ser_tracks_obj));

        obj->timeStamp = 0;

        obj->nTracks = msg_tracks_config->nTracks;
        obj->fS = msg_tracks_config->fS;

        obj->string = (char *) malloc(sizeof(char) * 1024);
        memset(obj->string, 0x00, sizeof(char) * 1024);

        obj->in = (msg_tracks_obj *) NULL;
        obj->out = (char *) NULL;

    	return obj;

    }

    void ser_tracks_destroy(ser_tracks_obj * obj) {

    	free((void *) obj->string);
    	free((void *) obj);

    }

    void ser_tracks_connect(ser_tracks_obj * obj, msg_tracks_obj * in, char * out) {

    	obj->in = in;
    	obj->out = out;

    }

    void ser_tracks_disconnect(ser_tracks_obj * obj) {

    	obj->in = (msg_tracks_obj *) NULL;
    	obj->out = (char *) NULL;

    }

    void ser_tracks_process(ser_tracks_obj * obj) {

    	unsigned int iTrack;

    	strcpy(obj->out, "");
    	strcat(obj->out, "{\n");
    	strcat(obj->out, "    \"tracks\":\n");
    	strcat(obj->out, "    [\n");

    	for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

    		strcat(obj->out, "        {\"id\": \"");
    		sprintf(obj->string, "%llu", obj->in->tracks->ids[iTrack]);
    		strcat(obj->out, obj->string);

    		strcat(obj->out, "\", \"tag\": \"");
    		sprintf(obj->string, "%s", obj->in->tracks->tags[iTrack]);
    		strcat(obj->out, obj->string);

    		strcat(obj->out, "\", \"x\": ");
    		sprintf(obj->string, "%1.3f", obj->in->tracks->array[iTrack*3 + 0]);
    		strcat(obj->out, obj->string);

    		strcat(obj->out, ", \"y\": ");
    		sprintf(obj->string, "%1.3f", obj->in->tracks->array[iTrack*3 + 1]);
    		strcat(obj->out, obj->string);

    		strcat(obj->out, ", \"z\": ");
    		sprintf(obj->string, "%1.3f", obj->in->tracks->array[iTrack*3 + 2]);
    		strcat(obj->out, obj->string);   		

    		strcat(obj->out, "}");

    		if (iTrack != (obj->nTracks - 1)) {
    			strcat(obj->out, ",");
    		}

    		strcat(obj->out, "\n");

    	}

    	strcat(obj->out, "    ]\n");
    	strcat(obj->out, "}\n");

    }

    ser_tracks_cfg * ser_tracks_cfg_construct(void) {

    }

    void ser_tracks_cfg_destroy(ser_tracks_cfg * cfg) {

    }
