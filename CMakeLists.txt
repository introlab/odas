cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)
pkg_check_modules(PC_ALSA REQUIRED alsa)
pkg_check_modules(PC_LIBCONFIG REQUIRED libconfig)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

set(SRC

    src/general/format.c
    src/general/interface.c
    src/general/link.c
    src/general/mic.c
    src/general/samplerate.c
    src/general/soundspeed.c
    src/general/spatialfilter.c    
    src/general/thread.c

    src/init/combining.c
    src/init/delay.c
    src/init/directivity.c
    src/init/hit.c
    src/init/linking.c
    src/init/scanning.c
    src/init/space.c
    src/init/windowing.c

    src/signal/aimg.c
    src/signal/area.c
    src/signal/assignation.c
    src/signal/beampattern.c
    src/signal/coherence.c
    src/signal/delta.c
    src/signal/frame.c
    src/signal/freq.c
    src/signal/gain.c
    src/signal/hop.c
    src/signal/index.c
    src/signal/kalman.c
    src/signal/map.c
    src/signal/mask.c
    src/signal/mixture.c
    src/signal/pair.c
    src/signal/particle.c
    src/signal/point.c
    src/signal/postprob.c
    src/signal/pot.c
    src/signal/scan.c
    src/signal/shift.c
    src/signal/spatialgain.c
    src/signal/spatialindex.c
    src/signal/spatialmask.c
    src/signal/tau.c
    src/signal/tdoa.c
    src/signal/track.c
    src/signal/triangle.c
    src/signal/window.c
    src/signal/xcorr.c

    src/system/hop2hop.c
    src/system/hop2frame.c
    src/system/frame2freq.c
    src/system/freq2freq.c
    src/system/freq2frame.c
    src/system/freq2xcorr.c
    src/system/frame2hop.c
    src/system/gain2mask.c
    src/system/kalman2coherence.c
    src/system/kalman2kalman.c
    src/system/mixture2mixture.c
    src/system/particle2coherence.c
    src/system/particle2particle.c
    src/system/shift2freq.c
    src/system/track2gain.c
    src/system/track2shift.c
    src/system/xcorr2aimg.c
    src/system/xcorr2xcorr.c

    src/utils/fft.c
    src/utils/fifo.c
    src/utils/gaussian.c
    src/utils/matrix.c
    src/utils/pcm.c
    src/utils/random.c

    src/aconnector/acon_hops.c
    src/aconnector/acon_pots.c
    src/aconnector/acon_spectra.c
    src/aconnector/acon_tracks.c
    src/amessage/amsg_hops.c
    src/amessage/amsg_pots.c
    src/amessage/amsg_spectra.c
    src/amessage/amsg_tracks.c
    src/amodule/amod_istft.c
    src/amodule/amod_mapping.c
    src/amodule/amod_resample.c
    src/amodule/amod_ssl.c
    src/amodule/amod_sspf.c
    src/amodule/amod_sss.c
    src/amodule/amod_sst.c
    src/amodule/amod_stft.c
    src/asink/asnk_hops.c    
    src/asink/asnk_pots.c
    src/asink/asnk_spectra.c
    src/asink/asnk_tracks.c
    src/asource/asrc_hops.c  
    src/asource/asrc_spectra.c
    
    src/connector/con_hops.c
    src/connector/con_pots.c
    src/connector/con_spectra.c
    src/connector/con_tracks.c
    src/message/msg_hops.c
    src/message/msg_pots.c
    src/message/msg_spectra.c
    src/message/msg_tracks.c
    src/message/msg_xcorrs.c
    src/module/mod_istft.c
    src/module/mod_mapping.c
    src/module/mod_resample.c
    src/module/mod_ssl.c
    src/module/mod_sspf.c
    src/module/mod_sss.c
    src/module/mod_sst.c
    src/module/mod_stft.c
    src/sink/snk_hops.c
    src/sink/snk_pots.c
    src/sink/snk_spectra.c
    src/sink/snk_tracks.c
    src/sink/snk_xcorrs.c
    src/source/src_hops.c
    src/source/src_pots.c
    src/source/src_spectra.c
    src/source/src_tracks.c

)

add_library(odas SHARED
	${SRC}
)

target_link_libraries(odas
	${PC_FFTW3_LIBRARIES}
	${PC_ALSA_LIBRARIES}
    ${PC_LIBCONFIG_LIBRARIES}
	m
    pthread
)

add_executable(core
    demo/main.c
    demo/configs.c
    demo/objects.c
    demo/parameters.c
    demo/profiler.c
    demo/threads.c
)
target_link_libraries(core
    odas
)

add_executable(server
    demo/server.c
)
