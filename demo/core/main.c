
	#include <odas/odas.h>

    #include "settings.h" 
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
        printf(" Version:     1.0\n");
        printf("\n");           

    }

    void print_arguments(void) {

        printf(" Parameters:\n");
        printf("\n");
        printf("  -c     Configuration file (.cfg)\n");
        printf("  -p     Port number\n");
        printf("  -s     Compute sequentially in a single thread,\n         otherwise multithread is set by default\n");
        printf("  -h     Help\n");
        printf("\n");

    }

	int main(int argc, char * argv[]) {

        int c;

        char * file_config = (char *) NULL;
        char sequential = 0;

        settings * sets;
        configs * cfgs;
        objects * objs;
        aobjects * aobjs;

        while ((c = getopt(argc,argv, "c:hs")) != -1) {

            switch(c) {

                case 'c':

                    file_config = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                    strcpy(file_config, optarg);                        

                break;

                case 's':

                    sequential = 1;

                break;

                case 'h':

                    print_copyright();
                    print_arguments();
            
                    exit(EXIT_SUCCESS);

                break;

            }

        }

        if (file_config == NULL) {
            printf("Missing configuration file.\n");
            exit(EXIT_FAILURE);
        }            

        print_copyright();    

        printf(" Initializing settings.... "); fflush(stdout);
        sets = settings_construct();
        settings_load(sets, file_config);
        printf("[Done]\n");

        printf(" Initializing configs..... "); fflush(stdout); 
        cfgs = configs_construct();
        params_process(sets, cfgs);
        printf("[Done]\n");

        printf(" Terminating settings..... "); fflush(stdout);
        settings_destroy(sets);
        printf("[Done]\n");

        printf(" Initializing objects..... "); fflush(stdout);        
        if (sequential == 1) { objs = objects_construct(cfgs); aobjs = NULL; }
        else { objs = NULL; aobjs = aobjects_construct(cfgs); }
        printf("[Done]\n");       

        printf(" Terminating configs...... "); fflush(stdout);
        configs_destroy(cfgs);
        printf("[Done]\n");
        
        printf(" Processing in progress... "); fflush(stdout);
        if (sequential == 1) { objects_process(objs); }
        else { aobjects_process(aobjs); }
        printf("[Done]\n");

        printf(" Terminating objects...... "); fflush(stdout);
        if (sequential == 1) { objects_destroy(objs); }
        else { aobjects_destroy(aobjs); }
        printf("[Done]\n");

        free((void *) file_config);

        return 0;

	}