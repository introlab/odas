
   /**
    * \file     interface.c
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

    #include <general/interface.h>

    interface_obj * interface_construct() {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_undefined;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_construct_blackhole() {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_blackhole;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_construct_file(const char * fileName) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_file;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName)+1));
            strcpy(obj->fileName, fileName);

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_construct_socket(const char * ip, const unsigned int port) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_socket;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) malloc(sizeof(char) * (strlen(ip)+1));
            strcpy(obj->ip, ip);
            obj->port = port;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;        

    }

    interface_obj * interface_construct_pulseaudio(const char * sourceName) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_pulseaudio;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

            obj->deviceName = (char *) malloc(sizeof(char) * (strlen(sourceName)+1));
            strcpy(obj->deviceName, sourceName);

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;        

    }

   interface_obj * interface_construct_soundcard(const unsigned int card, const unsigned int device) {

        char * deviceName = (char *) malloc(sizeof(char) * 1024);

        sprintf(deviceName, "hw:%u,%u", card, device);

        interface_obj * obj = interface_construct_soundcard_by_name(deviceName);

        free((void* ) deviceName);

        return obj;

   }

   interface_obj * interface_construct_soundcard_by_name(char * deviceName) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

        obj->type = interface_soundcard;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

        // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

        obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

        obj->ip = (char *) NULL;
        obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) malloc(sizeof(char) * (strlen(deviceName)+1));
        strcpy(obj->deviceName, deviceName);

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

        // (Empty)

        return obj;

   }

    interface_obj * interface_construct_terminal(void) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_terminal;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_clone(const interface_obj * obj) {

        interface_obj * clone;

        clone = interface_construct();

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            clone->type = obj->type;        

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            if (obj->type == interface_file) {
                
                clone->fileName = (char *) malloc(sizeof(char) * (strlen(obj->fileName) + 1));
                strcpy(clone->fileName, obj->fileName);

            }

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+                

            if (obj->type == interface_socket) {
                
                clone->ip = (char *) malloc(sizeof(char) * (strlen(obj->ip) + 1));
                strcpy(clone->ip, obj->ip);
                clone->port = obj->port;

            }

        // +----------------------------------------------------------+
        // | Soundcard or Pulseaudio                                  |
        // +----------------------------------------------------------+

            if (obj->type == interface_soundcard || obj->type == interface_pulseaudio) {
                
                clone->deviceName = (char *) malloc(sizeof(char) * (strlen(obj->deviceName) + 1));
                strcpy(clone->deviceName, obj->deviceName);

            }

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return clone;

    }

    void interface_destroy(interface_obj * obj) {

        if (obj->fileName != NULL) {

            free((void *) obj->fileName);

        }

        if (obj->deviceName != NULL) {

            free((void *) obj->deviceName);

        }

        if (obj->ip != NULL) {

            free((void *) obj->ip);

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

                    printf("type = file, fileName = %s\n",obj->fileName);

                break;

                case interface_socket:

                    printf("type = socket, ip = %s, port = %u\n",obj->ip,obj->port);

                break;

                case interface_soundcard:

                    printf("type = soundcard_name, devicename = %s\n",obj->deviceName);

                    break;

                case interface_pulseaudio:

                    printf("type = pulseaudio, devicename = %s\n", obj->deviceName);

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
