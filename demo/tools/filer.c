    
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

    void print_arguments(void) {

        unsigned int iFormat = 0;

        printf(" Parameters:\n");
        printf("\n");
        printf("  -h     Help\n");
        printf("  -p     Port\n");
        printf("\n");

    }

    int recvExactNumber(const unsigned int cid, char buffer[], unsigned int bufferSize) {

        unsigned int msgSize;
        unsigned int nBytes;
        int rtn;

        nBytes = 0;

        while( (msgSize = recv(cid, &(buffer[nBytes]), (bufferSize-nBytes), 0)) > 0) {

            nBytes += msgSize;
            if (nBytes == bufferSize) { break; }

        }        

        if (msgSize == 0) { rtn = -1; } else { rtn = 0; }
        return rtn;

    }

    int main(int argc, char * argv[]) {

        int c;

        struct sockaddr_in server_address;

        unsigned int portIn = 0;
        unsigned int sid;
        unsigned int cid;
        
        unsigned long long id;
        char strId[64] = "";
        
        char buffer[8];
        FILE * fp;
        int rtn;

        while ((c = getopt(argc,argv, "hp:")) != -1) {

            switch(c) {

                case 'h':

                    print_copyright();
                    print_arguments();
            
                    exit(EXIT_SUCCESS);

                break;

                case 'p':

                    portIn = atoi(optarg);

                break;

            }

        }

        if (portIn == 0) {
            printf("Missing port number\n");
            exit(EXIT_SUCCESS);
        }

        memset(&server_address, 0x00, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(portIn);

        sid = socket(AF_INET, SOCK_STREAM, 0);
        printf("sid = %d\n", sid);
        
        if ((bind(sid, (struct sockaddr *) &server_address, sizeof(server_address))) < 0) {
            printf("Cannot bind to port %u\n", portIn);
            exit(EXIT_FAILURE);
        }
        listen(sid, 1);
        
        while(1) {

            printf("Waiting to accept connection\n");
            cid = accept(sid, (struct sockaddr*) NULL, NULL);     
            printf("cid = %d\n", cid);
         
            if ((rtn = recvExactNumber(cid, buffer, 8)) == -1) { break; }
            
            memcpy(&id, buffer, sizeof(unsigned long long));

            sprintf(strId, "%020llu.raw", id);
            fp = fopen(strId, "wb");

            printf("File create: %s­\n", strId);

            while(1) {

                rtn = recvExactNumber(cid, buffer, sizeof(char));

                if (rtn == -1) { break; }

                fwrite(buffer, 1, sizeof(char), fp);

            }

            fclose(fp);

        }

    }