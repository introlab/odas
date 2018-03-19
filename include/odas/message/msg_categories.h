#ifndef __ODAS_MESSAGE_CATEGORIES
#define __ODAS_MESSAGE_CATEGORIES

   /**
    * \file     msg_categories.h
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

    #include <stdlib.h>
    #include <signal/category.h>

    typedef struct msg_categories_obj {

        unsigned long long timeStamp;
        unsigned int fS;
        categories_obj * categories;

    } msg_categories_obj;

    typedef struct msg_categories_cfg {

        unsigned int nChannels;
        unsigned int fS;

    } msg_categories_cfg;

    msg_categories_obj * msg_categories_construct(const msg_categories_cfg * msg_categories_config);

    void msg_categories_destroy(msg_categories_obj * obj);

    void msg_categories_copy(msg_categories_obj * dest, const msg_categories_obj * src);

    void msg_categories_zero(msg_categories_obj * obj);

    unsigned int msg_categories_isZero(const msg_categories_obj * obj);

    msg_categories_cfg * msg_categories_cfg_construct(void);

    void msg_categories_cfg_destroy(msg_categories_cfg * msg_categories_config);

    void msg_categories_cfg_printf(const msg_categories_cfg * msg_categories_config);

#endif
