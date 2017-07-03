#ifndef __ODAS_UTILS_RANDOM
#define __ODAS_UTILS_RANDOM
   
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <math.h>

    //! Random number generator
    typedef struct random_obj {

        unsigned int N;                         ///< Number of elements in the space
        unsigned int I;                         ///< Number of iterations to perform a binary search
        float * pdf;                            ///< Probability density function (probability mass function)
        float * cdf;                            ///< Cumulative density function

    } random_obj;

    //! Standard normal number generator
    typedef struct normal_obj {

        double epsilon;                         ///< Small value to perform the Box-Muller transform.

    } normal_obj;

    //! Standard normal number generator offline
    typedef struct normaloff_obj {

        unsigned int N;                         ///< Number of samples.
        float * values;                         ///< Normally distributed samples.

    } normaloff_obj;

    /** Constructor. Initialize all elements to zero.
        \param      N               Number of elements in the space.
        \return                     Pointer to the instantiated object.
    */  
    random_obj * random_construct_zero(const unsigned int N);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void random_destroy(random_obj * obj);

    /** Set the PDF.
        \param      pdf             Array that contains the PDF values.
        \param      obj             Object to be modified.
    */
    void random_pdf(random_obj * obj, const float * pdf);

    /** Pick element randomly according to the PDF, and return the index.
        \param      nSamples        Number of elements to pick.
        \param      indexes         Array that contains the returned indexes.
        \param      obj             Object to be used.
    */
    void random_generate(const random_obj * obj, const unsigned int nSamples, unsigned int * indexes);

    /** Constructor.
        \param      epsilon         Small value to perform the Box-Muller transform.
        \return                     Pointer of the instantiated object.
    */
    normal_obj * normal_construct_zero(const double epsilon);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void normal_destroy(normal_obj * obj);

    /** Generate a random number according to a standard normal distribution.
        \param      nSamples        Number of random numbers to generate.
        \param      values          Array that contains the generated random numbers.
        \param      obj             Object to be used.
    */
    void normal_generate(const normal_obj * obj, const unsigned int nSamples, float * values);

    /** Constructor.
        \param      epsilon         Small value to perform the Box-Muller transform.
        \param      N               Number of random numbers generated offline and stored.
        \return                     Pointer of the instantiated object.
    */
    normaloff_obj * normaloff_construct_rnd(const double epsilon, const unsigned int N);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void normaloff_destroy(normaloff_obj * obj);

    /** Generate a random number according to a standard normal distribution.
        \param      nSamples        Number of random numbers to generate.
        \param      values          Array that contains the generated random numbers.
        \param      obj             Object to be used.
    */
    void normaloff_generate(const normaloff_obj * obj, const unsigned int nSamples, float * values);


#endif