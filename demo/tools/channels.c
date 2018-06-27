
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
        printf("  -b     Bit format\n");
        printf("  -h     Help\n");
        printf("  -i     Input port number\n");
        printf("  -o     Output port number\n");
        printf("  -s     Selection of channels\n");
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

                f0 = 1;
                fN = 0;
                fR = 0;
                fS = 0;

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

                    if (fN == 1) { state = 1; }
                    if (f0 == 1) { state = 0; }

                    if (fN == 1) {
                        
                        number1 = 0;

                        tmp[0] = string[ptr];
                        number1 *= 10; 
                        number1 += atoi(tmp);

                    }

                break;

                case 1:

                    state = -1;

                    if (fN == 1) { state = 1; }
                    if (fR == 1) { state = 2; }
                    if (fS == 1) { state = 4; }
                    if (f0 == 1) { state = 0; }

                    if (fN == 1) {
                        
                        tmp[0] = string[ptr];
                        number1 *= 10; 
                        number1 += atoi(tmp);

                    }

                    if ((fS == 1) || (f0 == 1)) {

                        channels[iChannel] = number1;
                        iChannel++;

                    }

                break;

                case 2:

                    state = -1;

                    if (fN == 1) { state = 3; }

                    if (fN == 1) {
                        
                        number2 = 0;

                        tmp[0] = string[ptr];
                        number2 *= 10; 
                        number2 += atoi(tmp);

                    }

                break;

                case 3:

                    state = -1;

                    if (fN == 1) { state = 3; }
                    if (fS == 1) { state = 4; }
                    if (f0 == 1) { state = 0; }

                    if (fN == 1) {
                        
                        tmp[0] = string[ptr];
                        number2 *= 10; 
                        number2 += atoi(tmp);

                    }

                    if ((fS == 1) || (f0 == 1)) {

                        if (number2 >= number1) {

                            for (number = number1; number <= number2; number++) {

                                channels[iChannel] = number;
                                iChannel++;

                            }

                        }
                        else {

                            state = -1;

                        }

                    }                    

                break;

                case 4:

                    state = -1;

                    if (fN == 1) { state = 1; }

                    if (fN == 1) {
                        
                        number1 = 0;

                        tmp[0] = string[ptr];
                        number1 *= 10; 
                        number1 += atoi(tmp);

                    }

                break;                

            }

            if (state == -1) {
                break;
            }

        }

        return state;

    }

    void mapChannels(const char iBuffer[], char oBuffer[], const char unsigned nBits, const unsigned int channels[], const unsigned int nChannelsIn, const unsigned int nChannelsOut, const unsigned int nFrames) {

        unsigned int iFrame;
        
        unsigned int iChannelIn;
        unsigned int iChannelOut;
        unsigned int iSampleIn;
        unsigned int iSampleOut;
        unsigned int iByteIn;
        unsigned int iByteOut;

        unsigned int nBytes;

        nBytes = nBits / 8;

        for (iFrame = 0; iFrame < nFrames; iFrame++) {

            for (iChannelOut = 0; iChannelOut < nChannelsOut; iChannelOut++) {

                iChannelIn = channels[iChannelOut];

                iSampleIn = iFrame * nChannelsIn + iChannelIn;
                iSampleOut = iFrame * nChannelsOut + iChannelOut;

                iByteIn = iSampleIn * nBytes;
                iByteOut = iSampleOut * nBytes;

                memcpy(&(oBuffer[iByteOut]), &(iBuffer[iByteIn]), nBytes * sizeof(char));

            }

        }

    }

	int main(int argc, char * argv[]) {

        int c;
        char bStr[6] = "";
        unsigned int iPort = 0;
        unsigned int oPort = 0;
        char sStr[256] = "";
        unsigned int nChannels = 0;

        const unsigned int nChannelsMax = 32;
        char sStrCompact[256] = "";
        int channels[nChannelsMax];
        unsigned int iChannel;
        int rtnParse;

        unsigned int bBits;
        unsigned int bBytes;

        struct sockaddr_in server_address_in;
        struct sockaddr_in server_address_out;
        int sid_in;
        int sid_out;
        int cid_in;
        int cid_out;

        const unsigned int nFrames = 128;
        unsigned int nChannelsIn = 0;
        unsigned int nChannelsOut = 0;
        unsigned int nSamplesIn = 0;
        unsigned int nSamplesOut = 0;

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

        while ((c = getopt(argc,argv, "b:i:hn:o:s:")) != -1) {

            switch(c) {

                case 'b':

                    if (validate_format(formats, optarg) == -1) {
                        printf("Invalid destination bit format\n");
                        exit(EXIT_FAILURE);
                    }

                    strcpy(bStr, optarg);

                break;

                case 'h':

                    print_copyright();
                    print_arguments(formats);
            
                    exit(EXIT_SUCCESS);

                break;

                case 'i':

                    iPort = atoi(optarg);

                break;

                case 'n':

                    nChannels = atoi(optarg);

                break;

                case 'o':

                    oPort = atoi(optarg);

                break;

                case 's':

                    strcpy(sStr, optarg);

                break;
            }

        }

        if (strcmp(bStr, "") == 0) {
            printf("Missing format\n");
            exit(EXIT_FAILURE);
        }
        if (iPort == 0) {
            printf("Missing input port\n");
            exit(EXIT_FAILURE);
        }
        if (nChannels == 0) {
            printf("Missing number of channels of the input\n");
            exit(EXIT_FAILURE);
        }
        if (oPort == 0) {
            printf("Missing output port\n");
            exit(EXIT_FAILURE);
        }
        if (strcmp(sStr, "") == 0) {
            printf("Missing selection of channels\n");
            exit(EXIT_FAILURE);
        }

        bBits = extract_bits(formats, bStr);
        bBytes = bBits / 8;

        for (iChannel = 0; iChannel < nChannelsMax; iChannel++) {
            channels[iChannel] = -1;
        }

        remove_spaces(sStrCompact, sStr);
        if (parse_channels(sStrCompact, channels) == -1) {
            printf("Invalid expression for selected channels\n");
            exit(EXIT_FAILURE);
        };

        nChannelsIn = nChannels;

        nChannelsOut = 0;
        for (iChannel = 0; iChannel < nChannelsMax; iChannel++) {
            if (channels[iChannel] != -1) {
                nChannelsOut++;
            }
        }

        nSamplesIn = nFrames * nChannelsIn;
        nSamplesOut = nFrames * nChannelsOut;

        bufferInSize = nSamplesIn * bBytes;
        bufferOutSize = nSamplesOut * bBytes;
        
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
                                
                mapChannels(bufferIn, bufferOut, bBits, channels, nChannelsIn, nChannelsOut, nFrames);
                
                send(cid_out, bufferOut, bufferOutSize, 0);
                nBytes = 0;

            }

        }

        free((void *) bufferIn);
        free((void *) bufferOut);

        return 0;

	}
