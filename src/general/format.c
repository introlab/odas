    
    #include "format.h"

    format_obj * format_construct() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_undefined;

        return obj;

    }

    format_obj * format_construct_bin(const unsigned int nBits) {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        switch(nBits) {

            case 8:

                obj->type = format_bin08;

            break;

            case 16:

                obj->type = format_bin16;

            break;

            case 24:

                obj->type = format_bin24;

            break;

            case 32:

                obj->type = format_bin32;

            break;

            default:

                printf("Wrong number of bits.\n");
                exit(EXIT_FAILURE);

            break;

        }

        return obj;

    }

    format_obj * format_construct_float() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_float;

        return obj;

    }

    format_obj * format_construct_json() {

        format_obj * obj;

        obj = (format_obj *) malloc(sizeof(format_obj));

        obj->type = format_json;

        return obj;

    }

    format_obj * format_clone(const format_obj * obj) {

        format_obj * clone;

        clone = format_construct();

        clone->type = obj->type;

        return clone;

    }

    void format_destroy(format_obj * obj) {

        free((void *) obj);

    }

    void format_printf(const format_obj * obj) {

        if (obj != NULL) {

            switch(obj->type) {

                case format_bin08:
                    printf("type = bin08\n");
                break;

                case format_bin16:
                    printf("type = bin16\n");
                break;

                case format_bin24:
                    printf("type = bin24\n");
                break;

                case format_bin32:
                    printf("type = bin32\n");
                break;

                case format_float:
                    printf("type = float\n");
                break;

                case format_json:
                    printf("type = json\n");
                break;

            }

        }
        else {
            printf("(null)\n");
        }

    }