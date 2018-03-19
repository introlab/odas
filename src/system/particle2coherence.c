
   /**
    * \file     particle2coherence.c
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
    
    #include <system/particle2coherence.h>

    particle2coherence_obj * particle2coherence_construct(const float sigmaR) {

        particle2coherence_obj * obj;

        obj = (particle2coherence_obj *) malloc(sizeof(particle2coherence_obj));

        obj->sigmaR = sigmaR;
        obj->expScale = 1.0f / (sigmaR*sigmaR*sigmaR * powf(2*M_PI,(3.0f/2.0f)));
        obj->expFactor = -1.0f / (2.0f * sigmaR * sigmaR);

        return obj;

    }

    void particle2coherence_destroy(particle2coherence_obj * obj) {

        free((void *) obj);

    }

    void particle2coherence_process(particle2coherence_obj * obj, const particles_obj * particles, const pots_obj * pots, const unsigned int iTrack, coherences_obj * coherences) {

        unsigned int iPot;
        unsigned int iParticle;

        float total;
        float x1, y1, z1;
        float x2, y2, z2, w2;
        float dx, dy, dz;
        float scale, factor;
        float expr;        

        scale = obj->expScale;
        factor = obj->expFactor;

        for (iPot = 0; iPot < pots->nPots; iPot++) {

            x1 = pots->array[iPot * 4 + 0];
            y1 = pots->array[iPot * 4 + 1];
            z1 = pots->array[iPot * 4 + 2];

            total = 0.0f;

            for (iParticle = 0; iParticle < particles->nParticles; iParticle++) {
                 
                x2 = particles->array[iParticle * 7 + 0];
                y2 = particles->array[iParticle * 7 + 1];
                z2 = particles->array[iParticle * 7 + 2];
                w2 = particles->array[iParticle * 7 + 6];

                dx = x1 - x2;
                dy = y1 - y2;
                dz = z1 - z2;

                total += w2 * expf(factor * (dx*dx + dy*dy + dz*dz));

            }

            total *= scale;

            coherences->array[iTrack * coherences->nPots + iPot] = total;

        }

    }
