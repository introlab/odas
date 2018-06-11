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

        int sid;
        struct sockaddr_in server;
        char * message;
        int messageSize;

        int c;

        char * file_name = (char *) NULL;
        char * ip_string = (char *) NULL;
        unsigned int port_number = 0;

        FILE * fp;

        const unsigned int nBytes = 65536;

        while ((c = getopt(argc,argv,"f:i:p:")) != -1) {

            switch(c) {

                case 'f':

                    file_name = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));
                    strcpy(file_name, optarg);

                break;

                case 'i':

                    ip_string = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));
                    strcpy(ip_string, optarg);

                break;

                case 'p':

                    port_number = atoi(optarg);

                break;

            }

        }

        if (file_name == NULL) {
            printf("Missing content file.\n");
            exit(EXIT_FAILURE);
        }            
        if (ip_string == NULL) {
            printf("Missing ip address.\n");
            exit(EXIT_FAILURE);
        }            
        if (port_number == 0) {
            printf("Missing port number.\n");
            exit(EXIT_FAILURE);
        }        

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip_string);
        server.sin_port = htons(port_number);
        sid = socket(AF_INET, SOCK_STREAM, 0);

        if ( (connect(sid, (struct sockaddr *) &server, sizeof(server))) < 0 ) {

            printf("Cannot connect to server\n");
            exit(EXIT_FAILURE);

        }    

        while(1);

    }