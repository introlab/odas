#ifndef __ODAS_UTILS_GAUSSIAN
#define __ODAS_UTILS_GAUSSIAN

   /**
    * \file     gaussian.h
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
    #include <stdio.h>
    #include <math.h>

    //! 1-D gaussian
    typedef struct gaussian_1d_obj {

        float weight;                           ///< Weight of the gaussian.
        float mu_x;                             ///< Mean of the gaussian.
        float sigma_x;                          ///< Standard deviation of the gaussian.
        float scaleFactor;                      ///< Precomputed scale factor for the exponential function.

    } gaussian_1d_obj;

    //! 2-D gaussian
    typedef struct gaussian_2d_obj {

        float weight;                           ///< Weight of the gaussian.
        float mu_x;                             ///< X-component of the mean of the gaussian.
        float mu_y;                             ///< Y-component of the mean of the gaussian.
        float sigma_x;                          ///< X-component of the standard deviation of the gaussian.
        float sigma_y;                          ///< Y-component of the standard deviation of the gaussian.
        float scaleFactor;                      ///< Precomputed scale factor for the exponential function.

    } gaussian_2d_obj;

    //! 3-D gaussian
    typedef struct gaussian_3d_obj {

        float weight;                           ///< Weight of the gaussian.
        float mu_x;                             ///< X-component of the mean of the gaussian.
        float mu_y;                             ///< Y-component of the mean of the gaussian.
        float mu_z;                             ///< Z-component of the mean of the gaussian.
        float sigma_x;                          ///< X-component of the standard deviation of the gaussian.
        float sigma_y;                          ///< Y-component of the standard deviation of the gaussian.
        float sigma_z;                          ///< Z-component of the standard deviation of the gaussian.
        float scaleFactor;                      ///< Precomputed scale factor for the exponential function.

    } gaussian_3d_obj;

    //! 1-D gaussian mixture model
    typedef struct gaussians_1d_obj {

        unsigned int nSignals;                  ///< Number of gaussians.
        gaussian_1d_obj ** array;               ///< List of gaussians.

    } gaussians_1d_obj;

    //! 2-D gaussian mixture model
    typedef struct gaussians_2d_obj {

        unsigned int nSignals;                  ///< Number of gaussians.
        gaussian_2d_obj ** array;               ///< List of gaussians.

    } gaussians_2d_obj;

    //! 3-D gaussian mixture model
    typedef struct gaussians_3d_obj {

        unsigned int nSignals;                  ///< Number of gaussians.
        gaussian_3d_obj ** array;               ///< List of gaussians.

    } gaussians_3d_obj;

    /** Constructor. Initialize all fields to zero (weight to 1, mean to 0, standard deviation to 1).
        \return                     Pointer to the instantiated object.
    */  
    gaussian_1d_obj * gaussian_1d_construct_zero(void);

    /** Constructor. Initialize all fields to zero (weight to 1, means to 0, standard deviations to 1).
        \return                     Pointer to the instantiated object.
    */  
    gaussian_2d_obj * gaussian_2d_construct_zero(void);

    /** Constructor. Initialize all fields to zero (weight to 1, means to 0, standard deviations to 1).
        \return                     Pointer to the instantiated object.
    */  
    gaussian_3d_obj * gaussian_3d_construct_zero(void);

    /** Constructor. Initialize all fields to weight, mu and sigma.
        \param      weight          Weight value.
        \param      mu_x            Mean value.
        \param      sigma_x         Standard deviation value.
        \return                     Pointer to the instantiated object.
    */  
    gaussian_1d_obj * gaussian_1d_construct_weightmusigma(const float weight, const float mu_x, const float sigma_x);

    /** Constructor. Initialize all fields to weight, mus and sigmas.
        \param      weight          Weight value.
        \param      mu_x            X-coordinate of the mean.
        \param      mu_y            Y-coordinate of the mean.
        \param      sigma_x         X-coordinate of the standard deviation.
        \param      sigma_y         Y-coordinate of the standard deviation.
        \return                     Pointer to the instantiated object.
    */  
    gaussian_2d_obj * gaussian_2d_construct_weightmusigma(const float weight, const float mu_x, const float mu_y, const float sigma_x, const float sigma_y);

    /** Constructor. Initialize all fields to weight, mus and sigmas.
        \param      weight          Weight value.
        \param      mu_x            X-coordinate of the mean.
        \param      mu_y            Y-coordinate of the mean.
        \param      mu_z            Z-coordinate of the mean.
        \param      sigma_x         X-coordinate of the standard deviation.
        \param      sigma_y         Y-coordinate of the standard deviation.
        \param      sigma_z         Z-coordinate of the standard deviation.
        \return                     Pointer to the instantiated object.
    */  
    gaussian_3d_obj * gaussian_3d_construct_weightmusigma(const float weight, const float mu_x, const float mu_y, const float mu_z, const float sigma_x, const float sigma_y, const float sigma_z);

    /** Constructor. Clone the object.
        \param      gaussian    Object to cloned.
        \return                 Pointer to the instantiated object.
    */  
    gaussian_1d_obj * gaussian_1d_construct_gaussian(const gaussian_1d_obj * gaussian);

    /** Constructor. Clone the object.
        \param      gaussian    Object to cloned.
        \return                 Pointer to the instantiated object.
    */  
    gaussian_2d_obj * gaussian_2d_construct_gaussian(const gaussian_2d_obj * gaussian);

    /** Constructor. Clone the object.
        \param      gaussian    Object to cloned.
        \return                 Pointer to the instantiated object.
    */  
    gaussian_3d_obj * gaussian_3d_construct_gaussian(const gaussian_3d_obj * gaussian);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void gaussian_1d_destroy(gaussian_1d_obj * obj);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */    
    void gaussian_2d_destroy(gaussian_2d_obj * obj);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */    
    void gaussian_3d_destroy(gaussian_3d_obj * obj);

    /** Evaluate the gaussian at x.
        \param      obj         Object to be used.
        \param      x           Value of x.
        \return                 Value of the gaussian.
    */
    float gaussian_1d_eval(const gaussian_1d_obj * obj, const float x);

    /** Evaluate the gaussian at x and y.
        \param      obj         Object to be used.
        \param      x           Value of x.
        \param      y           Value of y.
        \return                 Value of the gaussian.
    */
    float gaussian_2d_eval(const gaussian_2d_obj * obj, const float x, const float y);

    /** Evaluate the gaussian at x, y and z.
        \param      obj         Object to be used.
        \param      x           Value of x.
        \param      y           Value of y.
        \param      z           Value of z.
        \return                 Value of the gaussian.
    */
    float gaussian_3d_eval(const gaussian_3d_obj * obj, const float x, const float y, const float z);

    /** Print the content of the gaussian.
        \param      obj         Object to be used.
    */
    void gaussian_1d_printf(const gaussian_1d_obj * obj);

    /** Print the content of the gaussian.
        \param      obj         Object to be used.
    */
    void gaussian_2d_printf(const gaussian_2d_obj * obj);

    /** Print the content of the gaussian.
        \param      obj         Object to be used.
    */
    void gaussian_3d_printf(const gaussian_3d_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of gaussians.    
        \return                 Pointer to the instantiated object.
    */  
    gaussians_1d_obj * gaussians_1d_construct_null(const unsigned int nSignals);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of gaussians.    
        \return                 Pointer to the instantiated object.
    */  
    gaussians_2d_obj * gaussians_2d_construct_null(const unsigned int nSignals);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of gaussians.    
        \return                 Pointer to the instantiated object.
    */  
    gaussians_3d_obj * gaussians_3d_construct_null(const unsigned int nSignals);

    /** Constructor. Clone the gaussians.
        \param      gaussians   Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    gaussians_1d_obj * gaussians_1d_construct_gaussians(const gaussians_1d_obj * gaussians);

    /** Constructor. Clone the gaussians.
        \param      gaussians   Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    gaussians_2d_obj * gaussians_2d_construct_gaussians(const gaussians_2d_obj * gaussians);

    /** Constructor. Clone the gaussians.
        \param      gaussians   Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    gaussians_3d_obj * gaussians_3d_construct_gaussians(const gaussians_3d_obj * gaussians);   

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void gaussians_1d_destroy(gaussians_1d_obj * obj);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void gaussians_2d_destroy(gaussians_2d_obj * obj);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void gaussians_3d_destroy(gaussians_3d_obj * obj);

    /** Evaluate the gaussian mixture model (GMM) at x.
        \param      obj         Object to be used.
        \param      x           Value of x.
        \return                 Value of the GMM.
    */
    float gaussians_1d_eval(const gaussians_1d_obj * obj, const float x);

    /** Evaluate the gaussian mixture model (GMM) at x and y.
        \param      obj         Object to be used.
        \param      x           Value of x.
        \param      y           Value of y.
        \return                 Value of the GMM.
    */
    float gaussians_2d_eval(const gaussians_2d_obj * obj, const float x, const float y);

    /** Evaluate the gaussian mixture model (GMM) at x, y and z.
        \param      obj         Object to be used.
        \param      x           Value of x.
        \param      y           Value of y.
        \param      z           Value of z.
        \return                 Value of the GMM.
    */
    float gaussians_3d_eval(const gaussians_3d_obj * obj, const float x, const float y, const float z);

    /** Print the content of the gaussian mixture model (GMM).
        \param      obj         Object to be used.
    */
    void gaussians_1d_printf(const gaussians_1d_obj * obj);

    /** Print the content of the gaussian mixture model (GMM).
        \param      obj         Object to be used.
    */
    void gaussians_2d_printf(const gaussians_2d_obj * obj);

    /** Print the content of the gaussian mixture model (GMM).
        \param      obj         Object to be used.
    */
    void gaussians_3d_printf(const gaussians_3d_obj * obj);

#endif