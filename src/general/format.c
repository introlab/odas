
   /**
    * \file     format.c
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

    #include <general/format.h>

    format_obj * format_construct() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_undefined;

        return obj;

    }

    format_obj * format_construct_undefined() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_undefined;

        return obj;        
        
    }

    format_obj * format_construct_binary_int(const unsigned int nBits) {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        switch(nBits) {

            case 8:

                obj->type = format_binary_int08;

            break;

            case 16:

                obj->type = format_binary_int16;

            break;

            case 24:

                obj->type = format_binary_int24;

            break;

            case 32:

                obj->type = format_binary_int32;

            break;

            default:

                printf("Wrong number of bits.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return obj;

    }

    format_obj * format_construct_binary_float() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_binary_float;

        return obj;

    }

    format_obj * format_construct_text_json() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_text_json;

        return obj;

    }

    format_obj * format_clone(const format_obj * obj) {

        format_obj * clone;

        clone = format_construct();

        clone->type = obj->type;

        return clone;

    }

    void format_destroy(format_obj * obj) {

        free((void *) obj);

    }

    void format_printf(const format_obj * obj) {

        if (obj != NULL) {

            switch(obj->type) {

                case format_binary_int08:
                    printf("type = binary_int08\n");
                break;

                case format_binary_int16:
                    printf("type = binary_int16\n");
                break;

                case format_binary_int24:
                    printf("type = binary_int24\n");
                break;

                case format_binary_int32:
                    printf("type = binary_int32\n");
                break;

                case format_binary_float:
                    printf("type = binary_float\n");
                break;

                case format_text_json:
                    printf("type = text_json\n");
                break;

            }

        }
        else {
            printf("(null)\n");
        }

    }
