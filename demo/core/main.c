
	#include <odas/odas.h>

    #include "settings.h"
    #include "sockets.h"
    #include "configs.h"  
    #include "params.h" 
    #include "objects.h"

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

        printf(" Parameters:\n");
        printf("\n");
        printf("  -c     Configuration file (.json)\n");
        printf("  -h     Help\n");
        printf("  -s     Socket file (.json)\n");
        printf("\n");

    }

	int main(int argc, char * argv[]) {

        const unsigned int nMessages = 100;

        settings * sets;
        sockets * scks;
        configs * cfgs;
        objects * objs;

        int c;

        char * file_config = (char *) NULL;
        char * file_socket = (char *) NULL;

        while ((c = getopt(argc,argv, "c:hs:")) != -1) {

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

                case 's':

                    file_socket = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                    strcpy(file_socket, optarg);                        

                break;

            }

        }

        if (file_config == NULL) {
            printf("Missing configuration file.\n");
            exit(EXIT_FAILURE);
        }            

        if (file_socket == NULL) {
            printf("Missing socket file.\n");
            exit(EXIT_FAILURE);
        } 

        print_copyright();    

        printf(" Initializing settings.... "); fflush(stdout);
        sets = settings_construct();
        scks = sockets_construct();
        settings_load(sets, file_config);
        sockets_load(scks, file_socket);
        printf("[Done]\n");

        printf(" Initializing configs..... "); fflush(stdout); 
        cfgs = configs_construct();
        params_process(sets, scks, cfgs);
        sockets_printf(scks);
        printf("[Done]\n");

        printf(" Terminating settings..... "); fflush(stdout);
        settings_destroy(sets);
        sockets_destroy(scks);
        printf("[Done]\n");

        printf(" Initializing objects..... "); fflush(stdout);        
        objs = objects_construct(cfgs, nMessages);
        printf("[Done]\n");       

        printf(" Terminating configs...... "); fflush(stdout);
        configs_destroy(cfgs);
        printf("[Done]\n");
        
        printf(" Processing in progress... "); fflush(stdout);
        objects_process(objs);
        printf("[Done]\n");

        printf(" Terminating objects...... "); fflush(stdout);
        objects_destroy(objs);
        printf("[Done]\n");

        free((void *) file_config);

        return 0;

	}