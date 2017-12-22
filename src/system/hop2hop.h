#ifndef __ODAS_SYSTEM_HOP2HOP
#define __ODAS_SYSTEM_HOP2HOP

    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    #include "../signal/hop.h"
    #include "../general/link.h"

    typedef struct hop2hop_multiplex_obj {

        unsigned int hopSize;
                
    } hop2hop_multiplex_obj;

    typedef struct hop2hop_buffer_obj {

        unsigned int nSignals;
        unsigned int hopSizeIn;
        unsigned int hopSizeOut;
        float intervalIn;
        float intervalOut;
        float intervalSize;
        unsigned int bufferSize;
        float ratio;
        float delta;

        float iWrite;
        float iRead;

        float ** array;

    } hop2hop_buffer_obj;

    typedef struct hop2hop_gain_obj {

        unsigned int hopSize;
        float gain;

    } hop2hop_gain_obj;

    hop2hop_multiplex_obj * hop2hop_multiplex_construct_zero(const unsigned int hopSize);

    void hop2hop_multiplex_destroy(hop2hop_multiplex_obj * obj);

    void hop2hop_multiplex_process(hop2hop_multiplex_obj * obj, const links_obj * links, const hops_obj * src, hops_obj * dest);    

    hop2hop_buffer_obj * hop2hop_buffer_construct_zero(const unsigned int nSignals, const unsigned int hopSizeIn, const unsigned int hopSizeOut, const float ratio);

    void hop2hop_buffer_destroy(hop2hop_buffer_obj * obj);

    void hop2hop_buffer_push(hop2hop_buffer_obj * obj, const hops_obj * hops);

    void hop2hop_buffer_pop(hop2hop_buffer_obj * obj, hops_obj * hops);

    char hop2hop_buffer_isFull(hop2hop_buffer_obj * obj);

    char hop2hop_buffer_isEmpty(hop2hop_buffer_obj * obj);

    hop2hop_gain_obj * hop2hop_gain_construct_zero(const unsigned int hopSize, const float gain);

    void hop2hop_gain_destroy(hop2hop_gain_obj * obj);

    void hop2hop_gain_process(hop2hop_gain_obj * obj, const hops_obj * src, hops_obj * dest);

#endif