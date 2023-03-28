#ifndef __ODAS_SYSTEM_PARTICLE2COHERENCE
#define __ODAS_SYSTEM_PARTICLE2COHERENCE

   /**
    * \file     particle2coherence.h
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

    #include <utils/gaussian.h>
    #include <signal/particle.h>
    #include <signal/coherence.h>
    #include <signal/pot.h>

    typedef struct particle2coherence_obj {

        float sigmaR;
        float expScale;
        float expFactor;

    } particle2coherence_obj;

    particle2coherence_obj * particle2coherence_construct(const float sigmaR);

    void particle2coherence_destroy(particle2coherence_obj * obj);

    void particle2coherence_process(particle2coherence_obj * obj, const particles_obj * particles, const pots_obj * pots, const unsigned int iTrack, coherences_obj * coherences);

#endif
