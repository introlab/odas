    
    #include "mod_resample.h"

    mod_resample_obj * mod_resample_construct(const mod_resample_cfg * mod_resample_config, const msg_hops_cfg * msg_hops_in_config, const msg_hops_cfg * msg_hops_out_config) {

        mod_resample_obj * obj;

        obj = (mod_resample_obj *) malloc(sizeof(mod_resample_obj));

        obj->timeStamp = 0;

        if (mod_resample_config->fSin == mod_resample_config->fSout) {
            obj->type = 's';
        }
        if (mod_resample_config->fSin > mod_resample_config->fSout) {
            obj->type = 'd';
        }
        if (mod_resample_config->fSin < mod_resample_config->fSout) {
            obj->type = 'u';
        }

        obj->nChannels = msg_hops_in_config->nChannels;
        obj->fSin = mod_resample_config->fSin;
        obj->fSout = mod_resample_config->fSout;
        obj->hopSizeIn = msg_hops_in_config->hopSize;
        obj->hopSizeOut = msg_hops_out_config->hopSize;
        obj->ratio = ((float) obj->fSout) / ((float) obj->fSin);

        switch (obj->type) {

            case 'd':

                obj->frameSize = obj->hopSizeIn * 2;
                obj->halfFrameSize = obj->frameSize / 2 + 1;
                obj->lowPassCut = (unsigned int) floorf(((float) (obj->frameSize/2)) * obj->ratio);

                obj->hop2hop = hop2hop_buffer_construct_zero(obj->nChannels, obj->hopSizeIn, obj->hopSizeOut, obj->ratio);

                obj->hop2frame = hop2frame_construct_zero(obj->hopSizeIn, obj->frameSize, obj->nChannels);
                obj->framesAnalysis = frames_construct_zero(obj->nChannels, obj->frameSize);
                obj->frame2freq = frame2freq_construct_zero(obj->frameSize, obj->halfFrameSize);
                obj->freqsAnalysis = freqs_construct_zero(obj->nChannels, obj->halfFrameSize);
                obj->freq2freq = freq2freq_construct_zero(obj->halfFrameSize, obj-> lowPassCut, 0.0f);
                obj->freqsSynthesis = freqs_construct_zero(obj->nChannels, obj->halfFrameSize);
                obj->freq2frame = freq2frame_construct_zero(obj->frameSize, obj->halfFrameSize);
                obj->framesSynthesis = frames_construct_zero(obj->nChannels, obj->frameSize);
                obj->frame2hop = frame2hop_construct_zero(obj->hopSizeIn, obj->frameSize, obj->nChannels);
                obj->hops = hops_construct_zero(obj->nChannels, obj->hopSizeIn);
                
            break;

            case 'u':

                obj->frameSize = obj->hopSizeOut * 2;
                obj->halfFrameSize = obj->frameSize / 2 + 1;
                obj->lowPassCut = (unsigned int) floorf(((float) (obj->frameSize/2)) / obj->ratio);

                obj->hop2hop = hop2hop_buffer_construct_zero(obj->nChannels, obj->hopSizeIn, obj->hopSizeOut, obj->ratio);
                
                obj->hop2frame = hop2frame_construct_zero(obj->hopSizeOut, obj->frameSize, obj->nChannels);
                obj->framesAnalysis = frames_construct_zero(obj->nChannels, obj->frameSize);
                obj->frame2freq = frame2freq_construct_zero(obj->frameSize, obj->halfFrameSize);
                obj->freqsAnalysis = freqs_construct_zero(obj->nChannels, obj->halfFrameSize);
                obj->freq2freq = freq2freq_construct_zero(obj->halfFrameSize, obj-> lowPassCut, 0.0f);
                obj->freqsSynthesis = freqs_construct_zero(obj->nChannels, obj->halfFrameSize);
                obj->freq2frame = freq2frame_construct_zero(obj->frameSize, obj->halfFrameSize);
                obj->framesSynthesis = frames_construct_zero(obj->nChannels, obj->frameSize);
                obj->frame2hop = frame2hop_construct_zero(obj->hopSizeOut, obj->frameSize, obj->nChannels);
                obj->hops = hops_construct_zero(obj->nChannels, obj->hopSizeOut);                

            break;

            case 's':

                obj->frameSize = 0;
                obj->halfFrameSize = 0;
                obj->lowPassCut = 0;

                obj->hop2hop = hop2hop_buffer_construct_zero(obj->nChannels, obj->hopSizeIn, obj->hopSizeOut, obj->ratio);

                obj->hop2frame = (hop2frame_obj *) NULL;
                obj->framesAnalysis = (frames_obj *) NULL;
                obj->frame2freq = (frame2freq_obj *) NULL;
                obj->freqsAnalysis = (freqs_obj *) NULL;
                obj->freq2freq = (freq2freq_obj *) NULL;
                obj->freqsSynthesis = (freqs_obj *) NULL;
                obj->freq2frame = (freq2frame_obj *) NULL;
                obj->framesSynthesis = (frames_obj *) NULL;
                obj->frame2hop = (frame2hop_obj *) NULL;
                obj->hops = (hops_obj *) NULL;

            break;

        }

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

        return obj;

    }

    void mod_resample_destroy(mod_resample_obj * obj) {

        if (obj->hop2hop != NULL) {
            hop2hop_buffer_destroy(obj->hop2hop);
        }

        if (obj->hop2frame != NULL) {
            hop2frame_destroy(obj->hop2frame);
        }

        if (obj->framesAnalysis != NULL) {
            frames_destroy(obj->framesAnalysis);
        }

        if (obj->frame2freq != NULL) {
            frame2freq_destroy(obj->frame2freq);
        }

        if (obj->freqsAnalysis != NULL) {
            freqs_destroy(obj->freqsAnalysis);
        }

        if (obj->freq2freq != NULL) {
            freq2freq_destroy(obj->freq2freq);
        }

        if (obj->freqsSynthesis != NULL) {
            freqs_destroy(obj->freqsSynthesis);
        }

        if (obj->freq2frame != NULL) {
            freq2frame_destroy(obj->freq2frame);
        }

        if (obj->framesSynthesis != NULL) {
            frames_destroy(obj->framesSynthesis);
        }

        if (obj->frame2hop != NULL) {
            frame2hop_destroy(obj->frame2hop);
        }

        if (obj->hops != NULL) {
            hops_destroy(obj->hops);
        }

        free((void *) obj);

    }

    int mod_resample_process(mod_resample_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            switch(obj->type) {

                case 'd':

                    rtnValue = mod_resample_process_down(obj);

                break;

                case 'u':

                    rtnValue = mod_resample_process_up(obj);

                break;

                case 's':

                    rtnValue = mod_resample_process_same(obj);

                break;

            }

            obj->timeStamp++;
            obj->out->timeStamp = obj->timeStamp;
            
        }
        else {

            msg_hops_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    int mod_resample_process_down(mod_resample_obj * obj) {

        int rtnValue;
        char pushDone;
        char popDone;

        if (hop2hop_buffer_isFull(obj->hop2hop) == 0) {

            hop2frame_process(obj->hop2frame, 
                              obj->in->hops,
                              obj->framesAnalysis);

            frame2freq_process(obj->frame2freq,
                               obj->framesAnalysis,
                               obj->freqsAnalysis);

            freq2freq_process_lowpass(obj->freq2freq,
                                      obj->freqsAnalysis,
                                      obj->freqsSynthesis);

            freq2frame_process(obj->freq2frame,
                               obj->freqsSynthesis,
                               obj->framesSynthesis);
         
            frame2hop_process(obj->frame2hop,
                              obj->framesSynthesis,
                              obj->hops);

            hop2hop_buffer_push(obj->hop2hop,
                                obj->hops);

            pushDone = 1;

        }
        else {

            pushDone = 0;

        }

        if (hop2hop_buffer_isEmpty(obj->hop2hop) == 0) {

            hop2hop_buffer_pop(obj->hop2hop,
                               obj->out->hops);

            popDone = 1;

        }
        else {

            popDone = 0;

        }

        if ((pushDone == 0) && (popDone == 0)) {
            rtnValue = 1;
        }
        if ((pushDone == 0) && (popDone == 1)) {
            rtnValue = 2;
        }
        if ((pushDone == 1) && (popDone == 0)) {
            rtnValue = 3;
        }
        if ((pushDone == 1) && (popDone == 1)) {
            rtnValue = 4;
        }

        return rtnValue;

    }

    int mod_resample_process_up(mod_resample_obj * obj) {

        int rtnValue;
        char pushDone;
        char popDone;

        if (hop2hop_buffer_isFull(obj->hop2hop) == 0) {

            hop2hop_buffer_push(obj->hop2hop,
                                obj->in->hops);

            pushDone = 1;

        }
        else {

            pushDone = 0;

        }

        if (hop2hop_buffer_isEmpty(obj->hop2hop) == 0) {

            hop2hop_buffer_pop(obj->hop2hop,
                               obj->hops);

            hop2frame_process(obj->hop2frame, 
                              obj->hops,
                              obj->framesAnalysis);

            frame2freq_process(obj->frame2freq,
                               obj->framesAnalysis,
                               obj->freqsAnalysis);

            freq2freq_process_lowpass(obj->freq2freq,
                                      obj->freqsAnalysis,
                                      obj->freqsSynthesis);

            freq2frame_process(obj->freq2frame,
                               obj->freqsSynthesis,
                               obj->framesSynthesis);
         
            frame2hop_process(obj->frame2hop,
                              obj->framesSynthesis,
                              obj->out->hops);

            popDone = 1;

        }
        else {

            popDone = 0;

        }

        if ((pushDone == 0) && (popDone == 0)) {
            rtnValue = 1;
        }
        if ((pushDone == 0) && (popDone == 1)) {
            rtnValue = 2;
        }
        if ((pushDone == 1) && (popDone == 0)) {
            rtnValue = 3;
        }
        if ((pushDone == 1) && (popDone == 1)) {
            rtnValue = 4;
        }

        return rtnValue;

    }

    int mod_resample_process_same(mod_resample_obj * obj) {

        int rtnValue;
        char pushDone;
        char popDone;

        if (hop2hop_buffer_isFull(obj->hop2hop) == 0) {

            hop2hop_buffer_push(obj->hop2hop,
                                obj->in->hops);

            pushDone = 1;

        }
        else {

            pushDone = 0;

        }

        if (hop2hop_buffer_isEmpty(obj->hop2hop) == 0) {

            hop2hop_buffer_pop(obj->hop2hop,
                               obj->out->hops);

            popDone = 1;

        }
        else {

            popDone = 0;

        }

        if ((pushDone == 0) && (popDone == 0)) {
            rtnValue = 1;
        }
        if ((pushDone == 0) && (popDone == 1)) {
            rtnValue = 2;
        }
        if ((pushDone == 1) && (popDone == 0)) {
            rtnValue = 3;
        }
        if ((pushDone == 1) && (popDone == 1)) {
            rtnValue = 4;
        }

        return rtnValue;

    }

    void mod_resample_connect(mod_resample_obj * obj, msg_hops_obj * in, msg_hops_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_resample_disconnect(mod_resample_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_hops_obj *) NULL;

    }

    mod_resample_cfg * mod_resample_cfg_construct(void) {

        mod_resample_cfg * cfg;

        cfg = (mod_resample_cfg *) malloc(sizeof(mod_resample_cfg));

        cfg->fSin = 0;
        cfg->fSout = 0;

        return cfg;

    }

    void mod_resample_cfg_destroy(mod_resample_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_resample_cfg_printf(const mod_resample_cfg * cfg) {

        printf("fSin = %u\n", cfg->fSin);
        printf("fSout = %u\n", cfg->fSout);

    }
