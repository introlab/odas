
    /**
    * \file     interface.c
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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

    #include <general/interface.h>

    interface_obj * interface_construct() {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        obj->type = interface_undefined;

        obj->fileName = (char *) NULL;
        obj->port = 0;
        obj->deviceName = (char *) NULL;

        return obj;

    }

    interface_obj * interface_construct_blackhole() {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        obj->type = interface_blackhole;

        obj->fileName = (char *) NULL;
        obj->port = 0;
        obj->deviceName = (char *) NULL;

        return obj;

    }

    interface_obj * interface_construct_file(const char * fileName) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        obj->type = interface_file;

        obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName)+1));
        strcpy(obj->fileName, fileName);
        obj->port = 0;
        obj->deviceName = (char *) NULL;

        return obj;

    }

    interface_obj * interface_construct_socket(const unsigned int port) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        obj->type = interface_socket;

        obj->fileName = (char *) NULL;
        obj->port = port;
        obj->deviceName = (char *) NULL;

        return obj;        

    }

   interface_obj * interface_construct_soundcard(const char * deviceName) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        obj->type = interface_soundcard;

        obj->fileName = (char *) NULL;
        obj->port = 0;
        obj->deviceName = (char *) malloc(sizeof(char) * (strlen(deviceName)+1));
        strcpy(obj->deviceName, deviceName);

       return obj;

   }

    interface_obj * interface_construct_terminal(void) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        obj->type = interface_terminal;

        obj->fileName = (char *) NULL;
        obj->port = 0;
        obj->deviceName = (char *) NULL;

        return obj;

    }

    interface_obj * interface_clone(const interface_obj * obj) {

        interface_obj * clone;

        clone = interface_construct();

        clone->type = obj->type;        

        if (obj->type == interface_file) {
            
            clone->fileName = (char *) malloc(sizeof(char) * (strlen(obj->fileName) + 1));
            strcpy(clone->fileName, obj->fileName);

        }

        if (obj->type == interface_socket) {
            
            clone->port = obj->port;

        }

        if (obj->type == interface_soundcard) {

            clone->deviceName = (char *) malloc(sizeof(char) * (strlen(obj->deviceName) + 1));
            strcpy(clone->deviceName, obj->deviceName);

        }

        return clone;

    }

    void interface_destroy(interface_obj * obj) {

        if (obj->fileName != NULL) {

            free((void *) obj->fileName);

        }

        if (obj->deviceName != NULL) {

            free((void *) obj->deviceName);

        }

        free((void *) obj);

    }

    void interface_printf(const interface_obj * obj) {

        if (obj != NULL) {

            switch(obj->type) {

                case interface_blackhole:

                    printf("type = blackhole\n");

                break;

                case interface_file:

                    printf("type = file, fileName = %s\n", obj->fileName);

                break;

                case interface_socket:

                    printf("type = socket, port = %u\n", obj->port);

                break;

                case interface_soundcard:

                    printf("type = soundcard, deviceName = %s\n", obj->deviceName);

                    break;

                case interface_terminal:

                    printf("type = terminal\n");

                break;

            }

        }
        else {

            printf("(null)\n");

        }

    }
