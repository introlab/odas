
   /**
    * \file     mod_tt.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-05-30
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
    
    #include <module/mod_tt.h>

    mod_tt_obj * mod_tt_construct(const mod_tt_cfg * mod_tt_config, const msg_targets_cfg * msg_targets_config, const msg_tracks_cfg * msg_tracks_config) {

        mod_tt_obj * obj;
        unsigned int iTrack;

        obj = (mod_tt_obj *) malloc(sizeof(mod_tt_obj));

        obj->nTargets = msg_targets_config->nTargets;
        obj->nTracks = msg_tracks_config->nTracks;

        obj->tags = (char **) malloc(sizeof(char *) * obj->nTracks);

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            obj->tags[iTrack] = (char *) malloc(sizeof(char) * 256);
            memset(obj->tags[iTrack], 0x00, sizeof(char) * 256);

        }

        obj->id = 0;

        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * obj->nTracks);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * obj->nTracks);

        obj->array = (float *) malloc(sizeof(float) * obj->nTracks * 3);
        memset(obj->array, 0x00, sizeof(float) * obj->nTracks * 3);

        obj->in = (msg_targets_obj *) NULL;
        obj->out = (msg_tracks_obj *) NULL;

        obj->enabled = 0;

        return obj;

    }

    void mod_tt_destroy(mod_tt_obj * obj) {

        unsigned int iTrack;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            free((void *) obj->tags[iTrack]);

        }

        free((void *) obj->tags);

        free((void *) obj->ids);

        free((void *) obj);

    }

    int mod_tt_process(mod_tt_obj * obj) {

        int rtnValue;

        unsigned int iTarget;
        unsigned int iTrack;
        char matchFound;

        if (msg_targets_isZero(obj->in) == 0) {

            if (obj->enabled == 1) {

                for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

                    if (strcmp(obj->in->targets->tags[iTarget], "") != 0) {

                        matchFound = 0x00;

                        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

                            if (strcmp(obj->tags[iTrack], obj->in->targets->tags[iTarget]) == 0) {

                                matchFound = 0x01;
                                break;

                            }

                        }

                        if (matchFound == 0x00) {

                            for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

                                if (strcmp(obj->tags[iTrack], "") == 0) {

                                    obj->id++;

                                    strcpy(obj->tags[iTrack], obj->in->targets->tags[iTarget]);
                                    obj->ids[iTrack] = obj->id;
                                    obj->array[iTrack*3+0] = obj->in->targets->array[iTrack*3+0];
                                    obj->array[iTrack*3+1] = obj->in->targets->array[iTrack*3+1];
                                    obj->array[iTrack*3+2] = obj->in->targets->array[iTrack*3+2];

                                    break;

                                }

                            }

                        }

                    }

                }

                for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

                    if (strcmp(obj->tags[iTrack], "") != 0) {

                        matchFound = 0x00;

                        for (iTarget = 0; iTarget < obj->nTargets; iTarget++) {

                            if (strcmp(obj->tags[iTrack], obj->in->targets->tags[iTarget]) == 0) {

                                matchFound = 0x01;
                                break;

                            }

                        }

                        if (matchFound == 0x00) {

                            strcpy(obj->tags[iTrack], "");
                            obj->ids[iTrack] = 0;

                        }

                    }

                }

                for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

                    obj->out->tracks->ids[iTrack] = obj->ids[iTrack];
                    strcpy(obj->out->tracks->tags[iTrack], obj->tags[iTrack]);
                    obj->out->tracks->array[iTrack*3+0] = obj->array[iTrack*3+0];
                    obj->out->tracks->array[iTrack*3+1] = obj->array[iTrack*3+1];
                    obj->out->tracks->array[iTrack*3+2] = obj->array[iTrack*3+2];
                    obj->out->tracks->activity[iTrack] = -1.0f;

                }

            }
            else {

                tracks_zero(obj->out->tracks);

            }

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_tracks_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_tt_connect(mod_tt_obj * obj, msg_targets_obj * in, msg_tracks_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_tt_disconnect(mod_tt_obj * obj) {

        obj->in = (msg_targets_obj *) NULL;
        obj->out = (msg_tracks_obj *) NULL;

    }

    void mod_tt_enable(mod_tt_obj * obj) {

        obj->enabled = 1;

    }

    void mod_tt_disable(mod_tt_obj * obj) {

        obj->enabled = 0;

    }

    mod_tt_cfg * mod_tt_cfg_construct(void) {

        mod_tt_cfg * cfg;

        cfg = (mod_tt_cfg *) malloc(sizeof(mod_tt_cfg));

        return cfg;

    }

    void mod_tt_cfg_destroy(mod_tt_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_tt_cfg_printf(const mod_tt_cfg * cfg) {

        if (cfg != NULL) {

            printf("msg_tt_cfg (%p)\n", cfg);

        }
        else {

            printf("msg_tt_cfg (null)\n");

        }

    }