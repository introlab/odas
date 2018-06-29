
    #include <getopt.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>

    unsigned long long counter = 0;

    typedef struct processor{

        char bufferAudio[32];
        char bufferData[32];

        unsigned long long id;
        FILE * fp;

    } processor;
    
    void print_copyright(void) {

        printf("­\n");
        printf(" ODAS (Open embeddeD Audition System)\n");
        printf("\n");
        printf(" Author:      Francois Grondin\n");
        printf(" Email:       fgrondin@mit.edu\n");
        printf(" Website:     odas.io\n");
        printf(" Version:     3.0\n");
        printf("\n");           

    }

    void print_arguments(const char * formats[][4]) {

        unsigned int iFormat = 0;

        printf(" Parameters:\n");
        printf("\n");
        printf("  -b     Bit format­\n");
        printf("  -h     Help\n");
        printf("\n");
        printf(" List of supported bit formats:\n");
        printf("\n");

        while (strlen(formats[iFormat][0]) > 0) {
            printf("  %-5s  %s\n", formats[iFormat][0], formats[iFormat][1]);
            iFormat++;
        }

        printf("\n");        

    }

    int validate_format(const char * formats[][4], const char format[]) {

        unsigned int iFormat = 0;
        int match = -1;

        while (strlen(formats[iFormat][0]) > 0) {
            
            if (strcmp(formats[iFormat][0], format) == 0) {
                match = 0;
                break;
            }

            iFormat++;
        }

        return match;        

    }

    unsigned char extract_bits(const char * formats[][4], const char format[]) {

        unsigned int iFormat = 0;
        unsigned char bits = 0;

        while (strlen(formats[iFormat][0]) > 0) {
            
            if (strcmp(formats[iFormat][0], format) == 0) {
                bits = atoi(formats[iFormat][2]);
                break;
            }

            iFormat++;
        }

        return bits;

    }

    void processor_init(processor * proc) {

        memset(proc->bufferData, 0x00, 32 * sizeof(char));
        memset(proc->bufferAudio, 0x00, 32 * sizeof(char));

        proc->id = 0;
        proc->fp = NULL;

    }

    void processor_process(processor * proc, const char cData, const char cAudio) {

        char fileStr[64] = "";
        unsigned long long flag1;
        unsigned long long flag2;
        unsigned long long timeStamp;
        unsigned long long id;

        unsigned int tmp;
        counter++;

        memmove(&(proc->bufferData[0]), &(proc->bufferData[1]), 31 * sizeof(char));
        proc->bufferData[31] = cData;

        memmove(&(proc->bufferAudio[0]), &(proc->bufferAudio[1]), 31 * sizeof(char));
        proc->bufferAudio[31] = cAudio;

        memcpy(&flag1, &(proc->bufferData[0]), 8);
        memcpy(&flag2, &(proc->bufferData[8]), 8);
        memcpy(&timeStamp, &(proc->bufferData[16]), 8);
        memcpy(&id, &(proc->bufferData[24]), 8);

        if ((flag1 == 0xFFFFFFFFFFFFFFFF) && (flag2 == 0x0000000000000000)) {

            proc->id = id;

        }

        if (proc->id != 0) {

            if (proc->fp == NULL) {

                sprintf(fileStr, "%08llu.raw", proc->id);
                proc->fp = fopen(fileStr, "wb");

            }

            fwrite(&(proc->bufferAudio[0]), 1, sizeof(char), proc->fp);

        }
        else {

            if (proc->fp != NULL) {

                fclose(proc->fp);
                proc->fp = NULL;

            }

        }

    }

    void processor_terminate(processor * proc) {

        if (proc->fp != NULL) {

            fclose(proc->fp);
            proc->fp = NULL;

        }        

    }

    int main(int argc, char * argv[]) {

        int c;

        char strBits[64] = "";
        unsigned int nBits = 0;
        unsigned int nBytes = 0;

        char cAudio[4];
        char cData[4];
        unsigned int iByte;

        processor proc;

        int rtn;

        const char * formats[][4] = { 
            {"s16be","PCM signed 16-bit big-endian","16","b"},
            {"s16le","PCM signed 16-bit little-endian","16","l"},
            {"s24be","PCM signed 24-bit big-endian","24","b"},
            {"s24le","PCM signed 24-bit little-endian","16","l"},
            {"s32be","PCM signed 32-bit big-endian","32","b"},
            {"s32le","PCM signed 32-bit little-endian","32","l"},
            {"s8","PCM signed 8-bit","8","b"},
            {"",""}
        };

        while ((c = getopt(argc,argv, "b:h")) != -1) {

            switch(c) {

                case 'b':

                    strcpy(strBits, optarg);

                break;

                case 'h':

                    print_copyright();
                    print_arguments(formats);
            
                    exit(EXIT_SUCCESS);

                break;

            }

        }

        if (strcmp(strBits, "") == 0) {
            printf("Missing bit format\n");
            exit(EXIT_FAILURE);
        }

        nBits = extract_bits(formats, strBits);
        nBytes = nBits / 8;

        processor_init(&proc);

        while(1) {

            rtn = read(STDIN_FILENO, cAudio, nBytes);
            if (rtn != nBytes) { break; }

            rtn = read(STDIN_FILENO, cData, nBytes);
            if (rtn != nBytes) { break; }

            for (iByte = 0; iByte < nBytes; iByte++) {
                processor_process(&proc, cData[iByte], cAudio[iByte]);
            }

        }

        processor_terminate(&proc);

    }
