
    #include <odas/odas.h>

    #include "parameters.h"
    #include "configs.h"
    #include "objects.h"
    #include "threads.h"

    #include <getopt.h>
    #include <time.h>

    int main(int argc, char * argv[]) {

        // +----------------------------------------------------------+
        // | Getopt                                                   |
        // +----------------------------------------------------------+   

            int c;
            char * file_config;
            char * file_ios;

        // +----------------------------------------------------------+
        // | Timer                                                    |
        // +----------------------------------------------------------+   

            struct timespec ts;

        // +----------------------------------------------------------+
        // | Flag                                                     |
        // +----------------------------------------------------------+              

            char isRunning;

        // +----------------------------------------------------------+
        // | Configurations                                           |
        // +----------------------------------------------------------+        

            configs * cfgs;

        // +----------------------------------------------------------+
        // | Objects                                                  |
        // +----------------------------------------------------------+        

            objects * objs;

        // +----------------------------------------------------------+
        // | Arguments                                                |
        // +----------------------------------------------------------+  

            file_config = (char *) NULL;
            file_ios = (char *) NULL;

            while ((c = getopt(argc,argv, "hc:i:")) != -1) {

                switch(c) {

                    case 'h':

                        exit(EXIT_SUCCESS);

                    break;

                    case 'c':

                        file_config = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(file_config, optarg);                        

                    break;

                    case 'i':

                        file_ios = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(file_ios, optarg);

                    break;

                }

            }

            if (file_config == NULL) {
                printf("Missing configuration file.\n");
                exit(EXIT_FAILURE);
            }
            if (file_ios == NULL) {
                printf("Missing ios file.\n");
                exit(EXIT_FAILURE);
            }

        // +----------------------------------------------------------+
        // | Copyright                                                |
        // +----------------------------------------------------------+ 

            printf("+--------------------------------------------+\n");
            printf("|    ODAS (Open embeddeD Audition System)    |\n");
            printf("+--------------------------------------------+\n");
            printf("| Author:  Francois Grondin                  |\n");
            printf("| Email:   francois.grondin2@usherbrooke.ca  |\n");
            printf("| Website: introlab.3it.usherbrooke.ca       |\n");
            printf("| Version: 1.0                               |\n");
            printf("+--------------------------------------------+\n");

        // +----------------------------------------------------------+
        // | Configure                                                |
        // +----------------------------------------------------------+ 

            printf("  + Initializing configurations...... "); fflush(stdout); 

            cfgs = configs_construct(file_config, file_ios);

            printf("[Done]\n");

        // +----------------------------------------------------------+
        // | Construct                                                |
        // +----------------------------------------------------------+  

            printf("  + Initializing objects............. "); fflush(stdout); 

            objs = objects_construct(cfgs);

            printf("[Done]\n");         

        // +----------------------------------------------------------+
        // | Launch threads                                           |
        // +----------------------------------------------------------+  

            printf("  + Launch threads................... "); fflush(stdout); 

            threads_start(objs);

            printf("[Done]\n");


        // +----------------------------------------------------------+
        // | Wait                                                     |
        // +----------------------------------------------------------+  

            printf("  + Threads running.................. "); fflush(stdout); 
            
            threads_join(objs);

            printf("[Done]\n");

        // +----------------------------------------------------------+
        // | Free memory                                              |
        // +----------------------------------------------------------+  

            printf("  + Free memory...................... "); fflush(stdout);

            objects_destroy(objs);
            configs_destroy(cfgs);
            free((void *) file_config);
            free((void *) file_ios);

            printf("[Done]\n");

        return 0;

    }
