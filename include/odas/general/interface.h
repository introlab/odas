#ifndef __ODAS_GENERAL_INTERFACE
#define __ODAS_GENERAL_INTERFACE

   /**
    * \file     interface.h
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

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef enum interface_type {

        interface_undefined = 0,
        interface_blackhole = 1,
        interface_file = 2,
        interface_socket = 3,
        interface_soundcard = 4,
        interface_terminal = 5,
        interface_pulseaudio = 6

    } interface_type;

    typedef struct interface_obj {

        interface_type type;

        char * fileName;

        char * ip;
        unsigned int port;

        char * deviceName;

    } interface_obj;

    interface_obj * interface_construct();

    interface_obj * interface_construct_blackhole();

    interface_obj * interface_construct_file(const char * fileName);

    interface_obj * interface_construct_socket(const char * ip, const unsigned int port);

    interface_obj * interface_construct_pulseaudio(const char * sourceName);

    interface_obj * interface_construct_soundcard(const unsigned int card, const unsigned int device);

    interface_obj * interface_construct_soundcard_by_name(char * deviceName);

    interface_obj * interface_construct_terminal(void);

    interface_obj * interface_clone(const interface_obj * obj);

    void interface_destroy(interface_obj * obj);

    void interface_printf(const interface_obj * obj);

#endif