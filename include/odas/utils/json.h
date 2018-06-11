#ifndef __ODAS_UTILS_JSON
#define __ODAS_UTILS_JSON

   /**
    * \file     json.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-06-01
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
    */

    #include <math.h>

    typedef struct json_token {

        int parent;
        int start;
        int end;

    } json_token;

    typedef struct json_tokens {

        json_token * tokens;
        unsigned int nTokens;
        signed int iToken;

    } json_tokens;


    json_tokens * json_tokens_construct(unsigned int nTokens);

    void json_tokens_destroy(json_tokens * obj);

    void json_tokens_clear(json_tokens * obj);

    int json_tokens_parse(json_tokens * obj, const char * string);

    void json_tokens_printf(json_tokens * obj, const char * string);


    void json_tokens_getSection(const json_tokens * obj, const char * string, const unsigned int iToken, char * dest);


    char json_tokens_type(const json_tokens * obj, const char * string, const unsigned int iToken);

    unsigned int json_tokens_count(const json_tokens * obj, const char * string, const unsigned int iToken);


    int json_tokens_getFromObject(const json_tokens * obj, const char * string, const int iToken, const char * key);

    int json_tokens_getFromArray(const json_tokens * obj, const char * string, const int iToken, const unsigned int index);

    int json_tokens_getFromValue(const json_tokens * obj, const char * string, const int iToken);


    void json_tokens_extractString(const json_tokens * obj, const char * string, const int iToken, char * dest);

    void json_tokens_extractFloat(const json_tokens * obj, const char * string, const int iToken, float * dest);

    void json_tokens_extractFloats(const json_tokens * obj, const char * string, const int iToken, float * dest);


    int json_fsm_micro_digit09(const char * string, int offset);

    int json_fsm_micro_digit19(const char * string, int offset);

    int json_fsm_micro_unicode(const char * string, int offset);

    int json_fsm_micro_4hex(const char * string, int offset);

    int json_fsm_micro_space(const char * string, int offset);

    int json_fsm_micro_char(const char * string, int offset, const char special);

    int json_fsm_micro_true(const char * string, int offset);

    int json_fsm_micro_false(const char * string, int offset);

    int json_fsm_micro_null(const char * string, int offset);


    int json_fsm_object(const char * string, int offset, json_tokens * tokens, int parent);

    int json_fsm_array(const char * string, int offset, json_tokens * tokens, int parent);

    int json_fsm_value(const char * string, int offset, json_tokens * tokens, int parent);

    int json_fsm_string(const char * string, int offset, json_tokens * tokens, int parent);

    int json_fsm_number(const char * string, int offset, json_tokens * tokens, int parent);

#endif