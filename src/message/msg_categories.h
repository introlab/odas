#ifndef __ODAS_MESSAGE_CATEGORIES
#define __ODAS_MESSAGE_CATEGORIES

    #include <stdlib.h>
    #include "../signal/category.h"

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