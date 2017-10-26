#ifndef __ODAS_GENERAL_FORMAT
#define __ODAS_GENERAL_FORMAT

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