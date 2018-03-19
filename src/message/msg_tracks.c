
   /**
    * \file     msg_tracks.c
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

    #include <message/msg_tracks.h>

    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg) {

        msg_tracks_obj * obj;

        obj = (msg_tracks_obj *) malloc(sizeof(msg_tracks_obj));

        obj->timeStamp = 0;
        obj->fS = cfg->fS;
        obj->tracks = tracks_construct_zero(cfg->nTracks);

        return obj;

    }

    void msg_tracks_destroy(msg_tracks_obj * obj) {

        tracks_destroy(obj->tracks);
        free((void *) obj);

    }

    void msg_tracks_copy(msg_tracks_obj * dest, const msg_tracks_obj * src) {

        dest->timeStamp = src->timeStamp;
        dest->fS = src->fS;
        tracks_copy(dest->tracks, src->tracks);

    }

    void msg_tracks_zero(msg_tracks_obj * obj) {

        obj->timeStamp = 0;
        obj->fS = 0;
        tracks_zero(obj->tracks);

    }

    unsigned int msg_tracks_isZero(const msg_tracks_obj * obj) {

        unsigned int rtnValue;

        if (obj->timeStamp == 0) {
            rtnValue = 1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }

    msg_tracks_cfg * msg_tracks_cfg_construct(void) {

        msg_tracks_cfg * cfg;

        cfg = (msg_tracks_cfg *) malloc(sizeof(msg_tracks_cfg));

        cfg->nTracks = 0;

        return cfg;

    }

    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg) {

        free((void *) cfg);

    }

    void msg_tracks_cfg_printf(const msg_tracks_cfg * msg_tracks_config) {

        printf("nTracks = %u\n", msg_tracks_config->nTracks);
        printf("fS = %u\n", msg_tracks_config->fS);        

    }    
