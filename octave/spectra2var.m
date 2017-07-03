function spectra = spectra2var(filename, frameSize, nChannels)

    fid = fopen(filename,'rb');
    vector = fread(fid,inf,'float');
    fclose(fid);
    
    vectorReal = vector(1:2:length(vector));
    vectorComplex = vector(2:2:length(vector));
    vectorRC = vectorReal + 1i * vectorComplex;
    
    halfFrameSize = frameSize/2 + 1;
    nSamplesPerFrame = nChannels * halfFrameSize;
    
    nSamples = length(vectorRC);
    nFrames = nSamples / nSamplesPerFrame;

    spectra = cell(nChannels,1);
    
    for iChannel = 1:1:nChannels
    
        spectra{iChannel} = zeros(nFrames, halfFrameSize);   
    
        for iFrame = 1:1:nFrames

            iStart = (iFrame-1) * (nChannels * halfFrameSize) + iChannel;
            iStop = iStart + halfFrameSize * nChannels - 1;

            indexes = iStart:nChannels:iStop;
            
            spectra{iChannel}(iFrame,:) = vectorRC(indexes);

        end
        
    end
    
return