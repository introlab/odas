function tracks = tracks2var(filename, nTracks)

    fid = fopen(filename,'rb');
    tmp = fread(fid,inf,'int8');
    fclose(fid);
    
    nFrames = length(tmp) / (20 * nTracks);   
    tracks = cell(nTracks,1);

    for iTrack = 1:1:nTracks
       
        tracks{iTrack} = zeros(nFrames,4);
        
    end
    
    fid = fopen(filename,'rb');
    
    for iFrame = 1:1:nFrames
       
        ids = fread(fid, nTracks, 'uint64');
        xyzs = fread(fid, nTracks * 3, 'float');
        
        for iTrack = 1:1:nTracks
           
            tracks{iTrack}(iFrame,1) = double(ids(iTrack));
            tracks{iTrack}(iFrame,2:1:4) = xyzs(((iTrack-1)*3+1):1:((iTrack-1)*3+3));
            
        end
        
    end
    
    fclose(fid);

return