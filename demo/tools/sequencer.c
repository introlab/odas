
    #include <getopt.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    typedef struct processor{

        char bufferAudio[32];
        char bufferData[32];

        char flagTag;
        unsigned long long id;

        struct sockaddr_in server_address;
        int sid;

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
        printf("  -i     IP address (default is localhost)\n");
        printf("  -p     Port number\n");
        printf("  -t     Tag stream with ID\n");
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

    void processor_init(processor * proc, const char flagTag, const char strIp[], const unsigned int port) {

        memset(proc->bufferData, 0x00, 32 * sizeof(char));
        memset(proc->bufferAudio, 0x00, 32 * sizeof(char));

        proc->id = 0;
        proc->flagTag = flagTag;

        proc->sid = -1;

        memset(&proc->server_address, 0x00, sizeof(proc->server_address));
        proc->server_address.sin_family = AF_INET;
        
        if (strcmp(strIp, "") == 0) { 
            proc->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else { 
            inet_pton(AF_INET, strIp, &(proc->server_address.sin_addr));
        }
                
        proc->server_address.sin_port = htons(port);


    }

    void processor_process(processor * proc, const char cData, const char cAudio) {

        char fileStr[64] = "";
        unsigned long long flag1;
        unsigned long long flag2;
        unsigned long long timeStamp;
        unsigned long long id;

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

            if (proc->sid == -1) {

                printf("Creating connection for %llu\n", proc->id);
                
                if ((proc->sid = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                    printf("Cannot connect to socket\n");
                    exit(EXIT_FAILURE);                   
                }

                if ((connect(proc->sid,(struct sockaddr *)&(proc->server_address),sizeof(proc->server_address))) < 0) {
                    printf("Cannot connect to socket\n");
                    exit(EXIT_FAILURE);
                }

                if (proc->flagTag == 1) {
                    send(proc->sid, &(proc->id), sizeof(unsigned long long), 0);
                }

            }

            send(proc->sid, &(proc->bufferAudio[0]), sizeof(char), 0);

        }
        else {

            if (proc->sid != -1) {

                printf("Closing connection for %llu\n", proc->id);
                close(proc->sid);
                proc->sid = -1;

            }

        }

    }

    void processor_terminate(processor * proc) {

        if (proc->sid != -1) {

            close(proc->sid);
            proc->sid = -1;

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
        char flagTag = 0;

        char strIp[64] = "";
        unsigned int portInput = 0;

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

        while ((c = getopt(argc,argv, "b:hi:p:t")) != -1) {

            switch(c) {

                case 'b':

                    strcpy(strBits, optarg);

                break;

                case 'h':

                    print_copyright();
                    print_arguments(formats);
            
                    exit(EXIT_SUCCESS);

                break;

                case 'i':

                    strcpy(strIp, optarg);

                break;

                case 'p':

                    portInput = atoi(optarg);

                break;

                case 't':

                    flagTag = 1;

                break;

            }

        }

        if (strcmp(strBits, "") == 0) {
            printf("Missing bit format\n");
            exit(EXIT_FAILURE);
        }
        if (portInput == 0) {
            printf("Missing port number\n");
            exit(EXIT_FAILURE);
        }

        nBits = extract_bits(formats, strBits);
        nBytes = nBits / 8;

        processor_init(&proc, flagTag, strIp, portInput);

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
