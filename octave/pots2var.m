function pots = pots2var(filename, nPots)

    fid = fopen(filename,'rb');
    vector = fread(fid,inf,'float');
    fclose(fid);
    
    pots = cell(nPots,1);
    nFrames = size(vector,1)/(4*nPots);
    
    for iPot = 1:1:nPots
    
        pots{iPot} = zeros(nFrames, 4);   

        for iFrame = 1:1:nFrames
            
            iStart = (iFrame-1) * 4 * nPots + 1;
            iStop = iStart + 3;
            
            pots{iPot}(iFrame,:) = vector(iStart:1:iStop);            
            
        end
        
    end
    
return