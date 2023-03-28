   
   /**
    * \file     particle.c
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
    
    #include <signal/particle.h>
    
    particles_obj * particles_construct_zero(const unsigned int nParticles) {

        particles_obj * obj;

        obj = (particles_obj *) malloc(sizeof(particles_obj));

        obj->nParticles = nParticles;

        obj->array = (float *) malloc(sizeof(float) * 7 * nParticles);
        memset(obj->array, 0x00, sizeof(float) * 7 * nParticles);

        obj->state = (unsigned char *) malloc(sizeof(unsigned char) * nParticles);
        memset(obj->state, 0x00, sizeof(unsigned char) * nParticles);

        return obj;

    }

    void particles_destroy(particles_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->state);
        free((void *) obj);

    }

    void particles_printf(const particles_obj * obj) {

        unsigned int iParticle;

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            printf("(%04u): x = (%+1.3f,%+1.3f,%+1.3f), v = (%+1.3f,%+1.3f,%+1.3f), w = %1.5f, s = %u\n",
                   iParticle,
                   obj->array[iParticle * 7 + 0],
                   obj->array[iParticle * 7 + 1],
                   obj->array[iParticle * 7 + 2],
                   obj->array[iParticle * 7 + 3],
                   obj->array[iParticle * 7 + 4],
                   obj->array[iParticle * 7 + 5],
                   obj->array[iParticle * 7 + 6],
                   obj->state[iParticle]);

        }

    }
