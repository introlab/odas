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
        char * message;
        int messageSize;

        int c;

        char file_name[256];
        char ip_string[256];
        unsigned int port_number = 0;

        const unsigned int nBytes = 65536;

        while ((c = getopt(argc,argv,"f:i:p:")) != -1) {

            switch(c) {

                case 'f':

                    strcpy(file_name, optarg);

                break;

                case 'i':

                    strcpy(ip_string, optarg);

                break;

                case 'p':

                    port_number = atoi(optarg);

                break;


            }

        }

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip_string);
        server.sin_port = htons(port_number);
        server_id = socket(AF_INET, SOCK_STREAM, 0);



    }