#ifndef __ODAS_GENERAL_FORMAT
#define __ODAS_GENERAL_FORMAT

    #include <stdlib.h>
    #include <stdio.h>

    typedef enum format_type { 
        
        format_undefined = 0,
        format_bin08 = 8, 
        format_bin16 = 16, 
        format_bin24 = 24, 
        format_bin32 = 32, 
        format_float = 1, 
        format_json = 2,

    } format_type;

    typedef struct format_obj {

        format_type type;

    } format_obj;

    format_obj * format_construct();

    format_obj * format_construct_bin(const unsigned int nBits);

    format_obj * format_construct_float();    

    format_obj * format_construct_json();

    format_obj * format_clone(const format_obj * obj);

    void format_destroy(format_obj * obj);

    void format_printf(const format_obj * obj);

#endif