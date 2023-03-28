#ifndef __ODAS_UTILS_FFT
#define __ODAS_UTILS_FFT

   /**
    * \file     cmatrix.h
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

    #include <fftw3.h>
    #include <stdlib.h>

    //! FFT object.
    typedef struct fft_obj {

        unsigned int frameSize;                 ///< Frame size (in samples).
        unsigned int halfFrameSize;             ///< Half frame size (frame size divided by 2 plus 1).
        fftwf_plan R2C;                         ///< FFTW plan for FFT from real to complex.
        fftwf_plan C2R;                         ///< FFTW plan for FFT from complex to real.
        float * realArray;                      ///< Array that holds all real values.
        fftwf_complex * complexArray;           ///< Array that holds all complex values.

    } fft_obj;

    /** Constructor. Initialize all fields to perform FFT.
        \param      size            FFT size (in samples).
        \return                     Pointer to the instantiated object.
    */  
    fft_obj * fft_construct(const unsigned int size);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void fft_destroy(fft_obj * obj);

    /** Perform Fast Fourier Transform (real vector as input, complex vector as output).
        \param      obj             Object used.
        \param      in              Pointer to the real array used for input.
        \param      out             Pointer to the complex array used for output.
    */
    void fft_r2c(fft_obj * obj, const float * in, float * out);

    /** Perform Inverse Fast Fourier Transform (complex vector as input, real vector as output).
        \param      obj             Object used.
        \param      in              Pointer to the complex array used for input.
        \param      out             Pointer to the real array used for output.
    */
    void fft_c2r(fft_obj * obj, const float * in, float * out);

#endif