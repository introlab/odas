#ifndef __ODAS_GENERAL_FORMAT
#define __ODAS_GENERAL_FORMAT

   /**
    * \file     format.h
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