project(ODAS)
cmake_minimum_required(VERSION 2.4.6..3.16)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

option(ODAS_INSTALL_EXECUTABLES "Install the odaslive and odasserver executables along with the odas library" OFF)
option(ODAS_FORCE_BIN_AND_LIB_DIRS "Force the installation of the odas library and executables in the bin and lib directories" ON)
option(ODAS_DISABLE_INSTALL "Disable the installation of the odas library and executables" OFF)


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

if(ODAS_FORCE_BIN_AND_LIB_DIRS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

#Add base directory for includes (global)
include_directories(include/odas)

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

add_library(odas SHARED
    ${SRC}
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

if (NOT ODAS_DISABLE_INSTALL)
    install(TARGETS odas LIBRARY DESTINATION lib)
    install(
        DIRECTORY include/
        DESTINATION include
        FILES_MATCHING
            PATTERN "*.h"
    )

    if(ODAS_INSTALL_EXECUTABLES)
        install(TARGETS odaslive DESTINATION bin)
        install(TARGETS odasserver DESTINATION bin)
    endif()
endif()


if(ODAS_FORCE_BIN_AND_LIB_DIRS)
    unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    unset(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
endif()
