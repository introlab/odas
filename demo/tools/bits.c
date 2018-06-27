
    #include <getopt.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

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
        printf("  -d     Destination bit format\n");
        printf("  -h     Help\n");
        printf("  -i     Input port number\n");
        printf("  -o     Output port number\n");
        printf("  -s     Source bit format\n");
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

    void convert(const char i[], const unsigned char iBits, const char iOrder, char o[], const char unsigned oBits, const char oOrder) {

        unsigned char iBytes;
        unsigned char oBytes;

        char iDelta;
        char oDelta;

        unsigned char c;
        unsigned char C;

        unsigned char ip;
        unsigned char iP;
        unsigned char op;
        unsigned char oP;

        iBytes = iBits / 8;
        oBytes = oBits / 8;

        memset(o, 0x00, sizeof(char) * oBytes);

        if (iOrder == 'b') { iDelta = +1; iP = 0; } 
        if (iOrder == 'l') { iDelta = -1; iP = iBytes - 1; }
        if (oOrder == 'b') { oDelta = +1; oP = 0; } 
        if (oOrder == 'l') { oDelta = -1; oP = oBytes - 1; }

        if (iBytes >= oBytes) { C = oBytes; }
        if (oBytes >= iBytes) { C = iBytes; }

        ip = iP;
        op = oP;

        for (c = 0; c < C; c++) {

            o[op] = i[ip];

            ip += iDelta;
            op += oDelta;

        }

    }

    void convertBuffer(const char iBuffer[], const unsigned char iBits, const char iOrder, char oBuffer[], const char unsigned oBits, const char oOrder, const unsigned int nSamples) {

        unsigned int iSample;

        unsigned int iBytes;
        unsigned int oBytes;

        iBytes = iBits / 8;
        oBytes = oBits / 8;

        for (iSample = 0; iSample < nSamples; iSample++) {

            convert(&(iBuffer[iSample * iBytes]), iBits, iOrder, &(oBuffer[iSample * oBytes]), oBits, oOrder);

        }

    }

	int main(int argc, char * argv[]) {

        int c;
        char iStr[6] = "";
        char oStr[6] = "";
        unsigned int iPort = 0;
        unsigned int oPort = 0;

        unsigned int iBits;
        unsigned int oBits;
        unsigned int iBytes;
        unsigned int oBytes;
        char iOrder;
        char oOrder;

        struct sockaddr_in server_address_in;
        struct sockaddr_in server_address_out;
        int sid_in;
        int sid_out;
        int cid_in;
        int cid_out;

        const unsigned int nSamples = 1024;

        unsigned int bufferInSize;
        unsigned int bufferOutSize;
        char * bufferIn;
        char * bufferOut;

        unsigned int messageSize;
        unsigned int nBytes;

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

        while ((c = getopt(argc,argv, "d:i:ho:s:")) != -1) {

            switch(c) {

                case 'd':

                    if (validate_format(formats, optarg) == -1) {
                        printf("Invalid destination bit format\n");
                        exit(EXIT_FAILURE);
                    }

                    strcpy(oStr, optarg);

                break;

                case 'h':

                    print_copyright();
                    print_arguments(formats);
            
                    exit(EXIT_SUCCESS);

                break;

                case 'i':

                    iPort = atoi(optarg);

                break;

                case 'o':

                    oPort = atoi(optarg);

                break;

                case 's':

                    if (validate_format(formats, optarg) == -1) {
                        printf("Invalid source bit format\n");
                        exit(EXIT_FAILURE);
                    }

                    strcpy(iStr, optarg);

                break;
            }

        }

        if (strcmp(iStr, "") == 0) {
            printf("Missing destination format\n");
            exit(EXIT_FAILURE);
        }
        if (iPort == 0) {
            printf("Missing input port\n");
            exit(EXIT_FAILURE);
        }
        if (strcmp(oStr, "") == 0) {
            printf("Missing source format\n");
            exit(EXIT_FAILURE);
        }
        if (oPort == 0) {
            printf("Missing output port\n");
            exit(EXIT_FAILURE);
        }

        iBits = extract_bits(formats, iStr);
        oBits = extract_bits(formats, oStr);
        iBytes = iBits / 8;
        oBytes = oBits / 8;
        iOrder = extract_order(formats, iStr);
        oOrder = extract_order(formats, oStr);

        bufferInSize = nSamples * iBytes;
        bufferOutSize = nSamples * oBytes;
        
        bufferIn = (char *) malloc(sizeof(char) * bufferInSize);
        bufferOut = (char *) malloc(sizeof(char) * bufferOutSize);
        memset(bufferIn, 0x00, sizeof(char) * bufferInSize);
        memset(bufferOut, 0x00, sizeof(char) * bufferOutSize);

        memset(&server_address_in, 0x00, sizeof(server_address_in));
        server_address_in.sin_family = AF_INET;
        server_address_in.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address_in.sin_port = htons(iPort);

        memset(&server_address_out, 0x00, sizeof(server_address_out));
        server_address_out.sin_family = AF_INET;
        server_address_out.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address_out.sin_port = htons(oPort);

        sid_in = socket(AF_INET, SOCK_STREAM, 0);
        sid_out = socket(AF_INET, SOCK_STREAM, 0);
        
        bind(sid_in, (struct sockaddr *) &server_address_in, sizeof(server_address_in));
        bind(sid_out, (struct sockaddr *) &server_address_out, sizeof(server_address_out));
        listen(sid_in, 1);
        listen(sid_out, 1);

        cid_in = accept(sid_in, (struct sockaddr*) NULL, NULL);
        cid_out = accept(sid_out, (struct sockaddr*) NULL, NULL);

        nBytes = 0;

        while( (messageSize = recv(cid_in, &(bufferIn[nBytes]), bufferInSize-nBytes, 0)) > 0) {

            // Socket is closed
            if (messageSize == 0) {
                break;
            }

            nBytes += messageSize;

            if (nBytes == bufferInSize) {
                
                convertBuffer(bufferIn, iBits, iOrder, bufferOut, oBits, oOrder, nSamples);
                send(cid_out, bufferOut, bufferOutSize, 0);
                nBytes = 0;

            }

        }

        free((void *) bufferIn);
        free((void *) bufferOut);

        return 0;

	}
