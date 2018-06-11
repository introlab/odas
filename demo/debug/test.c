
    #include <stdlib.h>
    #include <stdio.h>

	#include <odas/odas.h>

    int main(int argc, char * argv[]) {

    	unsigned int nChannels;
    	unsigned int nSamples;
    	unsigned int nTargets;
    	unsigned int nTracks;
    	unsigned int fS;

    	char strIn[32768];
    	char strOut[32768];

    	unsigned int iTrack;
    	unsigned int iChannel;
    	unsigned int iSample;

    	unsigned int nTrials = 10000;
    	unsigned int iTrial;

    	// Messages

		msg_hops_cfg * msg_hops_in_config;
		msg_hops_obj * msg_hops_in_object;
		msg_targets_cfg * msg_targets_config;
		msg_targets_obj * msg_targets_object;
		msg_tracks_cfg * msg_tracks_config;
		msg_tracks_obj * msg_tracks_object;
		msg_hops_cfg * msg_hops_out_config;
		msg_hops_obj * msg_hops_out_object;
		
		// (De)serializers

		dsr_hops_cfg * dsr_hops_config;
		dsr_hops_obj * dsr_hops_object;
		dsr_targets_cfg * dsr_targets_config;
		dsr_targets_obj * dsr_targets_object;
		ser_tracks_cfg * ser_tracks_config;
		ser_tracks_obj * ser_tracks_object;
		ser_hops_cfg * ser_hops_config;
		ser_hops_obj * ser_hops_object;

		// Parameters

    	nChannels = 7;
    	nSamples = 128;
    	nTargets = 4;
    	nTracks = 4;
  		fS = 16000;

  		// Init

   		msg_hops_in_config = msg_hops_cfg_construct();
   		msg_hops_in_config->nChannels = nChannels;
   		msg_hops_in_config->hopSize = nSamples;
   		msg_hops_in_config->fS = fS;
   		msg_hops_in_object = msg_hops_construct(msg_hops_in_config);

   		dsr_hops_config = dsr_hops_cfg_construct();
   		dsr_hops_object = dsr_hops_construct(dsr_hops_config, msg_hops_in_config);
   		dsr_hops_connect(dsr_hops_object, strIn, msg_hops_in_object);

   		msg_targets_config = msg_targets_cfg_construct();
   		msg_targets_config->nTargets = nTargets;
   		msg_targets_config->fS = fS;
   		msg_targets_object = msg_targets_construct(msg_targets_config);

   		dsr_targets_config = dsr_targets_cfg_construct();
   		dsr_targets_object = dsr_targets_construct(dsr_targets_config, msg_targets_config);
   		dsr_targets_connect(dsr_targets_object, strIn, msg_targets_object);

   		msg_tracks_config = msg_tracks_cfg_construct();
   		msg_tracks_config->nTracks = nTracks;
   		msg_tracks_config->fS = fS;
   		msg_tracks_object = msg_tracks_construct(msg_tracks_config);

   		ser_tracks_config = ser_tracks_cfg_construct();
   		ser_tracks_object = ser_tracks_construct(ser_tracks_config, msg_tracks_config);
   		ser_tracks_connect(ser_tracks_object, msg_tracks_object, strOut);

		msg_hops_out_config = msg_hops_cfg_construct();
		msg_hops_out_config->nChannels = nChannels;
		msg_hops_out_config->hopSize = nSamples;
		msg_hops_out_config->fS = fS;
		msg_hops_out_object = msg_hops_construct(msg_hops_out_config);		

		ser_hops_config = ser_hops_cfg_construct();
		ser_hops_object = ser_hops_construct(ser_hops_config, msg_hops_out_config);
		ser_hops_connect(ser_hops_object, msg_hops_out_object, strOut);

		msg_hops_out_object->timeStamp = 1;
		msg_hops_out_object->fS = 16000;

		for (iChannel = 0; iChannel < nChannels; iChannel++) {

			for (iSample = 0; iSample < nSamples; iSample++) {

				msg_hops_out_object->hops->array[iChannel][iSample] = (float) (iChannel * 1000 + iSample);

			}

		}

		hops_printf(msg_hops_out_object->hops);

		tracks_printf(msg_tracks_object->tracks);

		//ser_tracks_process(ser_tracks_object);
		//ser_hops_process(ser_hops_object);

		for (iTrial = 0; iTrial < nTrials; iTrial++) {
			//ser_hops_process(ser_hops_object);
			ser_tracks_process(ser_tracks_object);
		}

		printf("\n%s\n", strOut);

   		// Free

   		ser_tracks_disconnect(ser_tracks_object);
   		ser_tracks_destroy(ser_tracks_object);
   		ser_tracks_cfg_destroy(ser_tracks_config);
   		
   		msg_tracks_destroy(msg_tracks_object);
   		msg_tracks_cfg_destroy(msg_tracks_config);

   		dsr_targets_disconnect(dsr_targets_object);
   		dsr_targets_destroy(dsr_targets_object);
   		dsr_targets_cfg_destroy(dsr_targets_config);
   		
   		msg_targets_destroy(msg_targets_object);
   		msg_targets_cfg_destroy(msg_targets_config);

   		dsr_hops_disconnect(dsr_hops_object);
   		dsr_hops_destroy(dsr_hops_object);
   		dsr_hops_cfg_destroy(dsr_hops_config);
   		
   		msg_hops_destroy(msg_hops_in_object);
   		msg_hops_cfg_destroy(msg_hops_in_config);
    	
    }
