    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <signal.h>
    #include <getopt.h>

    int main(int argc, char* argv[])
    {

        char verbose = 0x00;

        int server_id;
        struct sockaddr_in server_address;
        int connection_id;
        char * message;
        int messageSize;

        int c;
        unsigned int portNumber;
        char * fileName;
        FILE * fp;

        const unsigned int nBytes = 10240;

        while ((c = getopt(argc,argv, "p:o:hv")) != -1) {

            switch(c) {

                case 'h':

                    printf("+----------------------------------------------------+\n");
                    printf("|        ODAS (Open embeddeD Audition System)        |\n");
                    printf("+----------------------------------------------------+\n");
                    printf("| Author:      Francois Grondin                      |\n");
                    printf("| Email:       francois.grondin2@usherbrooke.ca      |\n");
                    printf("| Website:     introlab.3it.usherbrooke.ca           |\n");
                    printf("| Repository:  github.com/introlab/odas              |\n");
                    printf("| Version:     1.0                                   |\n");
                    printf("+----------------------------------------------------+\n");        
                    printf("| -h       Help                                      |\n");
                    printf("| -o       Output file                               |\n");
                    printf("| -p       Port number                               |\n");
                    printf("| -v       Verbose                                   |\n");
                    printf("+----------------------------------------------------+\n");

                    exit(EXIT_SUCCESS);                     

                case 'o':

                    fileName = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                    strcpy(fileName, optarg);   

                break;

                case 'p':

                    portNumber = atoi(optarg);

                break;


            }

        }

        server_id = socket(AF_INET, SOCK_STREAM, 0);

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(portNumber);

        printf("Opening file............. "); fflush(stdout);
        fp = fopen(fileName, "wb");
        printf("[OK]\n");

        printf("Binding socket........... ");  fflush(stdout);
        bind(server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        printf("[OK]\n");

        printf("Listening socket......... ");  fflush(stdout);
        listen(server_id, 1);
        printf("[OK]\n");

        printf("Waiting for connection... "); fflush(stdout);
        connection_id = accept(server_id, (struct sockaddr*) NULL, NULL);
        printf("[OK]\n");

        message = (char *) malloc(sizeof(char) * nBytes);

        printf("Receiving data........... "); fflush(stdout);
        while( (messageSize = recv(connection_id, message, nBytes, 0)) > 0) {

            message[messageSize] = 0x00;

            fwrite(message, messageSize, sizeof(char), fp);

        }
        printf("[OK]\n");

        printf("Closing file............. "); fflush(stdout);
        fclose(fp);
        printf("[OK]\n");

    }