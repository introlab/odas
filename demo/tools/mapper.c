
    #include <getopt.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #define MAX_NCHANNELS 32

    typedef struct processor {

        int channels[MAX_NCHANNELS];

        unsigned int nBits;
        unsigned int nBytes;

        unsigned int nChannelsIn;
        unsigned int nChannelsOut;
        unsigned int nBytesIn;
        unsigned int nBytesOut;

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
        printf("  -b     Bit format\n");
        printf("  -h     Help\n");
        printf("  -i     Number of input channels\n");
        printf("  -o     Mapping of output channels\n");
        printf("\n");
        printf(" List of supported bit formats:\n");
        printf("\n");


        while (strlen(formats[iFormat][0]) > 0) {
            printf("  %-5s  %s\n", formats[iFormat][0], formats[iFormat][1]);
            iFormat++;
        }

        printf("\n");

    }

    int validate_format(const char * formats[][4], char format[]) {

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

    int remove_spaces(char * dest, const char * src) {

        const char spaces[] = { 0x09, 0x0A, 0x0D, 0x20, 0x00 };

        unsigned int ptrSrc = 0;
        unsigned int ptrDest = 0;

        for (ptrSrc = 0; ptrSrc < strlen(src); ptrSrc++) {

            if (strchr(spaces, src[ptrSrc]) == (char *) NULL) {
                dest[ptrDest++] = src[ptrSrc];
            }

        }

        dest[ptrDest] = 0x00;

    }

    int parse_channels(const char * string, unsigned int channels[]) {
        
        const char numbers[] = "0123456789";
        const char range[] = "-";
        const char separator[] = ",;";

        unsigned int ptr;
        int state;

        char fN, fR, fS, f0;

        unsigned int number1;
        unsigned int number2;
        char tmp[2] = {0,0};

        unsigned int iChannel;
        unsigned int number;

        state = 0;
        iChannel = 0;

        for (ptr = 0; ptr <= strlen(string); ptr++) {

            if (string[ptr] == 0x00) { 

                f0 = 1; fN = 0; fR = 0; fS = 0;

            } 
            else {
            
                f0 = 0;

                if (strchr(numbers, string[ptr]) != (char *) NULL) { fN = 1; } else { fN = 0; }
                if (strchr(range, string[ptr]) != (char *) NULL) { fR = 1; } else { fR = 0; }
                if (strchr(separator, string[ptr]) != (char *) NULL) { fS = 1; } else { fS = 0; }

            }

            switch(state) {

                case 0:

                    state = -1;
                    if (fN == 1) { state = 1; } if (f0 == 1) { state = 0; }                   
                    if (fN == 1) { number1 = 0;  tmp[0] = string[ptr]; number1 *= 10; number1 += atoi(tmp); }

                break;

                case 1:

                    state = -1;
                    if (fN == 1) { state = 1; } if (fR == 1) { state = 2; } if (fS == 1) { state = 4; } if (f0 == 1) { state = 0; }
                    if (fN == 1) { tmp[0] = string[ptr]; number1 *= 10; number1 += atoi(tmp); }
                    if ((fS == 1) || (f0 == 1)) { channels[iChannel] = number1; iChannel++; }

                break;

                case 2:

                    state = -1;
                    if (fN == 1) { state = 3; }
                    if (fN == 1) { number2 = 0; tmp[0] = string[ptr]; number2 *= 10; number2 += atoi(tmp); }

                break;

                case 3:

                    state = -1;
                    if (fN == 1) { state = 3; } if (fS == 1) { state = 4; } if (f0 == 1) { state = 0; }
                    if (fN == 1) { tmp[0] = string[ptr]; number2 *= 10; number2 += atoi(tmp); }
                    if ((fS == 1) || (f0 == 1)) { if (number2 >= number1) { for (number = number1; number <= number2; number++) { channels[iChannel] = number; iChannel++; } } else { state = -1; } }                    

                break;

                case 4:

                    state = -1;
                    if (fN == 1) { state = 1; }
                    if (fN == 1) { number1 = 0; tmp[0] = string[ptr]; number1 *= 10; number1 += atoi(tmp); }

                break;                

            }

            if (state == -1) { break; }

        }

        return state;

    }

    void processor_init(processor * proc, const unsigned int nBits, const unsigned int nChannelsIn, const char channelsOut[]) {

        char strTmp[256] = {0};
        unsigned int iChannel;

        remove_spaces(strTmp, channelsOut);

        memset(proc->channels, (int) -1, sizeof(int) * MAX_NCHANNELS);

        if (parse_channels(strTmp, proc->channels) == -1) {
            printf("Invalid expression for output channels\n");
            exit(EXIT_FAILURE);
        };

        proc->nBits = nBits;
        proc->nBytes = nBits / 8;

        proc->nChannelsIn = nChannelsIn;
        proc->nChannelsOut = 0;
        for (iChannel = 0; iChannel < MAX_NCHANNELS; iChannel++) {
            if (proc->channels[iChannel] != -1) {
                proc->nChannelsOut++;
            }
        }

        proc->nBytesIn = proc->nChannelsIn * proc->nBytes;
        proc->nBytesOut = proc->nChannelsOut * proc->nBytes; 

    }

    void processor_process(const processor * proc, const char cIn[], char cOut[]) {

        unsigned int iChannelIn;
        unsigned int iChannelOut;
        unsigned int iByteIn;
        unsigned int iByteOut;

        for (iChannelOut = 0; iChannelOut < proc->nChannelsOut; iChannelOut++) {

            iChannelIn = proc->channels[iChannelOut];

            iByteIn = iChannelIn * proc->nBytes;
            iByteOut = iChannelOut * proc->nBytes;

            memcpy(&(cOut[iByteOut]), &(cIn[iByteIn]), proc->nBytes * sizeof(char));

        }

    }

	int main(int argc, char * argv[]) {

        int c;
        char strBits[6] = "";
        char nIn = 0;
        char strOut[256] = "";

        processor proc;

        char cIn[1024];
        char cOut[1024];

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

        while ((c = getopt(argc,argv, "b:hi:o:")) != -1) {

            switch(c) {

                case 'b':

                    if (validate_format(formats, optarg) == -1) {
                        printf("Invalid destination bit format\n");
                        exit(EXIT_FAILURE);
                    }

                    strcpy(strBits, optarg);

                break;

                case 'h':

                    print_copyright();
                    print_arguments(formats);
            
                    exit(EXIT_SUCCESS);

                break;

                case 'i':

                    nIn = atoi(optarg);

                break;

                case 'o':

                    strcpy(strOut, optarg);

                break;

            }

        }

        if (strcmp(strBits, "") == 0) {
            printf("Missing format\n");
            exit(EXIT_FAILURE);
        }
        if (nIn == 0) {
            printf("Missing number of input channels\n");
            exit(EXIT_FAILURE);
        }
        if (strcmp(strOut, "") == 0) {
            printf("Missing output mapped channels\n");
            exit(EXIT_FAILURE);
        }

        processor_init(&proc, extract_bits(formats, strBits), nIn, strOut);

        while(1) {

            rtn = read(STDIN_FILENO, cIn, proc.nBytesIn);
            if (rtn != proc.nBytesIn) { break; }
            processor_process(&proc, cIn, cOut);
            rtn = write(STDOUT_FILENO, cOut, proc.nBytesOut);
            //fsync(STDOUT_FILENO);

        }        

        return 0;

	}
