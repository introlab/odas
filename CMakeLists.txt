project(ODAS)
cmake_minimum_required(VERSION 2.4.6..3.16)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

option(ODAS_INSTALL_EXECUTABLES "Install the odaslive and odasserver executables along with the odas library" OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)
pkg_check_modules(PC_ALSA REQUIRED alsa)
pkg_check_modules(PC_LIBCONFIG REQUIRED libconfig)
pkg_check_modules(PC_PULSEAUDIO REQUIRED libpulse-simple)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Compile in release mode if not set
if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#Add base directory for includes (global)
include_directories(include/odas)

add_subdirectory(include)

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

    src/signal/acorr.c
    src/signal/aimg.c
    src/signal/area.c
    src/signal/assignation.c
    src/signal/beampattern.c
    src/signal/category.c
    src/signal/coherence.c
    src/signal/delta.c
    src/signal/demixing.c
    src/signal/env.c
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
    src/signal/pitch.c
    src/signal/point.c
    src/signal/postprob.c
    src/signal/pot.c
    src/signal/scan.c
    src/signal/spatialgain.c
    src/signal/spatialindex.c
    src/signal/spatialmask.c
    src/signal/steer.c
    src/signal/target.c
    src/signal/tau.c
    src/signal/tdoa.c
    src/signal/track.c
    src/signal/triangle.c
    src/signal/window.c
    src/signal/xcorr.c

    src/system/acorr2pitch.c
    src/system/demixing2env.c
    src/system/demixing2freq.c
    src/system/env2env.c
    src/system/hop2hop.c
    src/system/hop2frame.c
    src/system/frame2freq.c
    src/system/freq2acorr.c
    src/system/freq2env.c
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
    src/system/pitch2category.c
    src/system/steer2demixing.c
    src/system/track2gain.c
    src/system/track2steer.c
    src/system/xcorr2aimg.c
    src/system/xcorr2xcorr.c

    src/utils/cmatrix.c
    src/utils/fft.c
    src/utils/fifo.c
    src/utils/gaussian.c
    src/utils/gaussjordan.c
    src/utils/inverse.c
    src/utils/matrix.c
    src/utils/pcm.c
    src/utils/random.c
    src/utils/transcendental.c

    src/aconnector/acon_categories.c
    src/aconnector/acon_hops.c
    src/aconnector/acon_pots.c
    src/aconnector/acon_powers.c
    src/aconnector/acon_spectra.c
    src/aconnector/acon_targets.c
    src/aconnector/acon_tracks.c
    src/ainjector/ainj_targets.c
    src/amessage/amsg_categories.c
    src/amessage/amsg_hops.c
    src/amessage/amsg_pots.c
    src/amessage/amsg_powers.c
    src/amessage/amsg_spectra.c
    src/amessage/amsg_targets.c
    src/amessage/amsg_tracks.c
    src/amodule/amod_classify.c
    src/amodule/amod_istft.c
    src/amodule/amod_mapping.c
    src/amodule/amod_noise.c
    src/amodule/amod_resample.c
    src/amodule/amod_ssl.c
    src/amodule/amod_sss.c
    src/amodule/amod_sst.c
    src/amodule/amod_stft.c
    src/amodule/amod_volume.c
    src/asink/asnk_categories.c
    src/asink/asnk_hops.c
    src/asink/asnk_pots.c
    src/asink/asnk_powers.c
    src/asink/asnk_spectra.c
    src/asink/asnk_tracks.c
    src/asource/asrc_hops.c

    src/connector/con_categories.c
    src/connector/con_hops.c
    src/connector/con_pots.c
    src/connector/con_powers.c
    src/connector/con_spectra.c
    src/connector/con_targets.c
    src/connector/con_tracks.c
    src/injector/inj_targets.c
    src/message/msg_categories.c
    src/message/msg_hops.c
    src/message/msg_pots.c
    src/message/msg_powers.c
    src/message/msg_spectra.c
    src/message/msg_targets.c
    src/message/msg_tracks.c
    src/module/mod_classify.c
    src/module/mod_istft.c
    src/module/mod_mapping.c
    src/module/mod_noise.c
    src/module/mod_resample.c
    src/module/mod_ssl.c
    src/module/mod_sss.c
    src/module/mod_sst.c
    src/module/mod_stft.c
    src/module/mod_volume.c
    src/sink/snk_categories.c
    src/sink/snk_hops.c
    src/sink/snk_pots.c
    src/sink/snk_powers.c
    src/sink/snk_spectra.c
    src/sink/snk_tracks.c
    src/source/src_hops.c

)

