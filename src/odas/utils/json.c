   
    /**
    * \file     json.c
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
    
    #include <utils/json.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    
    json_tokens * json_tokens_construct(unsigned int nTokens) {

        json_tokens * obj;

        obj = (json_tokens *) malloc(sizeof(json_tokens));

        obj->tokens = (json_token *) malloc(sizeof(json_token) * nTokens);
        memset(obj->tokens, 0x00, sizeof(json_token) * nTokens);

        obj->nTokens = nTokens;
        obj->iToken = -1;

        return obj;

    }

    void json_tokens_destroy(json_tokens * obj) {

        free((void *) obj->tokens);
        free((void *) obj);

    }

    void json_tokens_clear(json_tokens * obj) {

        memset(obj->tokens, 0x00, sizeof(json_token) * obj->nTokens);
        obj->iToken = -1;      

    }    

    int json_tokens_parse(json_tokens * obj, const char * string) {

        return json_fsm_object(string, 0, obj, -1);

    }

    void json_tokens_printf(json_tokens * obj, const char * string) {

        signed int iToken;
        int parent;
        int start;
        int end;
        char type;

        for (iToken = 0; iToken < obj->iToken; iToken++) {

            // Extract properties of this token and print
            parent = obj->tokens[iToken].parent;
            start = obj->tokens[iToken].start;
            end = obj->tokens[iToken].end;
            type = json_tokens_type(obj, string, iToken);
            
            printf("(%05u) %d: %d - %d: %c\n", iToken, parent, start, end, type);

        }

        if (obj->iToken < (obj->nTokens - 1)) {

            printf("(%05u) %d: %d - %d: %c\n", obj->iToken + 1, -1, -1, -1, '?');
            printf("...\n");
            printf("(%05u) %d: %d - %d: %c\n", obj->nTokens - 1, -1, -1, -1, '?');

        }               

    }

    void json_tokens_getSection(const json_tokens * obj, const char * string, const unsigned int iToken, char * dest) {

        unsigned int start;
        unsigned int len;

        start = obj->tokens[iToken].start;
        len = obj->tokens[iToken].end-obj->tokens[iToken].start;

        memcpy(dest, &(string[start]), sizeof(char) * len);
        dest[len] = 0x00;        

    }

    char json_tokens_type(const json_tokens * obj, const char * string, const unsigned int iToken) {

        char type = 0x00;

        if (obj->iToken < (obj->nTokens - 1)) {

            // If the current token points to the same place as the next one,
            // then it has to be a value that hold either an object, array,
            // string or number.
            if (obj->tokens[iToken].start == obj->tokens[iToken+1].start) {

                type = 'V';

            }

        }

        if (type != 'V') {

            // Otherwise the character pointed to will tell us what it is
            switch (string[obj->tokens[iToken].start]) {

                // All objects start with {
                case '{':
                    type = 'O';
                    break;

                // All arrays start with [
                case '[':
                    type = 'A';
                    break;

                // All strings start with "
                case '"':
                    type = 'S';
                    break;

                // All numbers start with minus sign or digits 0-9
                case '-':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    type = 'N';
                    break;

                // All values, if not holding another component (this is handled above)
                // will be either true, false or null expressions
                case 't':
                case 'f':
                case 'n':
                    type = 'V';
                    break;

            }

        }

        return type;

    }

    unsigned int json_tokens_count(const json_tokens * obj, const char * string, const unsigned int iToken) {

        unsigned int iToken2;
        unsigned int count;

        count = 0;

        // Loop only in filled tokens
        for (iToken2 = 0; iToken2 <= obj->iToken; iToken2++) {

            // If this token is part of the array or object, and is a value
            if ((obj->tokens[iToken2].parent == iToken) && (json_tokens_type(obj, string, iToken2) == 'V')) {
                
                count++;

            }

        }

        return count;        

    }

    int json_tokens_getFromObject(const json_tokens * obj, const char * string, const int iToken, const char * key) {

        unsigned int iToken2;
        unsigned int len;
        unsigned int iSample;
        char isEqual;
        int ptr = -1;

        // Loop only in filled tokens
        for (iToken2 = 0; iToken2 <= obj->iToken; iToken2++) {

            // If token belongs to this object...
            if (obj->tokens[iToken2].parent == iToken) {

                // ... and is a string
                if (json_tokens_type(obj, string, iToken2) == 'S') {

                    // Do not include quotes
                    len = (unsigned int) (obj->tokens[iToken2].end - obj->tokens[iToken2].start) - 2;

                    isEqual = 0x01;

                    for (iSample = 0; iSample < len; iSample++) {

                        if (key[iSample] != string[obj->tokens[iToken2].start + 1 + iSample]) {

                            isEqual = 0x00;
                            break;

                        }

                    }

                    if (isEqual == 0x01) {

                        // Return next token in the array (will be the corresponding value to this key)
                        ptr = iToken2 + 1;
                        break;

                    }

                }

            }

        }

        return ptr;        

    }

    int json_tokens_getFromArray(const json_tokens * obj, const char * string, const int iToken, const unsigned int index) {

        unsigned int iToken2;
        unsigned int count;
        int ptr = -1;

        count = 0;

        // Loop only in filled tokens
        for (iToken2 = 0; iToken2 <= obj->iToken; iToken2++) {

            // If token belongs to this object...
            if (obj->tokens[iToken2].parent == iToken) {

                // .... and is a value
                if (json_tokens_type(obj, string, iToken2) == 'V') {

                    if (count == index) {

                        ptr = iToken2;
                        break;

                    }

                    count++;

                }

            }

        }

        return ptr;

    }

    int json_tokens_getFromValue(const json_tokens * obj, const char * string, const int iToken) {

        unsigned int iToken2;
        int ptr = -1;

        // Loop only in filled tokens
        for (iToken2 = 0; iToken2 <= obj->iToken; iToken2++) {

            // If token belongs to this object
            if (obj->tokens[iToken2].parent == iToken) {

                ptr = iToken2;
                break;

            }

        }

        return ptr;

    }


    void json_tokens_extractString(const json_tokens * obj, const char * string, const int iToken, char * dest) {

        unsigned int start;
        unsigned int len;

        start = obj->tokens[iToken].start+1;
        len = obj->tokens[iToken].end-obj->tokens[iToken].start-2;

        memcpy(dest, &(string[start]), sizeof(char) * len);
        dest[len] = 0x00;

    }

    void json_tokens_extractFloat(const json_tokens * obj, const char * string, const int iToken, float * dest) {

        char tmp[256]; // 256 characters should be more than enough for any numbers
        unsigned int start;
        unsigned int len;

        start = obj->tokens[iToken].start;
        len = obj->tokens[iToken].end-obj->tokens[iToken].start;

        memcpy(tmp, &(string[start]), sizeof(char) * len);
        tmp[len] = 0x00;

        *dest = atof(tmp);

    }

    void json_tokens_extractInt(const json_tokens * obj, const char * string, const int iToken, int * dest) {

        char tmp[256]; // 256 characters should be more than enough for any numbers
        unsigned int start;
        unsigned int len;

        start = obj->tokens[iToken].start;
        len = obj->tokens[iToken].end-obj->tokens[iToken].start;

        memcpy(tmp, &(string[start]), sizeof(char) * len);
        tmp[len] = 0x00;

        *dest = atoi(tmp);        

    }


    int json_fsm_micro_digit09(const char * string, int offset) {

        const char allowed[] = "0123456789";
        int ptr = offset;

        while ((strchr(allowed, string[ptr]) != (char *) NULL) && (string[ptr] != 0x00)) { ptr++; }

        if (ptr == offset) {
            ptr = -1;
        }

        return ptr;

    }

    int json_fsm_micro_digit19(const char * string, int offset) {

        const char allowed[] = "123456789";
        int ptr = offset;

        while ((strchr(allowed, string[ptr]) != (char *) NULL) && (string[ptr] != 0x00)) { ptr++; }

        if (ptr == offset) {
            ptr = -1;
        }

        return ptr;

    }

    int json_fsm_micro_unicode(const char * string, int offset) {

        // All control characters, and ", \ and null char (null must be at the end when using strchr)
        const char forbidden[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 
                                   0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 
                                   0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x22, 0x5C, 
                                   0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 
                                   0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 
                                   0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
                                   0x00 };
        int ptr = offset;

        while ((strchr(forbidden, string[ptr]) == (char *) NULL) && (string[ptr] != 0x00)) { ptr++; }

        if (ptr == offset) {
            ptr = -1;
        }

        return ptr;

    }

    int json_fsm_micro_4hex(const char * string, int offset) {

        // Hex numbers (we allow both capitalized and non-capitalized letters a-f)
        const char allowed[] = "0123456789ABCDEFabcdef";
        int ptr = offset;

        while ((strchr(allowed, string[ptr]) != (char *) NULL) && (string[ptr] != 0x00)) { ptr++; }

        
        if (ptr == offset) {
            ptr = -1;
        }

        return ptr;

    }

    int json_fsm_micro_space(const char * string, int offset) {

        // Ignore space, line return, carriage return and tabs
        const char allowed[] = { 0x09, 0x0A, 0x0D, 0x20, 0x00 };
        int ptr = offset;

        while ((strchr(allowed, string[ptr]) != (char *) NULL) && (string[ptr] != 0x00)) { ptr++; }

        return ptr;

    }

    int json_fsm_micro_char(const char * string, int offset, const char special) {

        int ptr = offset;

        if (string[ptr] == special) {
            ptr++;
        }
        else {
            ptr = -1;
        }

        return ptr;

    }

    int json_fsm_micro_true(const char * string, int offset) {

        if (string[offset+0] != 't') { return -1; }
        if (string[offset+1] != 'r') { return -1; }
        if (string[offset+2] != 'u') { return -1; }
        if (string[offset+3] != 'e') { return -1; }

        return (offset+4);

    }

    int json_fsm_micro_false(const char * string, int offset) {

        if (string[offset+0] != 'f') { return -1; }
        if (string[offset+1] != 'a') { return -1; }
        if (string[offset+2] != 'l') { return -1; }
        if (string[offset+3] != 's') { return -1; }
        if (string[offset+4] != 'e') { return -1; }            

        return (offset+5);

    }

    int json_fsm_micro_null(const char * string, int offset) {

        if (string[offset+0] != 'n') { return -1; }
        if (string[offset+1] != 'u') { return -1; }
        if (string[offset+2] != 'l') { return -1; }
        if (string[offset+3] != 'l') { return -1; }

        return (offset+4);

    }

    int json_fsm_object(const char * string, int offset, json_tokens * tokens, int parent) {

        int start = offset;
        int end;
        int ptr = offset;
        int ptrUpd;
        int state = 1;
        int iToken;

        //             +------------------->------------------+
        //             |  3             4     5           6   |
        // 1 +-->[{]>--+--+-->[string]>---[:]---[value]---+---+--->[}]>--+ 0
        //             2  |                               |
        //                +-------------<[,]<-------------+

        tokens->iToken++;
        iToken = tokens->iToken;

        if (iToken == tokens->nTokens) {
            printf("Token buffer overflow\n");
            exit(EXIT_FAILURE);
        }

        while ((ptr != -1) && (state != 0)) {

            switch (state) {

                case 1:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '{')) != -1) { state = 2; }

                    break;

                case 2:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '}')) != -1) { state = 0; }
                    else { ptrUpd = ptr; state = 3; }

                    break;

                case 3:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_string(string, ptr, tokens, iToken)) != -1) { state = 4; }

                    break;

                case 4:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, ':')) != -1) { state = 5; }

                    break;

                case 5:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_value(string, ptr, tokens, iToken)) != -1) { state = 6; }

                    break;

                case 6:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '}')) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, ',')) != -1) { state = 3; }

                    break;

            }

            ptr = ptrUpd;

        }

        end = ptr;

        if (ptr != -1) {

            tokens->tokens[iToken].parent = parent;
            tokens->tokens[iToken].start = start;
            tokens->tokens[iToken].end = end;

        }
        else {

            tokens->iToken = ((signed int) iToken) - 1;

        }

        return ptr;            

    }

    int json_fsm_array(const char * string, int offset, json_tokens * tokens, int parent) {

        int start = offset;
        int end;
        int ptr = offset;
        int ptrUpd;
        int state = 1;
        int iToken;       

        //             +------------------>------------------+
        //             |  3                               4  |          
        // 1 +-->[[]>--+--+----------->[value]>-----------+--+-->[]]>--+ 0
        //             2  |                               |
        //                +-------------<[,]<-------------+

        tokens->iToken++;
        iToken = tokens->iToken;        

        if (iToken == tokens->nTokens) {
            printf("Token buffer overflow\n");
            exit(EXIT_FAILURE);
        }

        while ((ptr != -1) && (state != 0)) {

            switch (state) {

                case 1:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '[')) != -1) { state = 2; }

                    break;

                case 2:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, ']')) != -1) { state = 0; }
                    else { ptrUpd = ptr; state = 3; }

                    break;

                case 3:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_value(string, ptr, tokens, iToken)) != -1) { state = 4; }

                    break;

                case 4:

                    ptr = json_fsm_micro_space(string, ptr);

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, ']')) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, ',')) != -1) { state = 3; }

                    break;

            }

            ptr = ptrUpd;

        }

        end = ptr;

        if (ptr != -1) {

            tokens->tokens[iToken].parent = parent;
            tokens->tokens[iToken].start = start;
            tokens->tokens[iToken].end = end;

        }
        else {

            tokens->iToken = ((signed int) iToken) - 1;

        }        

        return ptr;         

    }

    int json_fsm_value(const char * string, int offset, json_tokens * tokens, int parent) {

        int start = offset;
        int end;
        int ptr = offset;
        int ptrUpd;
        int state = 1;
        int iToken;           

        // 1 +--+------>[string]>------+--+ 0
        //      +------>[number]>------+
        //      +------>[object]>------+
        //      +------>[array]>-------+
        //      +------>[true]>--------+
        //      +------>[false]>-------+
        //      +------>[null]>--------+

        tokens->iToken++;
        iToken = tokens->iToken;

        if (iToken == tokens->nTokens) {
            printf("Token buffer overflow\n");
            exit(EXIT_FAILURE);
        }

        while ((ptr != -1) && (state != 0)) {

            switch (state) {

                case 1:

                    if ((ptrUpd = json_fsm_string(string, offset, tokens, iToken)) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_number(string, offset, tokens, iToken)) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_object(string, offset, tokens, iToken)) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_array(string, offset, tokens, iToken)) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_micro_true(string, offset)) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_micro_false(string, offset)) != -1) { state = 0; }
                    else if ((ptrUpd = json_fsm_micro_null(string, offset)) != -1) { state = 0; }

                    break;

            }

            ptr = ptrUpd;

        }

        end = ptr;

        if (ptr != -1) {

            tokens->tokens[iToken].parent = parent;
            tokens->tokens[iToken].start = start;
            tokens->tokens[iToken].end = end;

        }
        else {

            tokens->iToken = iToken - 1;

        }        

        return ptr;        

    }

    int json_fsm_string(const char * string, int offset, json_tokens * tokens, int parent) {

        int start = offset;
        int end;
        int ptr = offset;
        int ptrUpd;
        int state = 1;
        int iToken;              

        //                 +------------------->------------------+
        //                 |   +---------------<---------------+  |
        //                 |   |                               |  |
        // 1 +--+->["]>-+--+---+---------->[unicode]>----------+--+-->["]>--+ 0
        //                 2   |                               |        
        //                     +-->[\]>--+---->["]>------------+
        //                               +---->[\]>------------+
        //                               +---->[/]>------------+
        //                               +---->[b]>------------+
        //                             3 +---->[f]>------------+  
        //                               +---->[n]>------------+
        //                               +---->[r]>------------+        
        //                               +---->[t]>------------+
        //                               +---->[u]>-->[4hex]>--+
        //                                          4

        tokens->iToken++;
        iToken = tokens->iToken;

        if (iToken == tokens->nTokens) {
            printf("Token buffer overflow\n");
            exit(EXIT_FAILURE);
        }

        while ((ptr != -1) && (state != 0)) {

            switch (state) {

                case 1:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '"')) != -1) { state = 2; }

                    break;

                case 2:

                    if ((ptrUpd = json_fsm_micro_unicode(string, ptr)) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, '\\')) != -1) { state = 3; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, '"')) != -1) { state = 0; }

                    break;

                case 3:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '"')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, '\\')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, '/')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 'b')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 'f')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 'n')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 'r')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 't')) != -1) { state = 2; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 'u')) != -1) { state = 4; }

                    break;

                case 4:

                    if ((ptrUpd = json_fsm_micro_4hex(string, ptr)) != -1) { state = 2; }

                    break;

            }

            ptr = ptrUpd;

        }

        end = ptr;

        if (ptr != -1) {

            tokens->tokens[iToken].parent = parent;
            tokens->tokens[iToken].start = start;
            tokens->tokens[iToken].end = end;

        }
        else {

            tokens->iToken = iToken - 1;

        }        

        return ptr;        

    }

    int json_fsm_number(const char * string, int offset, json_tokens * tokens, int parent) {

        int start = offset;
        int end;
        int ptr = offset;
        int ptrUpd;
        int state = 1;
        int iToken;                     

        //                                                               
        //                                    +------------>-------------+
        //                2                 4 |       5               6  |  7
        // 1 +--+--->---+---+------>[0]>------+->[.]>-+->[digit 0-9]>-+--+--+---------------------->--------------------+--+ 0
        //      |       |   |                 |       |               |     v                                           |
        //      +->[-]>-+   v                 ^       +-------<-------+     |                                           ^
        //                  |                 | 3                           +->[e]>-+   +->[+]>-+   +-------<-------+   |
        //                  +-->[digit 1-9]>--+-------<-------+             |       |   |       |   |               |   |
        //                                    |               |             v       +->-+--->---+->-+->[digit 0-9]>-+->-+
        //                                    +->[digit 0-9]>-+             |       | 8 |       | 9                  10
        //                                                                  +->[E]>-+   +->[-]>-+

        tokens->iToken++;
        iToken = tokens->iToken;        

        if (iToken == tokens->nTokens) {
            printf("Token buffer overflow\n");
            exit(EXIT_FAILURE);
        }

        while ((ptr != -1) && (state != 0)) {

            switch (state) {

                case 1:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '-')) != -1) { state = 2; }
                    else { ptrUpd = ptr; state = 2; }

                    break;

                case 2:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '0')) != -1) { state = 4; }
                    else if ((ptrUpd = json_fsm_micro_digit19(string, ptr)) != -1) { state = 3; }

                    break;

                case 3:

                    if ((ptrUpd = json_fsm_micro_digit09(string, ptr)) != -1) { state = 3; }
                    else { ptrUpd = ptr; state = 4; }

                    break;

                case 4:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '.')) != -1) { state = 5; }
                    else { ptrUpd = ptr; state = 7; }

                    break;

                case 5:

                    if ((ptrUpd = json_fsm_micro_digit09(string, ptr)) != -1) { state = 6; }

                    break;

                case 6:

                    if ((ptrUpd = json_fsm_micro_digit09(string, ptr)) != -1) { state = 6; }
                    else { ptrUpd = ptr; state = 7; }

                    break;

                case 7:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, 'e')) != -1) { state = 8; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, 'E')) != -1) { state = 8; }
                    else { ptrUpd = ptr; state = 0; }

                    break;

                case 8:

                    if ((ptrUpd = json_fsm_micro_char(string, ptr, '+')) != -1) { state = 9; }
                    else if ((ptrUpd = json_fsm_micro_char(string, ptr, '-')) != -1) { state = 9; }
                    else { ptrUpd = ptr; state = 9; }

                    break;

                case 9:

                    if ((ptrUpd = json_fsm_micro_digit09(string, ptr)) != -1) { state = 10; }

                    break;

                case 10:

                    if ((ptrUpd = json_fsm_micro_digit09(string, ptr)) != -1) { state = 10; }
                    else { ptrUpd = ptr; state = 0; }

                    break;

            }

            ptr = ptrUpd;

        }

        end = ptr;

        if (ptr != -1) {

            tokens->tokens[iToken].parent = parent;
            tokens->tokens[iToken].start = start;
            tokens->tokens[iToken].end = end;

        }
        else {

            tokens->iToken = iToken - 1;

        }                

        return ptr;        

    }
