#ifndef __ODAS_GENERAL_INTERFACE
#define __ODAS_GENERAL_INTERFACE

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef enum interface_type { 
        
        interface_undefined = 0,
        interface_file = 1,
        interface_socket = 2, 
        interface_soundcard = 3, 
        
    } interface_type;

    typedef struct interface_obj {

        interface_type type;

        char * fileName;

        char * ip;
        unsigned int port;

        unsigned int card;
        unsigned int device;

    } interface_obj;

    interface_obj * interface_construct();

    interface_obj * interface_construct_file(const char * fileName);

    interface_obj * interface_construct_socket(const char * ip, const unsigned int port);

    interface_obj * interface_construct_soundcard(const unsigned int card, const unsigned int device);

    interface_obj * interface_clone(const interface_obj * obj);

    void interface_destroy(interface_obj * obj);

    void interface_printf(const interface_obj * obj);

#endif