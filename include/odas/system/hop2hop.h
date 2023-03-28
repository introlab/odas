#ifndef __ODAS_SYSTEM_HOP2HOP
#define __ODAS_SYSTEM_HOP2HOP

   /**
    * \file     hop2hop.h
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
    #include <string.h>
    #include <math.h>

    #include <signal/hop.h>
    #include <general/link.h>

    typedef struct hop2hop_multiplex_obj {

        unsigned int hopSize;

    } hop2hop_multiplex_obj;

    typedef struct hop2hop_buffer_obj {

        unsigned int nSignals;
        unsigned int hopSizeIn;
        unsigned int hopSizeOut;
        double intervalIn;
        double intervalOut;
        double intervalSize;
        unsigned int bufferSize;
        double ratio;
        double delta;

        double iWrite;
        double iRead;

        float ** array;

    } hop2hop_buffer_obj;

    typedef struct hop2hop_gain_obj {

        unsigned int hopSize;
        float gain;

    } hop2hop_gain_obj;

    hop2hop_multiplex_obj * hop2hop_multiplex_construct_zero(const unsigned int hopSize);

    void hop2hop_multiplex_destroy(hop2hop_multiplex_obj * obj);

    void hop2hop_multiplex_process(hop2hop_multiplex_obj * obj, const links_obj * links, const hops_obj * src, hops_obj * dest);

    hop2hop_buffer_obj * hop2hop_buffer_construct_zero(const unsigned int nSignals, const unsigned int hopSizeIn, const unsigned int hopSizeOut, const double ratio);

    void hop2hop_buffer_destroy(hop2hop_buffer_obj * obj);

    void hop2hop_buffer_push(hop2hop_buffer_obj * obj, const hops_obj * hops);

    void hop2hop_buffer_pop(hop2hop_buffer_obj * obj, hops_obj * hops);

    char hop2hop_buffer_isFull(hop2hop_buffer_obj * obj);

    char hop2hop_buffer_isEmpty(hop2hop_buffer_obj * obj);

    hop2hop_gain_obj * hop2hop_gain_construct_zero(const unsigned int hopSize, const float gain);

    void hop2hop_gain_destroy(hop2hop_gain_obj * obj);

    void hop2hop_gain_process(hop2hop_gain_obj * obj, const hops_obj * src, hops_obj * dest);

#endif
