#ifndef __ODAS_GENERAL_SOUNDSPEED
#define __ODAS_GENERAL_SOUNDSPEED

    /**
    * \file     soundspeed.h
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

    #include <stdlib.h>
    #include <stdio.h>

    typedef struct soundspeed_obj {

        float mu;
        float sigma2;

    } soundspeed_obj;

    soundspeed_obj * soundspeed_construct_zero(void);

    soundspeed_obj * soundspeed_clone(const soundspeed_obj * obj);

    void soundspeed_destroy(soundspeed_obj * obj);

    void soundspeed_printf(const soundspeed_obj * obj);

#endif