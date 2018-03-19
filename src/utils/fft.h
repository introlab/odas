#ifndef __ODAS_UTILS_FFT
#define __ODAS_UTILS_FFT

   /**
    * \file     cmatrix.h
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