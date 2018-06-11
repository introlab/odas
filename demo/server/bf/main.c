
	#include <odas/odas.h>

    #include "configs.h"
    #include "objects.h"
    #include "params.h"
    #include "settings.h"    

    void print_copyright(void) {

        printf("­\n");
        printf(" ODAS (Open embeddeD Audition System)\n");
        printf("\n");
        printf(" Author:      Francois Grondin\n");
        printf(" Email:       fgrondin@mit.edu\n");
        printf(" Website:     odas.io\n");
        printf(" Version:     1.0\n");
        printf("\n");           

    }

    void print_arguments(void) {

        printf(" Parameters:\n");
        printf("\n");
        printf("  -c     Configuration file (.cfg)\n");
        printf("  -p     Port number\n");
        printf("  -h     Help\n");
        printf("\n");

    }

	int main(int argc, char * argv[]) {

        int c;

        char * file_config = (char *) NULL;
        unsigned int port_number = 0;
        char verbose = 0x00;

        settings * sets;
        configs * cfgs;
        objects * objs;

        int server_id;
        struct sockaddr_in server_address;
        int connection_id;

        const unsigned int nBytes = 65536;
        char * msg;
        char * strCumul;
        char * strTmp;
        unsigned int msgSize;

        json_tokens * tokens;
        int iToken;
        int lastChar;

        tokens = json_tokens_construct(65536);

        while ((c = getopt(argc,argv, "c:p:h")) != -1) {

            switch(c) {

                case 'c':

                    file_config = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                    strcpy(file_config, optarg);                        

                break;

                case 'h':

                    print_copyright();
                    print_arguments();
            
                    exit(EXIT_SUCCESS);

                break;

                case 'p':

                    port_number = atoi(optarg);

                break;

            }

        }

        if (file_config == NULL) {
            printf("Missing configuration file.\n");
            exit(EXIT_FAILURE);
        }            
        if (port_number == 0) {
            printf("Missing port number.\n");
            exit(EXIT_FAILURE);
        }

        print_copyright();    

        printf(" Loading settings... "); fflush(stdout);
        sets = settings_construct(file_config);
        printf("[Done]\n");

        printf(" Initializing configs... "); fflush(stdout); 
        cfgs = configs_construct();
        params_process(sets, cfgs);
        printf("[Done]\n");

        printf(" Initializing objects... "); fflush(stdout);
        objs = objects_construct(cfgs);
        objects_link(objs);
        printf("[Done]\n");       
        
        server_id = socket(AF_INET, SOCK_STREAM, 0);

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(port_number);

        msg = (char *) malloc(sizeof(char) * nBytes);
        strCumul = (char *) malloc(sizeof(char) * nBytes);
        strTmp = (char *) malloc(sizeof(char) * nBytes);
        strCumul[0] = 0x00;
        strTmp[0] = 0x00;

        printf(" Binding socket to port... ");  fflush(stdout);
        bind(server_id, (struct sockaddr *) &server_address, sizeof(server_address));
        printf("[Done]\n");

        printf(" Listening socket... ");  fflush(stdout);
        listen(server_id, 1);
        printf("[Done]\n");

        printf(" Waiting for connection... "); fflush(stdout);
        connection_id = accept(server_id, (struct sockaddr*) NULL, NULL);
        printf("[Done]\n");

        printf(" Receiving data... "); fflush(stdout);
        while( (msgSize = recv(connection_id, msg, nBytes, 0)) > 0) {

            msg[msgSize] = 0x00;
            strcat(strCumul, msg);

            json_tokens_clear(tokens);
            lastChar = json_tokens_parse(tokens, msg);

            if (lastChar != -1) {

                // Inputs

                iToken = json_tokens_getFromValue(tokens, msg, -1);
                iToken = json_tokens_getFromObject(tokens, msg, iToken, "raw");

                json_tokens_getSection(tokens, msg, iToken, objs->in1);

                iToken = json_tokens_getFromValue(tokens, msg, -1);
                iToken = json_tokens_getFromObject(tokens, msg, iToken, "aim");

                json_tokens_getSection(tokens, msg, iToken, objs->in2);

                // Process

                objects_process(objs);

                // Outputs

                strTmp[0] = 0x00;
                strcat(strTmp, "{\"separated\":");
                strcat(strTmp, objs->out1);
                strcat(strTmp, ",\"tracks\":");
                strcat(strTmp, objs->out2);
                strcat(strTmp, "}");

                send(connection_id, strTmp, strlen(strTmp), 0);

                // Update buffers
                
                strcpy(strTmp, &(strCumul[lastChar]));
                strcpy(strCumul, strTmp);

            }

        }
        printf("[Done]\n");

        return 0;

	}