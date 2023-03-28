
   /**
    * \file     particle2coherence.c
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
