#ifndef __ODAS_GENERAL_INTERFACE
#define __ODAS_GENERAL_INTERFACE

   /**
    * \file     interface.h
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

    interface_obj * interface_construct_soundcard(const unsigned int card, const unsigned int device);

    interface_obj * interface_construct_soundcard_by_name(char * deviceName);

    interface_obj * interface_construct_terminal(void);

    interface_obj * interface_clone(const interface_obj * obj);

    void interface_destroy(interface_obj * obj);

    void interface_printf(const interface_obj * obj);

#endif