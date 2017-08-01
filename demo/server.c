    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    int main(int argc, char* argv[])
    {

        int server_id;
        struct sockaddr_in server_address;
        int connection_id;
        char * message;
        int messageSize;

        if (argc != 2) {

            printf("Expecting one argument\n");
            exit(EXIT_FAILURE);
        }

        server_id = socket(AF_INET, SOCK_STREAM, 0);

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(atoi(argv[1]));

        printf("Binding socket... ");  fflush(stdout);
        bind(server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        printf("[OK]\n");

        printf("Listening socket... ");  fflush(stdout);
        listen(server_id, 1);
        printf("[OK]\n");

        printf("Waiting for connection..."); fflush(stdout);
        connection_id = accept(server_id, (struct sockaddr*) NULL, NULL);
        printf("[OK]\n");

        message = (char *) malloc(sizeof(char) * 1024 * 10);

        while( (messageSize = recv(connection_id, message, 1024 * 10, 0)) > 0) {

            message[messageSize] = 0x00;

            printf("Received (%u): %s\n",messageSize,message);

        }

        printf("messageSize = %d\n",messageSize);

    }