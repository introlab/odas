
    #include <odas/odas.h>

    #include "parameters.h"
    #include "configs.h"
    #include "objects.h"
    #include "threads.h"
    #include "profiler.h"

    #include <getopt.h>
    #include <time.h>
    #include <signal.h>

    // +----------------------------------------------------------+
    // | Variables                                                |
    // +----------------------------------------------------------+  

        // +------------------------------------------------------+
        // | Type                                                 |
        // +------------------------------------------------------+   

            enum processing {
                processing_singlethread,
                processing_multithread
            } type;

        // +------------------------------------------------------+
        // | Getopt                                               |
        // +------------------------------------------------------+   

            int c;
            char * file_config;

        // +------------------------------------------------------+
        // | Objects                                              |
        // +------------------------------------------------------+   

            objects * objs;
            aobjects * aobjs;

        // +------------------------------------------------------+
        // | Configurations                                       |
        // +------------------------------------------------------+        

            configs * cfgs;   

        // +------------------------------------------------------+
        // | Profiler                                             |
        // +------------------------------------------------------+   

            profiler * prf;

        // +------------------------------------------------------+
        // | Flag                                                 |
        // +------------------------------------------------------+                   

            char stopProcess;

    // +----------------------------------------------------------+
    // | Signal handler                                           |
    // +----------------------------------------------------------+  

    void sighandler(int signum) {
        
        if (type == processing_singlethread) {
            stopProcess = 1;
        }
        if (type == processing_multithread) {
            threads_multiple_stop(aobjs);
        }        

    }

    // +----------------------------------------------------------+
    // | Main routine                                             |
    // +----------------------------------------------------------+  

    int main(int argc, char * argv[]) {

        // +------------------------------------------------------+
        // | Arguments                                            |
        // +------------------------------------------------------+  

            file_config = (char *) NULL;
            char verbose = 0x00;

            type = processing_multithread;

            while ((c = getopt(argc,argv, "c:hsv")) != -1) {

                switch(c) {

                    case 'c':

                        file_config = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
                        strcpy(file_config, optarg);                        

                    break;

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
                        printf("| -c       Configuration file (.cfg)                 |\n");
                        printf("| -h       Help                                      |\n");
                        printf("| -s       Process sequentially (no multithread)     |\n");
                        printf("| -v       Verbose                                   |\n");
                        printf("+----------------------------------------------------+\n");                

                        exit(EXIT_SUCCESS);

                    break;

                    case 's':

                        type = processing_singlethread;

                    break;

                    case 'v':

                        verbose = 0x01;

                    break;

                }

            }

            if (file_config == NULL) {
                printf("Missing configuration file.\n");
                exit(EXIT_FAILURE);
            }

        // +------------------------------------------------------+
        // | Copyright                                            |
        // +------------------------------------------------------+ 

            if (verbose == 0x01) {

            printf("+--------------------------------------------+\n");
            printf("|    ODAS (Open embeddeD Audition System)    |\n");
            printf("+--------------------------------------------+\n");
            printf("| Author:  Francois Grondin                  |\n");
            printf("| Email:   francois.grondin2@usherbrooke.ca  |\n");
            printf("| Website: introlab.3it.usherbrooke.ca       |\n");
            printf("| Version: 1.0                               |\n");
            printf("+--------------------------------------------+\n");

            }

        // +------------------------------------------------------+
        // | Single thread                                        |
        // +------------------------------------------------------+  

            if (type == processing_singlethread) {

            // +--------------------------------------------------+
            // | Profiler                                         |
            // +--------------------------------------------------+ 

                prf = profiler_construct();

            // +--------------------------------------------------+
            // | Configure                                        |
            // +--------------------------------------------------+ 

                if (verbose == 0x01) printf("| + Initializing configurations...... "); fflush(stdout); 

                cfgs = configs_construct(file_config);

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Construct                                        |
            // +--------------------------------------------------+  

                if (verbose == 0x01) printf("| + Initializing objects............. "); fflush(stdout); 

                objs = objects_construct(cfgs);    
                
                if (verbose == 0x01) printf("[Done] |\n");   

            // +--------------------------------------------------+
            // | Processing                                       |
            // +--------------------------------------------------+  

                if (verbose == 0x01) printf("| + Processing....................... "); fflush(stdout);

                threads_single_open(objs);
                stopProcess = 0;
                while((threads_single_process(objs, prf) == 0) && (stopProcess == 0));
                threads_single_close(objs);

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Free memory                                      |
            // +--------------------------------------------------+  

                if (verbose == 0x01) printf("| + Free memory...................... "); fflush(stdout);

                objects_destroy(objs); 
                configs_destroy(cfgs);
                free((void *) file_config);

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Results                                          |
            // +--------------------------------------------------+  

                if (verbose == 0x01) profiler_printf(prf);

                profiler_destroy(prf);

            }

        // +------------------------------------------------------+
        // | Multiple threads                                     |
        // +------------------------------------------------------+  

            if (type == processing_multithread) {

            // +--------------------------------------------------+
            // | Configure                                        |
            // +--------------------------------------------------+ 

                if (verbose == 0x01) printf("| + Initializing configurations...... "); fflush(stdout); 

                cfgs = configs_construct(file_config);

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Construct                                        |
            // +--------------------------------------------------+  

                if (verbose == 0x01) printf("| + Initializing objects............. "); fflush(stdout); 
                
                aobjs = aobjects_construct(cfgs);    

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Launch threads                                   |
            // +--------------------------------------------------+  

                signal(SIGINT, sighandler);

                if (verbose == 0x01) printf("| + Launch threads................... "); fflush(stdout); 

                threads_multiple_start(aobjs);

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Wait                                             |
            // +--------------------------------------------------+  

                if (verbose == 0x01) printf("| + Threads running.................. "); fflush(stdout); 
                
                threads_multiple_join(aobjs);

                if (verbose == 0x01) printf("[Done] |\n");

            // +--------------------------------------------------+
            // | Free memory                                      |
            // +--------------------------------------------------+  

                if (verbose == 0x01) printf("| + Free memory...................... "); fflush(stdout);

                aobjects_destroy(aobjs);
                configs_destroy(cfgs);
                free((void *) file_config);

                if (verbose == 0x01) printf("[Done] |\n");

                if (verbose == 0x01) printf("+--------------------------------------------+\n");

            }

        return 0;

    }