set(PUBLIC_HEADER

    include/odas.h

    include/connector/con_categories.h
    include/connector/con_hops.h
    include/connector/con_pots.h
    include/connector/con_powers.h
    include/connector/con_spectra.h
    include/connector/con_targets.h
    include/connector/con_tracks.h

    include/injector/inj_targets.h

    include/message/msg_categories.h
    include/message/msg_hops.h
    include/message/msg_pots.h
    include/message/msg_powers.h
    include/message/msg_spectra.h
    include/message/msg_targets.h
    include/message/msg_tracks.h

    include/module/mod_classify.h
    include/module/mod_istft.h
    include/module/mod_mapping.h
    include/module/mod_noise.h
    include/module/mod_resample.h
    include/module/mod_ssl.h
    include/module/mod_sst.h
    include/module/mod_sss.h
    include/module/mod_stft.h
    include/module/mod_volume.h

    include/sink/snk_categories.h
    include/sink/snk_hops.h
    include/sink/snk_pots.h
    include/sink/snk_powers.h
    include/sink/snk_spectra.h
    include/sink/snk_tracks.h

    include/source/src_hops.h

    include/acconector/acon_categories.h
    include/acconector/acon_hops.h
    include/acconector/acon_pots.h
    include/acconector/acon_powers.h
    include/acconector/acon_spectra.h
    include/acconector/acon_targets.h
    include/acconector/acon_tracks.h

    include/ammessage/amsg_categories.h
    include/ammessage/amsg_hops.h
    include/ammessage/amsg_pots.h
    include/ammessage/amsg_powers.h
    include/ammessage/amsg_spectra.h
    include/ammessage/amsg_targets.h
    include/ammessage/amsg_tracks.h

    include/amodule/amod_classify.h
    include/amodule/amod_istft.h
    include/amodule/amod_mapping.h
    include/amodule/amod_noise.h
    include/amodule/amod_resample.h
    include/amodule/amod_ssl.h
    include/amodule/amod_sst.h
    include/amodule/amod_sss.h
    include/amodule/amod_stft.h
    include/amodule/amod_volume.h

    include/asink/asnk_categories.h
    include/asink/asnk_hops.h
    include/asink/asnk_pots.h
    include/asink/asnk_powers.h
    include/asink/asnk_spectra.h
    include/asink/asnk_tracks.h

    include/asource/asrc_hops.h

)

add_library(odas SHARED
    ${SRC}
)
set_property(
    TARGET odas
    PROPERTY PUBLIC_HEADER ${PUBLIC_HEADER}
)

target_link_libraries(odas
    ${PC_FFTW3_LIBRARIES}
    ${PC_ALSA_LIBRARIES}
    ${PC_LIBCONFIG_LIBRARIES}
    ${PC_PULSEAUDIO_LIBRARIES}
    m
    pthread
)

add_executable(odaslive
    demo/odaslive/main.c
    demo/odaslive/configs.c
    demo/odaslive/objects.c
    demo/odaslive/parameters.c
    demo/odaslive/profiler.c
    demo/odaslive/threads.c
)
target_link_libraries(odaslive
    odas
)

add_executable(odasserver
    demo/odasserver/main.c
)
target_link_libraries(odasserver
    odas
)

install(TARGETS odas LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

if(ODAS_INSTALL_EXECUTABLES)
    install(TARGETS odaslive DESTINATION bin)
    install(TARGETS odasserver DESTINATION bin)
endif()

unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
unset(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
