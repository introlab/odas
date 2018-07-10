#ifndef __ODAS_SYSTEM_PARTICLE2COHERENCE
#define __ODAS_SYSTEM_PARTICLE2COHERENCE

     /**
    * \file     particle2coherence.h
    * \author   Francois Grondin <fgrondin@mit.edu>
    * \version  3.0
    * \date     2018-07-02
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
