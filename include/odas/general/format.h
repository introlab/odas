#ifndef __ODAS_GENERAL_FORMAT
#define __ODAS_GENERAL_FORMAT

   /**
    * \file     format.h
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

    typedef enum format_type { 
        
        format_undefined = 0,
        format_binary_int08 = 8, 
        format_binary_int16 = 16, 
        format_binary_int24 = 24, 
        format_binary_int32 = 32, 
        format_binary_float = 1, 
        format_text_json = 2,

    } format_type;

    typedef struct format_obj {

        format_type type;

    } format_obj;

    format_obj * format_construct();

    format_obj * format_construct_undefined();

    format_obj * format_construct_binary_int(const unsigned int nBits);

    format_obj * format_construct_binary_float();    

    format_obj * format_construct_text_json();

    format_obj * format_clone(const format_obj * obj);

    void format_destroy(format_obj * obj);

    void format_printf(const format_obj * obj);

#endif