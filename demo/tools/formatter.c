
    #include <getopt.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>

    typedef struct processor {

        unsigned char nBytesIn;
        unsigned char nBytesOut;

        char deltaIn;
        char deltaOut;

        unsigned char C;

        unsigned char PIn;
        unsigned char POut;

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
        printf("  -h     Help\n");
        printf("  -i     Input bit format\n");
        printf("  -o     Output bit format\n");
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

    char extract_order(const char * formats[][4], const char format[]) {

        unsigned int iFormat = 0;
        char order = 0x00;

        while (strlen(formats[iFormat][0]) > 0) {
            
            if (strcmp(formats[iFormat][0], format) == 0) {
                order = formats[iFormat][3][0];
                break;
            }

            iFormat++;
        }

        return order;

    }

    void processor_init(processor * proc, const unsigned char nBitsIn, const char orderIn, const char unsigned nBitsOut, const char orderOut) {

        unsigned int iByteIn;
        unsigned int iByteOut;

        proc->nBytesIn = nBitsIn / 8;
        proc->nBytesOut = nBitsOut / 8;

        if (orderIn == 'b') { proc->deltaIn = +1; proc->PIn = 0; } 
        if (orderIn == 'l') { proc->deltaIn = -1; proc->PIn = proc->nBytesIn - 1; }
        if (orderOut == 'b') { proc->deltaOut = +1; proc->POut = 0; } 
        if (orderOut == 'l') { proc->deltaOut = -1; proc->POut = proc->nBytesOut - 1; }        

        if (proc->nBytesIn >= proc->nBytesOut) { proc->C = proc->nBytesOut; }
        if (proc->nBytesOut >= proc->nBytesIn) { proc->C = proc->nBytesIn; }

    }

    void processor_process(processor * proc, const char cIn[], char cOut[]) {

        unsigned char c;

        unsigned char pIn;
        unsigned char pOut;

        pIn = proc->PIn;
        pOut = proc->POut;

        memset(cOut, 0x00, proc->nBytesOut * sizeof(char));

        for (c = 0; c < proc->C; c++) {

            cOut[pOut] = cIn[pIn];

            pIn += proc->deltaIn;
            pOut += proc->deltaOut;

        }

    }

	int main(int argc, char * argv[]) {

        int c;
        char strIn[64] = "";
        char strOut[64] = "";

        unsigned int nBitsIn;
        unsigned int nBitsOut;
        char orderIn;
        char orderOut;

        char cIn[4];
        char cOut[4];

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

        while ((c = getopt(argc,argv, "hi:o:")) != -1) {

            switch(c) {

                case 'h':

                    print_copyright();
                    print_arguments(formats);
            
                    exit(EXIT_SUCCESS);

                break;

                case 'i':

                    if (validate_format(formats, optarg) == -1) {
                        printf("Invalid destination bit format\n");
                        exit(EXIT_FAILURE);
                    }

                    strcpy(strIn, optarg);

                break;

                case 'o':

                    if (validate_format(formats, optarg) == -1) {
                        printf("Invalid destination bit format\n");
                        exit(EXIT_FAILURE);
                    }

                    strcpy(strOut, optarg);

                break;

            }

        }

        if (strcmp(strIn, "") == 0) {
            printf("Missing input format\n");
            exit(EXIT_FAILURE);
        }
        if (strcmp(strOut, "") == 0) {
            printf("Missing output format\n");
            exit(EXIT_FAILURE);
        }

        nBitsIn = extract_bits(formats, strIn);
        nBitsOut = extract_bits(formats, strOut);
        orderIn = extract_order(formats, strIn);
        orderOut = extract_order(formats, strOut);

        processor_init(&proc, nBitsIn, orderIn, nBitsOut, orderOut);

        while(1) {

            rtn = read(STDIN_FILENO, cIn, proc.nBytesIn);
            if (rtn != proc.nBytesIn) { break; }
            processor_process(&proc, cIn, cOut);
            rtn = write(STDOUT_FILENO, cOut, proc.nBytesOut);
            //fsync(STDOUT_FILENO);

        }

        return 0;

	}
