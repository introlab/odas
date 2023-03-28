   
   /**
    * \file     random.c
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
    
    #include <utils/random.h>

    random_obj * random_construct_zero(const unsigned int N) {

        random_obj * obj;
        unsigned int n;
        time_t t;

        obj = (random_obj *) malloc(sizeof(random_obj));

        obj->N = N;
        obj->pdf = (float *) malloc(sizeof(float) * N);
        obj->cdf = (float *) malloc(sizeof(float) * (N+1));

        for (n = 0; n < N; n++) {
        	obj->pdf[n] = 0.0f;
        	obj->cdf[n] = 0.0f;
        }

        obj->I = (unsigned int) floorf(logf(N)/logf(2.0f)) + 1;

        srand((unsigned) time(&t));

        return obj;

    }

    void random_destroy(random_obj * obj) {

        free((void *) obj->pdf);
        free((void *) obj->cdf);
        free((void *) obj);

    }

    void random_pdf(random_obj * obj, const float * pdf) {

        unsigned int n;
        float cdfTotal;

        cdfTotal = 0.0f;

        for (n = 0; n < obj->N; n++) {

            obj->pdf[n] = pdf[n];
            obj->cdf[n] = cdfTotal;
            cdfTotal += pdf[n];            
            
        }
        
        obj->cdf[obj->N] = cdfTotal;

    }

    void random_generate(const random_obj * obj, const unsigned int nSamples, unsigned int * indexes) {

         unsigned int iSample;
         float rndNumber;
         
         unsigned int indexLow;
         unsigned int indexHigh;
         unsigned int indexMiddle;
         unsigned int i;

         for (iSample = 0; iSample < nSamples; iSample++) {

             rndNumber = (float) ((double)rand() / (double)RAND_MAX);

             indexLow = 0;
             indexHigh = obj->N;

             for (i = 0; i < obj->I; i++) {

                 indexMiddle = (indexLow + indexHigh) / 2;

                 if (obj->cdf[indexMiddle] <= rndNumber) {

                     indexLow = indexMiddle;

                 }
                 else {

                     indexHigh = indexMiddle;

                 }

             }

          	indexes[iSample] = indexLow;

         }

    }

    normal_obj * normal_construct_zero(const double epsilon) {

        normal_obj * obj;
        time_t t;

        obj = (normal_obj *) malloc(sizeof(normal_obj));

        obj->epsilon = epsilon;

        srand((unsigned) time(&t));

        return obj;

    }

    void normal_destroy(normal_obj * obj) {

        free((void *) obj);

    }

    void normal_generate(const normal_obj * obj, const unsigned int nSamples, float * values) {

        unsigned int iSample;
        double u1, u2;
        double z0, z1;
        
        for (iSample = 0; iSample < nSamples; iSample+=2) {

            do {

                u1 = ((double)rand() / (double)RAND_MAX);
                u2 = ((double)rand() / (double)RAND_MAX);

            } while (u1 <= obj->epsilon);

            z0 = sqrt(-2.0 * log(u1)) * cos(2.0*M_PI*u2);
            values[iSample] = (float) z0;

            if ((iSample+1) < nSamples) {
                z1 = sqrt(-2.0 * log(u1)) * sin(2.0*M_PI*u2);	
                values[iSample+1] = (float) z1;
            }
            
        }

    }

    normaloff_obj * normaloff_construct_rnd(const double epsilon, const unsigned int N) {

        normaloff_obj * obj;
        normal_obj * normal;
        unsigned int n;
        time_t t;

        obj = (normaloff_obj *) malloc(sizeof(normaloff_obj));

        obj->N = N;

        obj->values = (float *) malloc(sizeof(float) * N);

        normal = normal_construct_zero(epsilon);
        normal_generate(normal, N, obj->values);
        normal_destroy(normal);

        srand((unsigned) time(&t));

        return obj;

    }

    void normaloff_destroy(normaloff_obj * obj) {

        free((void *) obj->values);
        free((void *) obj);

    }

    void normaloff_generate(const normaloff_obj * obj, const unsigned int nSamples, float * values) {

        unsigned int iSample;
        unsigned int index;

        for (iSample = 0; iSample < nSamples; iSample++) {

            index = rand() % (obj->N);
            values[iSample] = obj->values[index];

        }

    }
