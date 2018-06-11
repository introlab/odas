   
   /**
    * \file     gaussian.c
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
    
    #include <utils/gaussian.h>

    gaussian_1d_obj * gaussian_1d_construct_zero(void) {

        gaussian_1d_obj * obj;

        obj = (gaussian_1d_obj *) malloc(sizeof(gaussian_1d_obj));

        obj->weight = 1.0f;
        obj->mu_x = 0.0f;
        obj->sigma_x = 1.0f;
        obj->scaleFactor = (obj->weight / (obj->sigma_x * powf(2*M_PI,(1.0f/2.0f))));

        return obj;

    }

    gaussian_2d_obj * gaussian_2d_construct_zero(void) {

        gaussian_2d_obj * obj;

        obj = (gaussian_2d_obj *) malloc(sizeof(gaussian_2d_obj));

        obj->weight = 1.0f;
        obj->mu_x = 0.0f;
        obj->mu_y = 0.0f;
        obj->sigma_x = 1.0f;
        obj->sigma_y = 1.0f;
        obj->scaleFactor = (obj->weight / (obj->sigma_x*obj->sigma_y * powf(2*M_PI,(2.0f/2.0f))));

        return obj;

    }

    gaussian_3d_obj * gaussian_3d_construct_zero(void) {

        gaussian_3d_obj * obj;

        obj = (gaussian_3d_obj *) malloc(sizeof(gaussian_3d_obj));

        obj->weight = 1.0f;
        obj->mu_x = 0.0f;
        obj->mu_y = 0.0f;
        obj->mu_z = 0.0f;
        obj->sigma_x = 1.0f;
        obj->sigma_y = 1.0f;
        obj->sigma_z = 1.0f;
        obj->scaleFactor = (obj->weight / (obj->sigma_x*obj->sigma_y*obj->sigma_z * powf(2*M_PI,(3.0f/2.0f))));

        return obj;

    }

    gaussian_1d_obj * gaussian_1d_construct_weightmusigma(const float weight, const float mu_x, const float sigma_x) {

        gaussian_1d_obj * obj;

        obj = (gaussian_1d_obj *) malloc(sizeof(gaussian_1d_obj));

        obj->weight = weight;
        obj->mu_x = mu_x;
        obj->sigma_x = sigma_x;
        obj->scaleFactor = (obj->weight / (obj->sigma_x * powf(2*M_PI,(1.0f/2.0f))));

        return obj;        

    }

    gaussian_2d_obj * gaussian_2d_construct_weigthmusigma(const float weight, const float mu_x, const float mu_y, const float sigma_x, const float sigma_y) {

        gaussian_2d_obj * obj;

        obj = (gaussian_2d_obj *) malloc(sizeof(gaussian_2d_obj));

        obj->weight = weight;
        obj->mu_x = mu_x;
        obj->mu_y = mu_y;
        obj->sigma_x = sigma_x;
        obj->sigma_y = sigma_y;
        obj->scaleFactor = (obj->weight / (obj->sigma_x*obj->sigma_y * powf(2*M_PI,(2.0f/2.0f))));

        return obj;

    }

    gaussian_3d_obj * gaussian_3d_construct_weightmusigma(const float weight, const float mu_x, const float mu_y, const float mu_z, const float sigma_x, const float sigma_y, const float sigma_z) {

        gaussian_3d_obj * obj;

        obj = (gaussian_3d_obj *) malloc(sizeof(gaussian_3d_obj));

        obj->weight = weight;
        obj->mu_x = mu_x;
        obj->mu_y = mu_y;
        obj->mu_z = mu_z;
        obj->sigma_x = sigma_x;
        obj->sigma_y = sigma_y;
        obj->sigma_z = sigma_z;
        obj->scaleFactor = (obj->weight / (obj->sigma_x*obj->sigma_y*obj->sigma_z * powf(2*M_PI,(3.0f/2.0f))));

        return obj;

    }

    gaussian_1d_obj * gaussian_1d_construct_gaussian(const gaussian_1d_obj * gaussian) {

        gaussian_1d_obj * obj;

        obj = (gaussian_1d_obj *) malloc(sizeof(gaussian_1d_obj));

        obj->weight = gaussian->weight;
        obj->mu_x = gaussian->mu_x;
        obj->sigma_x = gaussian->sigma_x;
        obj->scaleFactor = (obj->weight / (obj->sigma_x * powf(2*M_PI,(1.0f/2.0f))));

        return obj;     

    }

    gaussian_2d_obj * gaussian_2d_construct_gaussian(const gaussian_2d_obj * gaussian) {

        gaussian_2d_obj * obj;

        obj = (gaussian_2d_obj *) malloc(sizeof(gaussian_2d_obj));

        obj->weight = gaussian->weight;
        obj->mu_x = gaussian->mu_x;
        obj->mu_y = gaussian->mu_y;
        obj->sigma_x = gaussian->sigma_x;
        obj->sigma_y = gaussian->sigma_y;
        obj->scaleFactor = (obj->weight / (obj->sigma_x*obj->sigma_y * powf(2*M_PI,(2.0f/2.0f))));

        return obj;

    }

    gaussian_3d_obj * gaussian_3d_construct_gaussian(const gaussian_3d_obj * gaussian) {

        gaussian_3d_obj * obj;

        obj = (gaussian_3d_obj *) malloc(sizeof(gaussian_3d_obj));

        obj->weight = gaussian->weight;
        obj->mu_x = gaussian->mu_x;
        obj->mu_y = gaussian->mu_y;
        obj->mu_z = gaussian->mu_z;
        obj->sigma_x = gaussian->sigma_x;
        obj->sigma_y = gaussian->sigma_y;
        obj->sigma_z = gaussian->sigma_z;
        obj->scaleFactor = (obj->weight / (obj->sigma_x*obj->sigma_y*obj->sigma_z * powf(2*M_PI,(3.0f/2.0f))));

        return obj;

    }

    void gaussian_1d_destroy(gaussian_1d_obj * obj) {

        free((void *) obj);

    }
    
    void gaussian_2d_destroy(gaussian_2d_obj * obj) {

        free((void *) obj);

    }
    
    void gaussian_3d_destroy(gaussian_3d_obj * obj) {

        free((void *) obj);

    }

    float gaussian_1d_eval(const gaussian_1d_obj * obj, const float x) {

        float value;
        float diff_x;
        float diff2_x;
        float sigma_x;
        float sigma2_x;
        float expr;

        diff_x = x - obj->mu_x;
        diff2_x = diff_x * diff_x;

        sigma_x = obj->sigma_x;
        sigma2_x = sigma_x * sigma_x;

        expr = -0.5f * (diff2_x/sigma2_x);

        value = obj->scaleFactor * expf(expr);

        return value;        

    }

    float gaussian_2d_eval(const gaussian_2d_obj * obj, const float x, const float y) {

        float value;
        float diff_x, diff_y;
        float diff2_x, diff2_y;
        float sigma_x, sigma_y;
        float sigma2_x, sigma2_y;
        float expr;

        diff_x = x - obj->mu_x;
        diff_y = y - obj->mu_y;
        diff2_x = diff_x * diff_x;
        diff2_y = diff_y * diff_y;
        sigma_x = obj->sigma_x;
        sigma_y = obj->sigma_y;
        sigma2_x = sigma_x * sigma_x;
        sigma2_y = sigma_y * sigma_y;

        expr = -0.5f * ((diff2_x/sigma2_x)+(diff2_y/sigma2_y));

        value = obj->scaleFactor * expf(expr);

        return value; 

    }

    float gaussian_3d_eval(const gaussian_3d_obj * obj, const float x, const float y, const float z) {

        float value;
        float diff_x, diff_y, diff_z;
        float diff2_x, diff2_y, diff2_z;
        float sigma_x, sigma_y, sigma_z;
        float sigma2_x, sigma2_y, sigma2_z;
        float expr;

        diff_x = x - obj->mu_x;
        diff_y = y - obj->mu_y;
        diff_z = z - obj->mu_z;
        diff2_x = diff_x * diff_x;
        diff2_y = diff_y * diff_y;
        diff2_z = diff_z * diff_z;     
        sigma_x = obj->sigma_x;
        sigma_y = obj->sigma_y;
        sigma_z = obj->sigma_z;
        sigma2_x = sigma_x * sigma_x;
        sigma2_y = sigma_y * sigma_y;
        sigma2_z = sigma_z * sigma_z;

        expr = -0.5f * ((diff2_x/sigma2_x)+(diff2_y/sigma2_y)+(diff2_z/sigma2_z));

        value = obj->scaleFactor * expf(expr);

        return value; 

    }

    void gaussian_1d_printf(const gaussian_1d_obj * obj) {

        printf("weight = %+1.3f, mu = %+1.3f, sigma = %+1.3f\n",obj->weight, obj->mu_x,obj->sigma_x);

    }

    void gaussian_2d_printf(const gaussian_2d_obj * obj) {

        printf("weight = %+1.3f, mu = (%+1.3f,%+1.3f), sigma = (%+1.3f,%+1.3f)\n",obj->weight, obj->mu_x,obj->mu_y,obj->sigma_x,obj->sigma_y);

    }

    void gaussian_3d_printf(const gaussian_3d_obj * obj) {

        printf("weight = %+1.3f, mu = (%+1.3f,%+1.3f,%+1.3f), sigma = (%+1.3f,%+1.3f,%+1.3f)\n",obj->weight, obj->mu_x,obj->mu_y,obj->mu_z,obj->sigma_x,obj->sigma_y,obj->sigma_z);

    }

    gaussians_1d_obj * gaussians_1d_construct_null(const unsigned int nSignals) {

        gaussians_1d_obj * obj;
        unsigned int iSignal;

        obj = (gaussians_1d_obj *) malloc(sizeof(gaussians_1d_obj));

        obj->nSignals = nSignals;
        obj->array = (gaussian_1d_obj **) malloc(sizeof(gaussian_1d_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    gaussians_2d_obj * gaussians_2d_construct_null(const unsigned int nSignals) {

        gaussians_2d_obj * obj;
        unsigned int iSignal;

        obj = (gaussians_2d_obj *) malloc(sizeof(gaussians_2d_obj));

        obj->nSignals = nSignals;
        obj->array = (gaussian_2d_obj **) malloc(sizeof(gaussian_2d_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    gaussians_3d_obj * gaussians_3d_construct_null(const unsigned int nSignals) {

        gaussians_3d_obj * obj;
        unsigned int iSignal;

        obj = (gaussians_3d_obj *) malloc(sizeof(gaussians_3d_obj));

        obj->nSignals = nSignals;
        obj->array = (gaussian_3d_obj **) malloc(sizeof(gaussian_3d_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    gaussians_1d_obj * gaussians_1d_construct_gaussians(const gaussians_1d_obj * gaussians) {

        gaussians_1d_obj * obj;
        unsigned int iSignal;

        obj = (gaussians_1d_obj *) malloc(sizeof(gaussians_1d_obj));

        obj->nSignals = gaussians->nSignals;
        obj->array = (gaussian_1d_obj **) malloc(sizeof(gaussian_1d_obj *) * gaussians->nSignals);

        for (iSignal = 0; iSignal < gaussians->nSignals; iSignal++) {
            obj->array[iSignal] = gaussian_1d_construct_gaussian(gaussians->array[iSignal]);
        }

        return obj;

    }

    gaussians_2d_obj * gaussians_2d_construct_gaussians(const gaussians_2d_obj * gaussians) {

        gaussians_2d_obj * obj;
        unsigned int iSignal;

        obj = (gaussians_2d_obj *) malloc(sizeof(gaussians_2d_obj));

        obj->nSignals = gaussians->nSignals;
        obj->array = (gaussian_2d_obj **) malloc(sizeof(gaussian_2d_obj *) * gaussians->nSignals);

        for (iSignal = 0; iSignal < gaussians->nSignals; iSignal++) {
            obj->array[iSignal] = gaussian_2d_construct_gaussian(gaussians->array[iSignal]);
        }

        return obj;

    }

    gaussians_3d_obj * gaussians_3d_construct_gaussians(const gaussians_3d_obj * gaussians) {

        gaussians_3d_obj * obj;
        unsigned int iSignal;

        obj = (gaussians_3d_obj *) malloc(sizeof(gaussians_3d_obj));

        obj->nSignals = gaussians->nSignals;
        obj->array = (gaussian_3d_obj **) malloc(sizeof(gaussian_3d_obj *) * gaussians->nSignals);

        for (iSignal = 0; iSignal < gaussians->nSignals; iSignal++) {
            obj->array[iSignal] = gaussian_3d_construct_gaussian(gaussians->array[iSignal]);
        }

        return obj;

    }

    void gaussians_1d_destroy(gaussians_1d_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            if (obj->array[iSignal] != NULL) {
                gaussian_1d_destroy(obj->array[iSignal]);
            }

        }

        free((void *) obj->array);

        free((void *) obj);

    }

    void gaussians_2d_destroy(gaussians_2d_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            if (obj->array[iSignal] != NULL) {
                gaussian_2d_destroy(obj->array[iSignal]);
            }

        }

        free((void *) obj->array);

        free((void *) obj);

    }

    void gaussians_3d_destroy(gaussians_3d_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            if (obj->array[iSignal] != NULL) {
                gaussian_3d_destroy(obj->array[iSignal]);
            }

        }

        free((void *) obj->array);

        free((void *) obj);

    }

    float gaussians_1d_eval(const gaussians_1d_obj * obj, const float x) {

        unsigned int iSignal;
        float value;

        value = 0.0f;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            value += gaussian_1d_eval(obj->array[iSignal], x);

        }

        return value;

    }

    float gaussians_2d_eval(const gaussians_2d_obj * obj, const float x, const float y) {

        unsigned int iSignal;
        float value;

        value = 0.0f;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            value += gaussian_2d_eval(obj->array[iSignal], x, y);

        }

        return value;

    }

    float gaussians_3d_eval(const gaussians_3d_obj * obj, const float x, const float y, const float z) {

        unsigned int iSignal;
        float value;

        value = 0.0f;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            value += gaussian_3d_eval(obj->array[iSignal], x, y, z);

        }

        return value;

    }

    void gaussians_1d_printf(const gaussians_1d_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%03u): ",iSignal);

            if (obj->array[iSignal] != NULL) {
                
                printf("weight = %+1.3f, mu = %+1.3f, sigma = %+1.3f",obj->array[iSignal]->weight, obj->array[iSignal]->mu_x,obj->array[iSignal]->sigma_x);

            }
            else {
                
                printf("(null)");

            }
                    
            printf("\n");

        }

    }

    void gaussians_2d_printf(const gaussians_2d_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%03u): ",iSignal);

            if (obj->array[iSignal] != NULL) {
                
                printf("weight = %+1.3f, mu = (%+1.3f,%+1.3f), sigma = (%+1.3f,%+1.3f)",obj->array[iSignal]->weight, obj->array[iSignal]->mu_x,obj->array[iSignal]->mu_y,obj->array[iSignal]->sigma_x,obj->array[iSignal]->sigma_y);

            }
            else {
                
                printf("(null)");

            }
                    
            printf("\n");

        }

    }

    void gaussians_3d_printf(const gaussians_3d_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%03u): ",iSignal);

            if (obj->array[iSignal] != NULL) {
                
                printf("weight = %+1.3f, mu = (%+1.3f,%+1.3f,%+1.3f), sigma = (%+1.3f,%+1.3f,%+1.3f)",obj->array[iSignal]->weight, obj->array[iSignal]->mu_x,obj->array[iSignal]->mu_y,obj->array[iSignal]->mu_z,obj->array[iSignal]->sigma_x,obj->array[iSignal]->sigma_y,obj->array[iSignal]->sigma_z);

            }
            else {
                
                printf("(null)");

            }
                    
            printf("\n");

        }

    }
