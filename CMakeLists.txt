project(ODAS)
cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

# Add base directory for includes (global)
include_directories(include/odas)

add_subdirectory(include)

add_library(odas SHARED

    src/odas/general/link.c
    src/odas/general/mic.c
    src/odas/general/samplerate.c
    src/odas/general/soundspeed.c
    src/odas/general/spatialfilter.c    
    src/odas/general/thread.c

    src/odas/init/combining.c
    src/odas/init/delay.c
    src/odas/init/directivity.c
    src/odas/init/hit.c
    src/odas/init/linking.c
    src/odas/init/scanning.c
    src/odas/init/space.c
    src/odas/init/windowing.c

    src/odas/signal/acorr.c
    src/odas/signal/aimg.c
    src/odas/signal/area.c
    src/odas/signal/assignation.c
    src/odas/signal/beampattern.c
    src/odas/signal/category.c
    src/odas/signal/coherence.c
    src/odas/signal/delta.c
    src/odas/signal/demixing.c
    src/odas/signal/env.c
    src/odas/signal/frame.c
    src/odas/signal/freq.c
    src/odas/signal/gain.c
    src/odas/signal/hop.c
    src/odas/signal/index.c
    src/odas/signal/kalman.c
    src/odas/signal/map.c
    src/odas/signal/mask.c
    src/odas/signal/mixture.c
    src/odas/signal/pair.c
    src/odas/signal/particle.c
    src/odas/signal/pitch.c
    src/odas/signal/point.c
    src/odas/signal/postprob.c
    src/odas/signal/pot.c
    src/odas/signal/scan.c
    src/odas/signal/spatialgain.c
    src/odas/signal/spatialindex.c
    src/odas/signal/spatialmask.c
    src/odas/signal/steer.c
    src/odas/signal/target.c
    src/odas/signal/tau.c
    src/odas/signal/tdoa.c
    src/odas/signal/track.c
    src/odas/signal/triangle.c
    src/odas/signal/window.c
    src/odas/signal/xcorr.c

    src/odas/system/acorr2pitch.c
    src/odas/system/demixing2env.c
    src/odas/system/demixing2freq.c
    src/odas/system/env2env.c
    src/odas/system/hop2hop.c
    src/odas/system/hop2frame.c
    src/odas/system/frame2freq.c
    src/odas/system/freq2acorr.c
    src/odas/system/freq2env.c
    src/odas/system/freq2freq.c
    src/odas/system/freq2frame.c
    src/odas/system/freq2xcorr.c
    src/odas/system/frame2hop.c
    src/odas/system/gain2mask.c
    src/odas/system/kalman2coherence.c
    src/odas/system/kalman2kalman.c
    src/odas/system/mixture2mixture.c
    src/odas/system/particle2coherence.c
    src/odas/system/particle2particle.c
    src/odas/system/pitch2category.c
    src/odas/system/steer2demixing.c
    src/odas/system/track2gain.c
    src/odas/system/track2steer.c
    src/odas/system/xcorr2aimg.c
    src/odas/system/xcorr2xcorr.c

    src/odas/utils/cmatrix.c
    src/odas/utils/fft.c
    src/odas/utils/fifo.c
    src/odas/utils/gaussian.c
    src/odas/utils/gaussjordan.c
    src/odas/utils/inverse.c
    src/odas/utils/json.c
    src/odas/utils/matrix.c
    src/odas/utils/pcm.c
    src/odas/utils/random.c
    src/odas/utils/share.c
    src/odas/utils/transcendental.c

    src/odas/aconnector/acon_hops.c
    src/odas/aconnector/acon_pots.c
    src/odas/aconnector/acon_powers.c
    src/odas/aconnector/acon_spectra.c
    src/odas/aconnector/acon_targets.c
    src/odas/aconnector/acon_tracks.c
    src/odas/amessage/amsg_hops.c
    src/odas/amessage/amsg_pots.c
    src/odas/amessage/amsg_powers.c
    src/odas/amessage/amsg_spectra.c
    src/odas/amessage/amsg_targets.c
    src/odas/amessage/amsg_tracks.c
    src/odas/amodule/amod_istft.c
    src/odas/amodule/amod_lag.c
    src/odas/amodule/amod_noise.c
    src/odas/amodule/amod_ssl.c
    src/odas/amodule/amod_sss.c
    src/odas/amodule/amod_sst.c
    src/odas/amodule/amod_stft.c
    src/odas/asink/asnk_hops.c    
    src/odas/asink/asnk_pots.c
    src/odas/asink/asnk_targets.c
    src/odas/asink/asnk_tracks.c
    src/odas/asource/asrc_hops.c
    src/odas/asource/asrc_targets.c

    src/odas/connector/con_hops.c
    src/odas/connector/con_pots.c
    src/odas/connector/con_powers.c
    src/odas/connector/con_spectra.c
    src/odas/connector/con_targets.c
    src/odas/connector/con_tracks.c
    src/odas/message/msg_hops.c
    src/odas/message/msg_pots.c
    src/odas/message/msg_powers.c
    src/odas/message/msg_spectra.c
    src/odas/message/msg_targets.c
    src/odas/message/msg_tracks.c
    src/odas/module/mod_istft.c
    src/odas/module/mod_lag.c
    src/odas/module/mod_noise.c
    src/odas/module/mod_ssl.c
    src/odas/module/mod_sss.c
    src/odas/module/mod_sst.c
    src/odas/module/mod_stft.c
    src/odas/sink/snk_hops.c
    src/odas/sink/snk_pots.c
    src/odas/sink/snk_targets.c
    src/odas/sink/snk_tracks.c
    src/odas/source/src_hops.c
    src/odas/source/src_targets.c

)

target_link_libraries(odas
	
    ${PC_FFTW3_LIBRARIES}
	m
    pthread

)

add_executable(core

    demo/core/main.c

    demo/core/configs.c
    demo/core/objects.c
    demo/core/params.c
    demo/core/settings.c
    demo/core/sockets.c

)

target_link_libraries(core

    odas

)

install(TARGETS odas DESTINATION lib)

